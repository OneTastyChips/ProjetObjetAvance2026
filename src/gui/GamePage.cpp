
#include "GamePage.hpp"

#include <data/Interrogation.hpp>
#include <gui/SettingsDialog.hpp>

namespace NomCool::gui {

GamePage::GamePage(data::Experience &experience, data::SkinManager &skinManager,
                   data::QuestionGenerator &questionGenerator,
                   const data::GameConfig &config, QWidget *parent)
    : QWidget(parent), mExperience(experience), mSkinManager(skinManager),
      mQuestionGenerator(questionGenerator), mConfig(config),
      mQuestionsRemaining(config.questionCount) {
  auto *mainLayout = new QVBoxLayout();
  mainLayout->setContentsMargins(20, 10, 20, 20);
  mainLayout->setSpacing(8);

  // --- Barre du haut : retour + XP + pause (si applicable) ---
  auto *topBar = new QHBoxLayout();

  auto *backButton = new QPushButton("← Accueil");
  connect(backButton, &QPushButton::clicked, this, [this] {
    mQuestionTimer->stop();
    mExperience.save();
    emit backToHome();
  });
  topBar->addWidget(backButton);

  mExperienceBar = new ExperienceBar();
  mExperienceBar->update(mExperience);
  topBar->addWidget(mExperienceBar, 1);

  // Bouton pause uniquement si timer ou nombre de questions fixe
  const bool showPause = mConfig.hasTimer || mConfig.questionCount != -1;
  if (showPause) {
    mPauseButton = new QPushButton("Pause");
    connect(mPauseButton, &QPushButton::clicked, this, [this] {
      if (mQuestionTimer->isPaused()) {
        mQuestionTimer->resume();
        if (mInterrogation)
          mInterrogation->show();
        mPauseButton->setText("Pause");
      } else {
        mQuestionTimer->pause();
        if (mInterrogation)
          mInterrogation->hide();
        mPauseButton->setText("Reprendre");
      }
    });
    topBar->addWidget(mPauseButton);
  }

  mainLayout->addLayout(topBar);

  // --- Ligne score ---
  mScoreRow = new QHBoxLayout();
  mScoreDisplay = new ScoreDisplay(mScore);
  mScoreRow->addWidget(mScoreDisplay);
  if (mConfig.questionCount > 0) {
    mCountLabel = new QLabel(
        QString("Questions restantes : %1").arg(mQuestionsRemaining));
    mCountLabel->setStyleSheet("color: #555;");
    mScoreRow->addWidget(mCountLabel);
  }
  mScoreRow->addStretch();
  mainLayout->addLayout(mScoreRow);

  // --- Chronomètre ---
  mQuestionTimer = new QuestionTimer();
  if (mConfig.hasTimer) {
    connect(mQuestionTimer, &QuestionTimer::timeout, this,
            [this] { handleResponse("Time's up"); });
    mainLayout->addWidget(mQuestionTimer);
  }

  // --- Zone principale : question (gauche) | mascotte + bulle (droite) ---
  auto *contentRow = new QHBoxLayout();
  contentRow->setSpacing(20);

  // Colonne gauche : feedback (si mascotte désactivée) + question + réponses
  mQuestionAreaLayout = new QVBoxLayout();
  mQuestionAreaLayout->setSpacing(10);

  mFeedbackLabel = new QLabel();
  mFeedbackLabel->setWordWrap(true);
  mFeedbackLabel->setAlignment(Qt::AlignCenter);
  mFeedbackLabel->setStyleSheet("font-size: 14px; padding: 8px 12px; border-radius: 6px;");
  mFeedbackLabel->hide();
  mQuestionAreaLayout->addWidget(mFeedbackLabel);

  contentRow->addLayout(mQuestionAreaLayout, 1);

  // Colonne droite : bulle de dialogue + mascotte
  auto *mascotArea = new QVBoxLayout();
  mascotArea->setSpacing(4);
  mascotArea->setAlignment(Qt::AlignTop | Qt::AlignHCenter);

  mSpeechBubble = new SpeechBubble();
  mSpeechBubble->setMinimumWidth(160);
  mascotArea->addWidget(mSpeechBubble, 0, Qt::AlignHCenter);

  mMascot = new Mascot();
  mMascot->setSkin(mSkinManager.selectedSkin());
  mascotArea->addWidget(mMascot, 0, Qt::AlignHCenter);

  const bool mascotVisible = SettingsDialog::mascotEnabled();
  mMascot->setVisible(mascotVisible);
  mSpeechBubble->setVisible(false); // toujours caché au départ

  if (mascotVisible && SettingsDialog::musicEnabled())
    mMascot->startRotation();

  contentRow->addLayout(mascotArea);
  mainLayout->addLayout(contentRow, 1);

  setLayout(mainLayout);

  nextInterrogation(mQuestionGenerator.generate(mConfig.difficulty));
}

void GamePage::nextInterrogation(const data::Interrogation &interrogation) {
  // Mémoriser la bonne réponse pour le feedback sans mascotte
  mCorrectAnswerText.clear();
  for (const auto &answer : interrogation.availableAnswers()) {
    if (answer.second == "Correct") {
      mCorrectAnswerText = QString::fromStdString(answer.first);
      break;
    }
  }

  if (mInterrogation) {
    mQuestionAreaLayout->removeWidget(mInterrogation);
    delete mInterrogation;
    mInterrogation = nullptr;
  }
  mInterrogation = new Interrogation(interrogation);
  connect(mInterrogation, &Interrogation::responseSelected, this,
          [this](data::Response r) { handleResponse(r); });
  mQuestionAreaLayout->addWidget(mInterrogation);

  if (mConfig.hasTimer)
    mQuestionTimer->start();
}

void GamePage::showResult(const data::Result &result) {
  if (mMascot->isVisible()) {
    mSpeechBubble->setText(QString::fromStdString(result.message()),
                           result.isSuccess());
    return;
  }

  // Mascotte désactivée : afficher un bandeau de feedback
  QString text = QString::fromStdString(result.message());
  if (!result.isSuccess() && !mCorrectAnswerText.isEmpty())
    text += QString("\nLa bonne réponse était : %1").arg(mCorrectAnswerText);

  mFeedbackLabel->setText(text);
  mFeedbackLabel->setStyleSheet(
      result.isSuccess()
          ? "font-size: 14px; padding: 8px 12px; border-radius: 6px; "
            "background-color: #e8f5e9; color: #2e7d32; border: 1px solid #a5d6a7;"
          : "font-size: 14px; padding: 8px 12px; border-radius: 6px; "
            "background-color: #ffebee; color: #c62828; border: 1px solid #ef9a9a;");
  mFeedbackLabel->show();
}

void GamePage::refreshScoreDisplay() {
  mScoreRow->removeWidget(mScoreDisplay);
  delete mScoreDisplay;
  mScoreDisplay = new ScoreDisplay(mScore);
  mScoreRow->insertWidget(0, mScoreDisplay);
}

void GamePage::handleResponse(const data::Response &response) {
  if (mConfig.hasTimer)
    mQuestionTimer->stop();

  if (response == "Correct") {
    mScore.recordSuccess();
    mExperience.recordCorrectAnswer(mConfig.difficulty);
    showResult({data::Result::Status::Success, "Bravo !"});
  } else {
    mScore.recordFailure();
    mExperience.recordWrongAnswer();
    if (response == "I don't know")
      showResult({data::Result::Status::Failure, "Tu y arriveras !"});
    else if (response == "Time's up")
      showResult({data::Result::Status::Failure, "Temps écoulé !"});
    else
      showResult({data::Result::Status::Failure, "Non, ce n'est pas ça !"});
  }

  mExperienceBar->update(mExperience);
  refreshScoreDisplay();

  if (mConfig.questionCount > 0) {
    --mQuestionsRemaining;
    if (mCountLabel)
      mCountLabel->setText(
          QString("Questions restantes : %1").arg(mQuestionsRemaining));
    if (mQuestionsRemaining <= 0) {
      mExperience.save();
      emit backToHome();
      return;
    }
  }

  nextInterrogation(mQuestionGenerator.generate(mConfig.difficulty));
}

} // namespace NomCool::gui

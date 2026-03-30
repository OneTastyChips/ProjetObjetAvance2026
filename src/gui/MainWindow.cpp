
#include "MainWindow.hpp"

#include <gui/DifficultySelector.hpp>
#include <gui/Interrogation.hpp>
#include <gui/MascotManager.hpp>
#include <gui/ScoreDisplay.hpp>

#include <data/Interrogation.hpp>

#include <QVBoxLayout>

// Debug
#include <QPushButton>
// End debug

namespace NomCool::gui {

MainWindow::MainWindow() {
  mExperience.load();
  mMainLayout = new QGridLayout();

  auto *difficultySelector = new DifficultySelector();
  connect(difficultySelector, &DifficultySelector::difficultyChanged, this,
          [this](data::Difficulty difficulty) {
            mDifficulty = difficulty;
            setInterrogation(mQuestionGenerator.generate(mDifficulty));
          });
  if (mExperience.isHardUnlocked()) {
    difficultySelector->unlockHard();
  }
  mMainLayout->addWidget(difficultySelector, mMainLayout->rowCount(), 0);

  mExperienceBar = new ExperienceBar();
  mExperienceBar->update(mExperience);
  connect(mExperienceBar, &ExperienceBar::hardUnlocked, difficultySelector,
          &DifficultySelector::unlockHard);
  mMainLayout->addWidget(mExperienceBar, mMainLayout->rowCount(), 0);

  // Debug
  auto *randomQuestion = new QPushButton("Random question");
  connect(randomQuestion, &QPushButton::clicked, this,
          [this] { setInterrogation(mQuestionGenerator.generate(mDifficulty)); });
  mMainLayout->addWidget(randomQuestion, mMainLayout->rowCount(), 0);
  connect(this, &MainWindow::responseSelected, this,
          [this](data::Response response) {
            mQuestionTimer->stop();
            if (response == "Correct") {
              mScore.recordSuccess();
              mExperience.recordCorrectAnswer(mDifficulty);
              setPreviousResult({data::Result::Status::Success, "Well done!"});
            } else {
              mScore.recordFailure();
              mExperience.recordWrongAnswer();
              if (response == "I don't know") {
                setPreviousResult({data::Result::Status::Failure,
                                   "You will get it next time!"});
              } else if (response == "Time's up") {
                setPreviousResult(
                    {data::Result::Status::Failure, "Time's up!"});
              } else {
                setPreviousResult(
                    {data::Result::Status::Failure, "No, it's not that one!"});
              }
            }
            mExperienceBar->update(mExperience);
            setScoreDisplay(mScore);
            setInterrogation(mQuestionGenerator.generate(mDifficulty));
          });
  // End debug

  mQuestionTimer = new QuestionTimer();
  connect(mQuestionTimer, &QuestionTimer::timeout, this,
          [this] { emit responseSelected("Time's up"); });
  mMainLayout->addWidget(mQuestionTimer, mMainLayout->rowCount(), 0);

  auto *pauseButton = new QPushButton("Pause");
  connect(pauseButton, &QPushButton::clicked, this,
          [this, pauseButton] {
            if (mQuestionTimer->isPaused()) {
              mQuestionTimer->resume();
              if (mInterrogation)
                mInterrogation->show();
              pauseButton->setText("Pause");
            } else {
              mQuestionTimer->pause();
              if (mInterrogation)
                mInterrogation->hide();
              pauseButton->setText("Resume");
            }
          });
  mMainLayout->addWidget(pauseButton, mMainLayout->rowCount(), 0);

  mScoreDisplayPosition = {mMainLayout->rowCount(), 0};
  setScoreDisplay(mScore);

  // This row is reserved for the previous result widget
  // The next one should be added at the mPreviousResultPosition.first + 1
  mPreviousResultPosition = {mMainLayout->rowCount(), 0};

  // This row is reserved for the interrogation widget
  // The next one should be added at the mInterrogationPosition.first + 1
  mInterrogationPosition = {mPreviousResultPosition.first + 1, 0};

  // Debug
  // Quit button
  auto *quitButton = new QPushButton("Quit");
  connect(quitButton, &QPushButton::clicked, this, &MainWindow::close);
  mMainLayout->addWidget(quitButton, mInterrogationPosition.first + 1, 0);
  // End debug
  mMascotManager = new MascotManager(mSkinManager, mExperience);
  mMainLayout->addWidget(mMascotManager, 0, 1, mMainLayout->rowCount() + 1, 1);

  auto *centralWidget = new QWidget();
  centralWidget->setLayout(mMainLayout);
  setCentralWidget(centralWidget);
}

void MainWindow::setInterrogation(const data::Interrogation &interrogation) {
  if (mInterrogation) {
    mMainLayout->removeWidget(mInterrogation);
    delete mInterrogation;
  }
  mInterrogation = new Interrogation(interrogation);
  connect(mInterrogation, &Interrogation::responseSelected, this,
          &MainWindow::responseSelected);
  mMainLayout->addWidget(mInterrogation, mInterrogationPosition.first,
                         mInterrogationPosition.second);

  mQuestionTimer->start();
}

void MainWindow::setScoreDisplay(const data::Score &score) {
  if (mScoreDisplay) {
    mMainLayout->removeWidget(mScoreDisplay);
    delete mScoreDisplay;
  }
  mScoreDisplay = new ScoreDisplay(score);
  mMainLayout->addWidget(mScoreDisplay, mScoreDisplayPosition.first,
                         mScoreDisplayPosition.second);
}

void MainWindow::setPreviousResult(const data::Result &result) {
  if (mPreviousResult) {
    mMainLayout->removeWidget(mPreviousResult);
    delete mPreviousResult;
  }
  mPreviousResult = new PreviousResult(result);
  mMainLayout->addWidget(mPreviousResult, mPreviousResultPosition.first,
                         mPreviousResultPosition.second);
}

} // namespace NomCool::gui

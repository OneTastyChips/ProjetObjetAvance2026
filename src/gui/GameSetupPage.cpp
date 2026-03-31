
#include "GameSetupPage.hpp"

#include <QButtonGroup>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

namespace NomCool::gui {

GameSetupPage::GameSetupPage(bool hardUnlocked, QWidget *parent)
    : QWidget(parent) {
  auto *mainLayout = new QVBoxLayout();
  mainLayout->setContentsMargins(40, 30, 40, 30);
  mainLayout->setSpacing(20);

  // Titre
  auto *title = new QLabel("Configuration de la partie");
  title->setStyleSheet("font-size: 22px; font-weight: bold;");
  title->setAlignment(Qt::AlignCenter);
  mainLayout->addWidget(title);

  // --- Difficulté ---
  auto *difficultyGroup = new QGroupBox("Difficulté");
  auto *difficultyLayout = new QHBoxLayout();
  mEasyButton = new QRadioButton("Facile");
  mNormalButton = new QRadioButton("Normal");
  mHardButton = new QRadioButton("Difficile");
  if (!hardUnlocked)
    mHardButton->setEnabled(false);
  mNormalButton->setChecked(true);
  auto *diffBtnGroup = new QButtonGroup(this);
  diffBtnGroup->addButton(mEasyButton);
  diffBtnGroup->addButton(mNormalButton);
  diffBtnGroup->addButton(mHardButton);
  difficultyLayout->addWidget(mEasyButton);
  difficultyLayout->addWidget(mNormalButton);
  difficultyLayout->addWidget(mHardButton);
  difficultyGroup->setLayout(difficultyLayout);
  mainLayout->addWidget(difficultyGroup);

  // --- Chronomètre ---
  auto *timerGroup = new QGroupBox("Chronomètre");
  auto *timerLayout = new QHBoxLayout();
  mTimerOnButton = new QRadioButton("Activé");
  mTimerOffButton = new QRadioButton("Désactivé");
  mTimerOnButton->setChecked(true);
  auto *timerBtnGroup = new QButtonGroup(this);
  timerBtnGroup->addButton(mTimerOnButton);
  timerBtnGroup->addButton(mTimerOffButton);
  timerLayout->addWidget(mTimerOnButton);
  timerLayout->addWidget(mTimerOffButton);
  timerGroup->setLayout(timerLayout);
  mainLayout->addWidget(timerGroup);

  // --- Nombre de questions ---
  auto *countGroup = new QGroupBox("Nombre de questions");
  auto *countLayout = new QVBoxLayout();
  mInfiniteButton = new QRadioButton("Infini");
  mFixedButton = new QRadioButton("Nombre défini :");
  mInfiniteButton->setChecked(true);
  auto *countBtnGroup = new QButtonGroup(this);
  countBtnGroup->addButton(mInfiniteButton);
  countBtnGroup->addButton(mFixedButton);
  mQuestionCountSpinBox = new QSpinBox();
  mQuestionCountSpinBox->setMinimum(1);
  mQuestionCountSpinBox->setMaximum(999);
  mQuestionCountSpinBox->setValue(10);
  mQuestionCountSpinBox->setEnabled(false);
  connect(mFixedButton, &QRadioButton::toggled, mQuestionCountSpinBox,
          &QSpinBox::setEnabled);
  auto *countRow = new QHBoxLayout();
  countRow->addWidget(mFixedButton);
  countRow->addWidget(mQuestionCountSpinBox);
  countLayout->addWidget(mInfiniteButton);
  countLayout->addLayout(countRow);
  countGroup->setLayout(countLayout);
  mainLayout->addWidget(countGroup);

  mainLayout->addStretch();

  // --- Boutons ---
  auto *buttonLayout = new QHBoxLayout();

  auto *backButton = new QPushButton("Retour");
  backButton->setMinimumHeight(40);
  connect(backButton, &QPushButton::clicked, this,
          &GameSetupPage::backClicked);

  auto *startButton = new QPushButton("Commencer !");
  startButton->setMinimumHeight(40);
  startButton->setStyleSheet(
      "font-weight: bold; background-color: #4CAF50; "
      "color: white; border-radius: 6px;");
  connect(startButton, &QPushButton::clicked, this, [this] {
    data::GameConfig config;
    if (mEasyButton->isChecked())
      config.difficulty = data::Difficulty::Easy;
    else if (mHardButton->isChecked())
      config.difficulty = data::Difficulty::Hard;
    else
      config.difficulty = data::Difficulty::Normal;
    config.hasTimer = mTimerOnButton->isChecked();
    config.questionCount =
        mFixedButton->isChecked() ? mQuestionCountSpinBox->value() : -1;
    emit startGame(config);
  });

  buttonLayout->addWidget(backButton);
  buttonLayout->addWidget(startButton);
  mainLayout->addLayout(buttonLayout);

  setLayout(mainLayout);
}

void GameSetupPage::unlockHard() {
  mHardButton->setEnabled(true);
}

} // namespace NomCool::gui

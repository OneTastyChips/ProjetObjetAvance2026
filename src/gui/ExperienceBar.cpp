
#include "ExperienceBar.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>

namespace NomCool::gui {

ExperienceBar::ExperienceBar() {
  auto *layout = new QVBoxLayout();

  auto *topRow = new QHBoxLayout();
  mLevelLabel = new QLabel("Niveau 1");
  mLevelLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
  topRow->addWidget(mLevelLabel);

  mGoldLabel = new QLabel("Or : 0");
  mGoldLabel->setStyleSheet(
      "font-weight: bold; font-size: 14px; color: #DAA520;");
  topRow->addWidget(mGoldLabel);

  mStreakLabel = new QLabel();
  mStreakLabel->setStyleSheet("color: orange; font-weight: bold;");
  topRow->addWidget(mStreakLabel);
  topRow->addStretch();

  layout->addLayout(topRow);

  mXPBar = new QProgressBar();
  mXPBar->setTextVisible(true);
  mXPBar->setFormat("%v / %m XP");
  mXPBar->setStyleSheet(
      "QProgressBar { border: 1px solid grey; border-radius: 3px; "
      "text-align: center; } "
      "QProgressBar::chunk { background-color: #4CAF50; }");
  layout->addWidget(mXPBar);

  mUnlockLabel = new QLabel();
  mUnlockLabel->setStyleSheet("color: #4CAF50; font-style: italic;");
  mUnlockLabel->hide();
  layout->addWidget(mUnlockLabel);

  setLayout(layout);
}

void ExperienceBar::update(const data::Experience &experience) {
  mLevelLabel->setText(
      QString("Niveau %1").arg(experience.level()));

  mGoldLabel->setText(QString("Or : %1").arg(experience.gold()));

  mXPBar->setMaximum(experience.xpForNextLevel());
  mXPBar->setValue(experience.xpInCurrentLevel());

  if (experience.streak() >= 2) {
    mStreakLabel->setText(QString("Serie x%1 !").arg(experience.streak()));
    mStreakLabel->show();
  } else {
    mStreakLabel->hide();
  }

  if (experience.isHardUnlocked() && !mHardWasUnlocked) {
    mHardWasUnlocked = true;
    mUnlockLabel->setText("Niveau 2 ! Mode difficile debloque !");
    mUnlockLabel->show();
    emit hardUnlocked();
  }
}

} // namespace NomCool::gui

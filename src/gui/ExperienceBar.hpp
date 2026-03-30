
#pragma once

#include <QLabel>
#include <QProgressBar>
#include <QWidget>

#include <data/Experience.hpp>

namespace NomCool::gui {

class ExperienceBar : public QWidget {
  Q_OBJECT

public:
  ExperienceBar();

  void update(const data::Experience &experience);

Q_SIGNALS:
  void hardUnlocked();

private:
  QLabel *mLevelLabel = nullptr;
  QLabel *mGoldLabel = nullptr;
  QProgressBar *mXPBar = nullptr;
  QLabel *mStreakLabel = nullptr;
  QLabel *mUnlockLabel = nullptr;
  bool mHardWasUnlocked = false;
};

} // namespace NomCool::gui

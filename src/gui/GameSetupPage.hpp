
#pragma once

#include <QRadioButton>
#include <QSpinBox>
#include <QWidget>

#include <data/GameConfig.hpp>

namespace NomCool::gui {

class GameSetupPage : public QWidget {
  Q_OBJECT

public:
  explicit GameSetupPage(bool hardUnlocked, QWidget *parent = nullptr);

  void unlockHard();

Q_SIGNALS:
  void startGame(data::GameConfig config);
  void backClicked();

private:
  QRadioButton *mEasyButton = nullptr;
  QRadioButton *mNormalButton = nullptr;
  QRadioButton *mHardButton = nullptr;
  QRadioButton *mTimerOnButton = nullptr;
  QRadioButton *mTimerOffButton = nullptr;
  QRadioButton *mInfiniteButton = nullptr;
  QRadioButton *mFixedButton = nullptr;
  QSpinBox *mQuestionCountSpinBox = nullptr;
};

} // namespace NomCool::gui

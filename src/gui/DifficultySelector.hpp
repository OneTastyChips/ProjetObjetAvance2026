
#pragma once

#include <QAbstractButton>
#include <QWidget>

#include <data/Difficulty.hpp>

namespace NomCool::gui {

class DifficultySelector : public QWidget {
  Q_OBJECT

public:
  DifficultySelector();

  void unlockHard();

Q_SIGNALS:
  void difficultyChanged(data::Difficulty difficulty);

private:
  QAbstractButton *mHardButton = nullptr;
};

} // namespace NomCool::gui


#pragma once

#include <QWidget>

#include <data/Difficulty.hpp>

namespace NomCool::gui {

class DifficultySelector : public QWidget {
  Q_OBJECT

public:
  DifficultySelector();

Q_SIGNALS:
  void difficultyChanged(data::Difficulty difficulty);
};

} // namespace NomCool::gui

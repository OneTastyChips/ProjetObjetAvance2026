
#pragma once

#include <QWidget>

#include <data/Score.hpp>

namespace NomCool::gui {

class ScoreDisplay : public QWidget {
  Q_OBJECT

public:
  ScoreDisplay(const data::Score &score);
};

} // namespace NomCool::gui

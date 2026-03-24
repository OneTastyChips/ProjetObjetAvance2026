
#include "ScoreDisplay.hpp"

#include <QHBoxLayout>
#include <QLabel>

namespace NomCool::gui {

ScoreDisplay::ScoreDisplay(const data::Score &score) {
  auto *layout = new QHBoxLayout();
  auto *label = new QLabel(
      QString("Score: %1 / %2").arg(score.correct()).arg(score.total()));
  layout->addWidget(label);
  setLayout(layout);
}

} // namespace NomCool::gui

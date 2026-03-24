
#include "DifficultySelector.hpp"

#include <QButtonGroup>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>

namespace NomCool::gui {

DifficultySelector::DifficultySelector() {
  auto *layout = new QHBoxLayout();
  layout->addWidget(new QLabel("Difficulty:"));

  auto *group = new QButtonGroup(this);
  auto *easy = new QRadioButton("Easy");
  auto *normal = new QRadioButton("Normal");
  auto *hard = new QRadioButton("Hard");
  normal->setChecked(true);

  group->addButton(easy, static_cast<int>(data::Difficulty::Easy));
  group->addButton(normal, static_cast<int>(data::Difficulty::Normal));
  group->addButton(hard, static_cast<int>(data::Difficulty::Hard));

  layout->addWidget(easy);
  layout->addWidget(normal);
  layout->addWidget(hard);
  setLayout(layout);

  connect(group, &QButtonGroup::idClicked, this, [this](int id) {
    emit difficultyChanged(static_cast<data::Difficulty>(id));
  });
}

} // namespace NomCool::gui

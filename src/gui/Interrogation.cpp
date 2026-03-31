
#include "Interrogation.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

namespace NomCool::gui {

Interrogation::Interrogation(const data::Interrogation &interrogation) {
  auto *mainLayout = new QVBoxLayout();
  auto *questionLabel = new QLabel();
  questionLabel->setText(QString::fromStdString(interrogation.question()));
  questionLabel->setAlignment(Qt::AlignCenter);
  questionLabel->setStyleSheet("font-size: 24px; font-weight: bold; padding: 10px;");
  mainLayout->addWidget(questionLabel);
  auto *solutionLayout = new QHBoxLayout();
  for (const auto &proposedAnswer : interrogation.availableAnswers()) {
    auto *button =
        new QPushButton(QString::fromStdString(proposedAnswer.first));
    button->setMinimumHeight(40);
    connect(button, &QPushButton::clicked, this, [this, proposedAnswer] {
      emit responseSelected(proposedAnswer.second);
    });
    solutionLayout->addWidget(button);
  }
  mainLayout->addLayout(solutionLayout);
  setLayout(mainLayout);
}

} // namespace NomCool::gui

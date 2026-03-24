
#include "Mascot.hpp"

#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>

namespace NomCool::gui {

Mascot::Mascot() {
  auto *layout = new QVBoxLayout();
  auto *imageLabel = new QLabel();
  QPixmap pixmap(":/mascot/mascot.png");
  imageLabel->setPixmap(pixmap.scaledToHeight(200, Qt::SmoothTransformation));
  imageLabel->setAlignment(Qt::AlignCenter);
  layout->addWidget(imageLabel);
  setLayout(layout);
}

} // namespace NomCool::gui

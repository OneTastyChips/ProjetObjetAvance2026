
#include "Mascot.hpp"

#include <QGraphicsColorizeEffect>
#include <QPixmap>
#include <QVBoxLayout>

namespace NomCool::gui {

Mascot::Mascot() {
  auto *layout = new QVBoxLayout();
  mImageLabel = new QLabel();
  QPixmap pixmap(":/mascot/mascot.png");
  mImageLabel->setPixmap(
      pixmap.scaledToHeight(200, Qt::SmoothTransformation));
  mImageLabel->setAlignment(Qt::AlignCenter);
  layout->addWidget(mImageLabel);
  setLayout(layout);
}

void Mascot::setSkin(const data::Skin &skin) {
  if (skin.tint.alpha() == 0) {
    mImageLabel->setGraphicsEffect(nullptr);
  } else {
    auto *effect = new QGraphicsColorizeEffect();
    effect->setColor(skin.tint);
    effect->setStrength(0.5);
    mImageLabel->setGraphicsEffect(effect);
  }
}

} // namespace NomCool::gui


#include "Mascot.hpp"

#include <QPainter>
#include <QGraphicsColorizeEffect>
#include <QVBoxLayout>

namespace NomCool::gui {

Mascot::Mascot() {
  auto *layout = new QVBoxLayout();
  mImageLabel = new QLabel();
  QPixmap pixmap(":/mascot/mascot.png");
  mBasePixmap = pixmap.scaledToHeight(200, Qt::SmoothTransformation);
  mImageLabel->setPixmap(mBasePixmap);
  mImageLabel->setAlignment(Qt::AlignCenter);
  layout->addWidget(mImageLabel);
  setLayout(layout);

  mRotTimer = new QTimer(this);
  mRotTimer->setInterval(30);
  connect(mRotTimer, &QTimer::timeout, this, &Mascot::onRotationTick);
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

void Mascot::startRotation() {
  mRotAngle = 0.0;
  mRotTimer->start();
}

void Mascot::stopRotation() {
  mRotTimer->stop();
  mRotAngle = 0.0;
  mImageLabel->setPixmap(mBasePixmap);
}

void Mascot::onRotationTick() {
  mRotAngle = std::fmod(mRotAngle + 54.0, 360.0);

  QPixmap canvas(mBasePixmap.size());
  canvas.fill(Qt::transparent);
  QPainter p(&canvas);
  p.setRenderHint(QPainter::Antialiasing);
  p.setRenderHint(QPainter::SmoothPixmapTransform);
  p.translate(canvas.width() / 2.0, canvas.height() / 2.0);
  p.rotate(mRotAngle);
  p.drawPixmap(-mBasePixmap.width() / 2, -mBasePixmap.height() / 2,
               mBasePixmap);
  mImageLabel->setPixmap(canvas);
}

} // namespace NomCool::gui

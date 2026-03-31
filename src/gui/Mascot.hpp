
#pragma once

#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QWidget>

#include <data/Skin.hpp>

namespace NomCool::gui {

class Mascot : public QWidget {
  Q_OBJECT

public:
  Mascot();

  void setSkin(const data::Skin &skin);
  void startRotation();
  void stopRotation();

private slots:
  void onRotationTick();

private:
  QLabel *mImageLabel = nullptr;
  QPixmap mBasePixmap;
  QTimer *mRotTimer = nullptr;
  qreal mRotAngle = 0.0;
};

} // namespace NomCool::gui

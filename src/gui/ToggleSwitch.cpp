
#include "ToggleSwitch.hpp"

#include <QPainter>

namespace NomCool::gui {

ToggleSwitch::ToggleSwitch(QWidget *parent) : QAbstractButton(parent) {
  setCheckable(true);
  setFixedSize(W, H);
  setCursor(Qt::PointingHandCursor);
}

QSize ToggleSwitch::sizeHint() const { return QSize(W, H); }

void ToggleSwitch::paintEvent(QPaintEvent *) {
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);

  // Fond
  QColor bg = isChecked() ? QColor(76, 175, 80) : QColor(180, 180, 180);
  p.setBrush(bg);
  p.setPen(Qt::NoPen);
  p.drawRoundedRect(0, 0, W, H, H / 2, H / 2);

  // Cercle blanc
  int margin = (H - CIRCLE) / 2;
  int x = isChecked() ? W - margin - CIRCLE : margin;
  p.setBrush(Qt::white);
  p.drawEllipse(x, margin, CIRCLE, CIRCLE);
}

} // namespace NomCool::gui

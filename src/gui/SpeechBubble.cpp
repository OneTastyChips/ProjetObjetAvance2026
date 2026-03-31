
#include "SpeechBubble.hpp"

#include <QPainter>
#include <QPainterPath>
#include <QVBoxLayout>

namespace NomCool::gui {

SpeechBubble::SpeechBubble(QWidget *parent) : QWidget(parent) {
  setAttribute(Qt::WA_TranslucentBackground);
  auto *layout = new QVBoxLayout(this);
  layout->setContentsMargins(PADDING, PADDING, PADDING, PADDING + TAIL_SIZE);
  mLabel = new QLabel(this);
  mLabel->setWordWrap(true);
  mLabel->setAlignment(Qt::AlignCenter);
  mLabel->setStyleSheet("font-size: 14px; font-weight: bold; "
                        "background: transparent;");
  layout->addWidget(mLabel);
  hide();
}

void SpeechBubble::setText(const QString &text, bool success) {
  mSuccess = success;
  mLabel->setText(text);
  show();
  update();
}

void SpeechBubble::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  int w = width();
  int bh = height() - TAIL_SIZE;
  int cx = w / 2;

  QColor fill = mSuccess ? QColor(230, 255, 230) : QColor(255, 230, 230);
  QColor border = mSuccess ? QColor(100, 180, 100) : QColor(200, 80, 80);

  // Bulle + queue en un seul chemin
  QPainterPath path;
  path.moveTo(RADIUS, 1);
  path.lineTo(w - RADIUS, 1);
  path.quadTo(w - 1, 1, w - 1, RADIUS);
  path.lineTo(w - 1, bh - RADIUS);
  path.quadTo(w - 1, bh - 1, w - RADIUS, bh - 1);
  path.lineTo(cx + 9, bh - 1);
  path.lineTo(cx, bh + TAIL_SIZE - 2);
  path.lineTo(cx - 9, bh - 1);
  path.lineTo(RADIUS, bh - 1);
  path.quadTo(1, bh - 1, 1, bh - RADIUS);
  path.lineTo(1, RADIUS);
  path.quadTo(1, 1, RADIUS, 1);
  path.closeSubpath();

  painter.setBrush(fill);
  painter.setPen(QPen(border, 1.5));
  painter.drawPath(path);
}

} // namespace NomCool::gui

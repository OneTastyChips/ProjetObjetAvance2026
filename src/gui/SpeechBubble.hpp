
#pragma once

#include <QLabel>
#include <QWidget>

namespace NomCool::gui {

class SpeechBubble : public QWidget {
  Q_OBJECT

public:
  explicit SpeechBubble(QWidget *parent = nullptr);

  void setText(const QString &text, bool success);

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  static constexpr int TAIL_SIZE = 14;
  static constexpr int RADIUS = 12;
  static constexpr int PADDING = 12;

  QLabel *mLabel = nullptr;
  bool mSuccess = true;
};

} // namespace NomCool::gui


#pragma once

#include <QAbstractButton>

namespace NomCool::gui {

class ToggleSwitch : public QAbstractButton {
  Q_OBJECT

public:
  explicit ToggleSwitch(QWidget *parent = nullptr);
  QSize sizeHint() const override;

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  static constexpr int W = 52;
  static constexpr int H = 28;
  static constexpr int CIRCLE = 22;
};

} // namespace NomCool::gui

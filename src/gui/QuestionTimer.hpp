
#pragma once

#include <QProgressBar>
#include <QTimer>
#include <QWidget>

namespace NomCool::gui {

class QuestionTimer : public QWidget {
  Q_OBJECT

public:
  QuestionTimer();

  void start();
  void stop();
  void pause();
  void resume();
  bool isPaused() const;

Q_SIGNALS:
  void timeout();

private:
  static constexpr int TIMER_STEPS = 100;
  static constexpr int TIMER_INTERVAL_MS = 100;

  QProgressBar *mBar = nullptr;
  QTimer *mTimer = nullptr;
  bool mPaused = false;
};

} // namespace NomCool::gui

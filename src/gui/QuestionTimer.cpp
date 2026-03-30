
#include "QuestionTimer.hpp"

#include <QVBoxLayout>

namespace NomCool::gui {

QuestionTimer::QuestionTimer() {
  mBar = new QProgressBar();
  mBar->setRange(0, TIMER_STEPS);
  mBar->setValue(TIMER_STEPS);
  mBar->setTextVisible(false);

  mTimer = new QTimer(this);
  mTimer->setInterval(TIMER_INTERVAL_MS);
  connect(mTimer, &QTimer::timeout, this, [this] {
    mBar->setValue(mBar->value() - 1);
    if (mBar->value() == 0) {
      mTimer->stop();
      emit timeout();
    }
  });

  auto *layout = new QVBoxLayout();
  layout->addWidget(mBar);
  setLayout(layout);
}

void QuestionTimer::start() {
  mPaused = false;
  mBar->setValue(TIMER_STEPS);
  mTimer->start();
}

void QuestionTimer::stop() {
  mPaused = false;
  mTimer->stop();
}

void QuestionTimer::pause() {
  if (mTimer->isActive()) {
    mPaused = true;
    mTimer->stop();
  }
}

void QuestionTimer::resume() {
  if (mPaused) {
    mPaused = false;
    mTimer->start();
  }
}

bool QuestionTimer::isPaused() const { return mPaused; }

} // namespace NomCool::gui

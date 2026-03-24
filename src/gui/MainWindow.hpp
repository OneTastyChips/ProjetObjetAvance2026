
#pragma once

#include <QMainWindow>

#include <gui/DifficultySelector.hpp>
#include <gui/Interrogation.hpp>
#include <gui/PreviousResult.hpp>
#include <gui/QuestionTimer.hpp>
#include <gui/ScoreDisplay.hpp>

#include <QGridLayout>
#include <QLabel>

#include <data/Difficulty.hpp>
#include <data/QuestionGenerator.hpp>
#include <data/Score.hpp>

namespace NomCool::data {
class Interrogation;
} // namespace NomCool::data

namespace NomCool::gui {

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow();

  void setInterrogation(const data::Interrogation &interrogation);
  void setPreviousResult(const data::Result &result);
  void setScoreDisplay(const data::Score &score);

Q_SIGNALS:
  void responseSelected(data::Response response);

private:
  QGridLayout *mMainLayout = nullptr;
  QuestionTimer *mQuestionTimer = nullptr;
  std::pair<int, int> mScoreDisplayPosition;
  ScoreDisplay *mScoreDisplay = nullptr;
  std::pair<int, int> mPreviousResultPosition;
  PreviousResult *mPreviousResult = nullptr;
  std::pair<int, int> mInterrogationPosition;
  Interrogation *mInterrogation = nullptr;
  data::Score mScore;
  data::Difficulty mDifficulty = data::Difficulty::Normal;
  data::QuestionGenerator mQuestionGenerator;
};

} // namespace NomCool::gui

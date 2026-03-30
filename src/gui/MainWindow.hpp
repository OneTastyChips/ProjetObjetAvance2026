
#pragma once

#include <QMainWindow>

#include <gui/DifficultySelector.hpp>
#include <gui/ExperienceBar.hpp>
#include <gui/Interrogation.hpp>
#include <gui/MascotManager.hpp>
#include <gui/PreviousResult.hpp>
#include <gui/QuestionTimer.hpp>
#include <gui/ScoreDisplay.hpp>

#include <QGridLayout>
#include <QLabel>

#include <data/Difficulty.hpp>
#include <data/Experience.hpp>
#include <data/QuestionGenerator.hpp>
#include <data/Score.hpp>
#include <data/SkinManager.hpp>

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
  data::Experience mExperience;
  data::SkinManager mSkinManager;
  ExperienceBar *mExperienceBar = nullptr;
  MascotManager *mMascotManager = nullptr;
};

} // namespace NomCool::gui

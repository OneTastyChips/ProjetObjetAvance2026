
#pragma once

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include <data/Experience.hpp>
#include <data/GameConfig.hpp>
#include <data/QuestionGenerator.hpp>
#include <data/Result.hpp>
#include <data/Score.hpp>
#include <data/SkinManager.hpp>
#include <gui/ExperienceBar.hpp>
#include <gui/Interrogation.hpp>
#include <gui/Mascot.hpp>
#include <gui/QuestionTimer.hpp>
#include <gui/ScoreDisplay.hpp>
#include <gui/SpeechBubble.hpp>

namespace NomCool::data {
class Interrogation;
} // namespace NomCool::data

namespace NomCool::gui {

class GamePage : public QWidget {
  Q_OBJECT

public:
  GamePage(data::Experience &experience, data::SkinManager &skinManager,
           data::QuestionGenerator &questionGenerator,
           const data::GameConfig &config, QWidget *parent = nullptr);

Q_SIGNALS:
  void backToHome();

private:
  void nextInterrogation(const data::Interrogation &interrogation);
  void showResult(const data::Result &result);
  void refreshScoreDisplay();
  void handleResponse(const data::Response &response);

  data::Experience &mExperience;
  data::SkinManager &mSkinManager;
  data::QuestionGenerator &mQuestionGenerator;
  data::GameConfig mConfig;
  data::Score mScore;
  int mQuestionsRemaining;

  QVBoxLayout *mQuestionAreaLayout = nullptr;
  QHBoxLayout *mScoreRow = nullptr;
  QuestionTimer *mQuestionTimer = nullptr;
  ScoreDisplay *mScoreDisplay = nullptr;
  Interrogation *mInterrogation = nullptr;
  ExperienceBar *mExperienceBar = nullptr;
  QPushButton *mPauseButton = nullptr;
  QLabel *mCountLabel = nullptr;
  Mascot *mMascot = nullptr;
  SpeechBubble *mSpeechBubble = nullptr;
};

} // namespace NomCool::gui

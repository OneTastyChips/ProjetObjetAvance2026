
#pragma once

#include <QMainWindow>
#include <QStackedWidget>

#include <data/Experience.hpp>
#include <data/GameConfig.hpp>
#include <data/QuestionGenerator.hpp>
#include <data/SkinManager.hpp>
#include <gui/GamePage.hpp>
#include <gui/GameSetupPage.hpp>
#include <gui/HomePage.hpp>

namespace NomCool::gui {

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow();

private:
  void showHome();
  void showSetup();
  void startGame(const data::GameConfig &config);

  QStackedWidget *mStack = nullptr;
  HomePage *mHomePage = nullptr;
  GameSetupPage *mGameSetupPage = nullptr;
  GamePage *mGamePage = nullptr;

  data::Experience mExperience;
  data::SkinManager mSkinManager;
  data::QuestionGenerator mQuestionGenerator;
};

} // namespace NomCool::gui

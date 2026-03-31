
#include "MainWindow.hpp"

namespace NomCool::gui {

MainWindow::MainWindow() {
  mExperience.load();
  mSkinManager.load();

  mStack = new QStackedWidget();

  // Page d'accueil
  mHomePage = new HomePage(mExperience, mSkinManager);
  connect(mHomePage, &HomePage::playClicked, this, &MainWindow::showSetup);
  mStack->addWidget(mHomePage); // index 0

  // Page de configuration
  mGameSetupPage = new GameSetupPage(mExperience.isHardUnlocked());
  connect(mGameSetupPage, &GameSetupPage::backClicked, this,
          &MainWindow::showHome);
  connect(mGameSetupPage, &GameSetupPage::startGame, this,
          &MainWindow::startGame);
  mStack->addWidget(mGameSetupPage); // index 1

  setCentralWidget(mStack);
  showHome();
}

void MainWindow::showHome() {
  mHomePage->refresh();
  mStack->setCurrentWidget(mHomePage);
}

void MainWindow::showSetup() {
  if (mExperience.isHardUnlocked())
    mGameSetupPage->unlockHard();
  mStack->setCurrentWidget(mGameSetupPage);
}

void MainWindow::startGame(const data::GameConfig &config) {
  if (mGamePage) {
    mStack->removeWidget(mGamePage);
    delete mGamePage;
    mGamePage = nullptr;
  }
  mGamePage =
      new GamePage(mExperience, mSkinManager, mQuestionGenerator, config);
  connect(mGamePage, &GamePage::backToHome, this, [this] {
    mStack->removeWidget(mGamePage);
    delete mGamePage;
    mGamePage = nullptr;
    showHome();
  });
  mStack->addWidget(mGamePage);
  mStack->setCurrentWidget(mGamePage);
}

} // namespace NomCool::gui


#include "MainWindow.hpp"

#include <gui/SettingsDialog.hpp>

namespace NomCool::gui {

MainWindow::MainWindow() {
  mExperience.load();

  // Lecteur audio
  mMusicPlayer = new QMediaPlayer(this);
  mAudioOutput = new QAudioOutput(this);
  mMusicPlayer->setAudioOutput(mAudioOutput);
  mMusicPlayer->setSource(QUrl("qrc:/music/background.mp3"));
  mMusicPlayer->setLoops(QMediaPlayer::Infinite);
  mAudioOutput->setVolume(0.5f);

  mStack = new QStackedWidget();

  // Page d'accueil
  mHomePage = new HomePage(mExperience, mSkinManager);
  connect(mHomePage, &HomePage::playClicked, this, &MainWindow::showSetup);
  connect(mHomePage, &HomePage::musicToggled, this, &MainWindow::updateMusic);
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
  updateMusic(SettingsDialog::musicEnabled());
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

void MainWindow::updateMusic(bool enabled) {
  if (enabled) {
    if (mMusicPlayer->playbackState() != QMediaPlayer::PlayingState)
      mMusicPlayer->play();
  } else {
    mMusicPlayer->stop();
  }
}

} // namespace NomCool::gui


#include "HomePage.hpp"

#include <gui/ShopDialog.hpp>

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

namespace NomCool::gui {

HomePage::HomePage(data::Experience &experience, data::SkinManager &skinManager)
    : mExperience(experience), mSkinManager(skinManager) {
  auto *mainLayout = new QVBoxLayout();
  mainLayout->setContentsMargins(30, 20, 30, 30);
  mainLayout->setSpacing(20);

  // Barre XP + gold en haut
  mExperienceBar = new ExperienceBar();
  mExperienceBar->update(mExperience);
  mainLayout->addWidget(mExperienceBar);

  // Mascotte au centre
  mMascot = new Mascot();
  mMascot->setSkin(mSkinManager.selectedSkin());
  mainLayout->addWidget(mMascot, 0, Qt::AlignCenter);

  // Sélecteur de skin
  auto *skinRow = new QHBoxLayout();
  skinRow->setSpacing(8);
  auto *skinLabel = new QLabel("Skin :");
  skinLabel->setStyleSheet("font-weight: bold;");
  mSkinCombo = new QComboBox();
  rebuildSkinCombo();
  connect(mSkinCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
          this, [this](int comboIdx) {
            if (comboIdx < 0)
              return;
            int skinIdx = mSkinCombo->itemData(comboIdx).toInt();
            mSkinManager.selectSkin(skinIdx);
            mSkinManager.save();
            mMascot->setSkin(mSkinManager.selectedSkin());
          });
  skinRow->addStretch();
  skinRow->addWidget(skinLabel);
  skinRow->addWidget(mSkinCombo);
  skinRow->addStretch();
  mainLayout->addLayout(skinRow);

  mainLayout->addStretch();

  // Boutons principaux
  auto *buttonLayout = new QHBoxLayout();
  buttonLayout->setSpacing(15);

  auto *playButton = new QPushButton("Jouer");
  playButton->setMinimumHeight(50);
  playButton->setStyleSheet(
      "font-size: 18px; font-weight: bold; "
      "background-color: #4CAF50; color: white; border-radius: 8px;");
  connect(playButton, &QPushButton::clicked, this, &HomePage::playClicked);

  auto *shopButton = new QPushButton("Boutique");
  shopButton->setMinimumHeight(50);
  shopButton->setStyleSheet(
      "font-size: 18px; "
      "background-color: #DAA520; color: white; border-radius: 8px;");
  connect(shopButton, &QPushButton::clicked, this, [this] {
    auto *dialog = new ShopDialog(mSkinManager, mExperience, this);
    connect(dialog, &ShopDialog::skinPurchased, this, &HomePage::refresh);
    dialog->exec();
    refresh();
  });

  auto *settingsButton = new QPushButton("Paramètres");
  settingsButton->setMinimumHeight(50);
  settingsButton->setStyleSheet(
      "font-size: 18px; "
      "background-color: #757575; color: white; border-radius: 8px;");
  settingsButton->setEnabled(false);

  buttonLayout->addWidget(playButton);
  buttonLayout->addWidget(shopButton);
  buttonLayout->addWidget(settingsButton);
  mainLayout->addLayout(buttonLayout);

  // Bouton quitter
  auto *quitButton = new QPushButton("Quitter");
  quitButton->setMinimumHeight(35);
  quitButton->setStyleSheet(
      "font-size: 14px; background-color: #c0392b; "
      "color: white; border-radius: 6px;");
  connect(quitButton, &QPushButton::clicked, this,
          [] { QApplication::quit(); });
  mainLayout->addWidget(quitButton);

  setLayout(mainLayout);
}

void HomePage::rebuildSkinCombo() {
  mSkinCombo->blockSignals(true);
  mSkinCombo->clear();
  const auto &allSkins = mSkinManager.allSkins();
  for (int idx : mSkinManager.ownedSkinIndices()) {
    mSkinCombo->addItem(allSkins[idx].name, QVariant(idx));
  }
  int selected = mSkinManager.selectedSkinIndex();
  for (int i = 0; i < mSkinCombo->count(); ++i) {
    if (mSkinCombo->itemData(i).toInt() == selected) {
      mSkinCombo->setCurrentIndex(i);
      break;
    }
  }
  mSkinCombo->blockSignals(false);
}

void HomePage::refresh() {
  mExperienceBar->update(mExperience);
  rebuildSkinCombo();
  mMascot->setSkin(mSkinManager.selectedSkin());
}

} // namespace NomCool::gui

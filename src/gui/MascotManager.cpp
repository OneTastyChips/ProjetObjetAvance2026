
#include "MascotManager.hpp"

#include <gui/ShopDialog.hpp>

#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

namespace NomCool::gui {

MascotManager::MascotManager(data::SkinManager &skinManager,
                             data::Experience &experience)
    : mSkinManager(skinManager), mExperience(experience) {
  auto *layout = new QVBoxLayout();

  auto *toggle = new QCheckBox("Show mascot");
  toggle->setChecked(true);
  layout->addWidget(toggle);

  mMascot = new Mascot();
  layout->addWidget(mMascot);

  connect(toggle, &QCheckBox::toggled, mMascot, &Mascot::setVisible);

  auto *skinLabel = new QLabel("Skin:");
  skinLabel->setStyleSheet("font-weight: bold;");
  layout->addWidget(skinLabel);

  mSkinSelector = new QComboBox();
  layout->addWidget(mSkinSelector);

  connect(mSkinSelector, &QComboBox::activated, this,
          &MascotManager::applySkin);

  auto *shopButton = new QPushButton("Shop");
  shopButton->setStyleSheet(
      "background-color: #DAA520; color: white; font-weight: bold; "
      "padding: 8px;");
  connect(shopButton, &QPushButton::clicked, this, &MascotManager::openShop);
  layout->addWidget(shopButton);

  setLayout(layout);

  refreshSkins();
  mMascot->setSkin(mSkinManager.selectedSkin());
}

void MascotManager::refreshSkins() {
  mSkinSelector->blockSignals(true);
  mSkinSelector->clear();

  auto owned = mSkinManager.ownedSkinIndices();
  const auto &allSkins = mSkinManager.allSkins();

  int currentComboIndex = 0;
  for (int i = 0; i < static_cast<int>(owned.size()); ++i) {
    int skinIdx = owned[i];
    mSkinSelector->addItem(allSkins[skinIdx].name, skinIdx);
    if (skinIdx == mSkinManager.selectedSkinIndex()) {
      currentComboIndex = i;
    }
  }

  mSkinSelector->setCurrentIndex(currentComboIndex);
  mSkinSelector->blockSignals(false);
}

void MascotManager::applySkin(int comboIndex) {
  int skinIndex = mSkinSelector->itemData(comboIndex).toInt();
  mSkinManager.selectSkin(skinIndex);
  mMascot->setSkin(mSkinManager.selectedSkin());
}

void MascotManager::openShop() {
  auto *shop = new ShopDialog(mSkinManager, mExperience, this);
  connect(shop, &ShopDialog::skinPurchased, this,
          &MascotManager::refreshSkins);
  shop->exec();
  delete shop;
}

} // namespace NomCool::gui

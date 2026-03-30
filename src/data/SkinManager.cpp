
#include "SkinManager.hpp"

#include <QSettings>

namespace NomCool::data {

SkinManager::SkinManager() {
  mSkins = {
      {"Default", QColor(0, 0, 0, 0), 0},
      {"Golden", QColor(255, 215, 0), 15},
      {"Ice", QColor(100, 180, 255), 30},
      {"Fire", QColor(255, 80, 40), 50},
      {"Shadow", QColor(120, 60, 200), 80},
  };
  mOwnedSkins.insert(0); // Default is always owned
  load();
}

const std::vector<Skin> &SkinManager::allSkins() const { return mSkins; }

bool SkinManager::isOwned(int index) const {
  return mOwnedSkins.count(index) > 0;
}

std::vector<int> SkinManager::ownedSkinIndices() const {
  return {mOwnedSkins.begin(), mOwnedSkins.end()};
}

int SkinManager::selectedSkinIndex() const { return mSelectedIndex; }

const Skin &SkinManager::selectedSkin() const { return mSkins[mSelectedIndex]; }

void SkinManager::selectSkin(int index) {
  if (index >= 0 && index < static_cast<int>(mSkins.size()) && isOwned(index)) {
    mSelectedIndex = index;
    save();
  }
}

bool SkinManager::purchase(int index, int &gold) {
  if (index < 0 || index >= static_cast<int>(mSkins.size()))
    return false;
  if (isOwned(index))
    return false;
  if (gold < mSkins[index].price)
    return false;

  gold -= mSkins[index].price;
  mOwnedSkins.insert(index);
  save();
  return true;
}

void SkinManager::save() const {
  QSettings settings("NomCool", "NomCool");
  settings.setValue("skin/selected", mSelectedIndex);

  QStringList owned;
  for (int idx : mOwnedSkins) {
    owned.append(QString::number(idx));
  }
  settings.setValue("skin/owned", owned);
}

void SkinManager::load() {
  QSettings settings("NomCool", "NomCool");
  mSelectedIndex = settings.value("skin/selected", 0).toInt();

  QStringList owned = settings.value("skin/owned").toStringList();
  for (const QString &s : owned) {
    bool ok = false;
    int idx = s.toInt(&ok);
    if (ok && idx >= 0 && idx < static_cast<int>(mSkins.size())) {
      mOwnedSkins.insert(idx);
    }
  }

  // Validate selected skin is owned
  if (!isOwned(mSelectedIndex)) {
    mSelectedIndex = 0;
  }
}

} // namespace NomCool::data

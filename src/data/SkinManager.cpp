
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

void SkinManager::addCustomSkin(const QString &name, const QColor &color) {
  mSkins.push_back({name, color, 0});
  mOwnedSkins.insert(static_cast<int>(mSkins.size()) - 1);
  save();
}

void SkinManager::save() const {
  QSettings settings("NomCool", "NomCool");
  settings.setValue("skin/selected", mSelectedIndex);

  QStringList owned;
  for (int idx : mOwnedSkins) {
    owned.append(QString::number(idx));
  }
  settings.setValue("skin/owned", owned);

  // Sauvegarder les skins custom
  int customCount = static_cast<int>(mSkins.size()) - BUILT_IN_COUNT;
  settings.setValue("skin/custom/count", customCount);
  for (int i = 0; i < customCount; ++i) {
    const Skin &s = mSkins[BUILT_IN_COUNT + i];
    settings.setValue(QString("skin/custom/%1/name").arg(i), s.name);
    settings.setValue(QString("skin/custom/%1/color").arg(i), s.tint.name());
  }
}

void SkinManager::load() {
  QSettings settings("NomCool", "NomCool");

  // Charger les skins custom en premier (avant de traiter les indices)
  int customCount = settings.value("skin/custom/count", 0).toInt();
  for (int i = 0; i < customCount; ++i) {
    QString name =
        settings.value(QString("skin/custom/%1/name").arg(i)).toString();
    QColor color(
        settings.value(QString("skin/custom/%1/color").arg(i)).toString());
    if (name.isEmpty() || !color.isValid())
      continue;
    mSkins.push_back({name, color, 0});
    mOwnedSkins.insert(static_cast<int>(mSkins.size()) - 1);
  }

  mSelectedIndex = settings.value("skin/selected", 0).toInt();

  QStringList owned = settings.value("skin/owned").toStringList();
  for (const QString &s : owned) {
    bool ok = false;
    int idx = s.toInt(&ok);
    if (ok && idx >= 0 && idx < static_cast<int>(mSkins.size())) {
      mOwnedSkins.insert(idx);
    }
  }

  if (!isOwned(mSelectedIndex)) {
    mSelectedIndex = 0;
  }
}

} // namespace NomCool::data

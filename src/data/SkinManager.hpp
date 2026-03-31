
#pragma once

#include <data/Skin.hpp>

#include <set>
#include <vector>

namespace NomCool::data {

class SkinManager {
public:
  SkinManager();

  const std::vector<Skin> &allSkins() const;
  bool isOwned(int index) const;
  std::vector<int> ownedSkinIndices() const;

  int selectedSkinIndex() const;
  const Skin &selectedSkin() const;
  void selectSkin(int index);

  bool purchase(int index, int &gold);
  void addCustomSkin(const QString &name, const QColor &color);

  void save() const;
  void load();

private:
  static constexpr int BUILT_IN_COUNT = 5;

  std::vector<Skin> mSkins;
  std::set<int> mOwnedSkins;
  int mSelectedIndex = 0;
};

} // namespace NomCool::data

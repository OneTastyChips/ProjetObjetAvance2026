
#pragma once

#include <QComboBox>
#include <QWidget>

#include <data/Experience.hpp>
#include <data/SkinManager.hpp>
#include <gui/Mascot.hpp>

namespace NomCool::gui {

class MascotManager : public QWidget {
  Q_OBJECT

public:
  MascotManager(data::SkinManager &skinManager, data::Experience &experience);

  void refreshSkins();

private:
  void applySkin(int comboIndex);
  void openShop();

  data::SkinManager &mSkinManager;
  data::Experience &mExperience;
  Mascot *mMascot = nullptr;
  QComboBox *mSkinSelector = nullptr;
};

} // namespace NomCool::gui

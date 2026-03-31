
#pragma once

#include <QComboBox>
#include <QWidget>

#include <data/Experience.hpp>
#include <data/SkinManager.hpp>
#include <gui/ExperienceBar.hpp>
#include <gui/Mascot.hpp>

namespace NomCool::gui {

class HomePage : public QWidget {
  Q_OBJECT

public:
  HomePage(data::Experience &experience, data::SkinManager &skinManager);

  void refresh();

Q_SIGNALS:
  void playClicked();

private:
  void rebuildSkinCombo();

  data::Experience &mExperience;
  data::SkinManager &mSkinManager;
  ExperienceBar *mExperienceBar = nullptr;
  Mascot *mMascot = nullptr;
  QComboBox *mSkinCombo = nullptr;
};

} // namespace NomCool::gui

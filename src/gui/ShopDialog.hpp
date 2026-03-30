
#pragma once

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>

#include <data/Experience.hpp>
#include <data/SkinManager.hpp>

namespace NomCool::gui {

class ShopDialog : public QDialog {
  Q_OBJECT

public:
  ShopDialog(data::SkinManager &skinManager, data::Experience &experience,
             QWidget *parent = nullptr);

Q_SIGNALS:
  void skinPurchased();

private:
  void rebuildItems();

  data::SkinManager &mSkinManager;
  data::Experience &mExperience;
  QLabel *mGoldLabel = nullptr;
  QVBoxLayout *mItemsLayout = nullptr;
};

} // namespace NomCool::gui

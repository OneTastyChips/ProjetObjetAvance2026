
#pragma once

#include <QColor>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

#include <data/SkinManager.hpp>
#include <gui/Mascot.hpp>

namespace NomCool::gui {

class SkinCreatorDialog : public QDialog {
  Q_OBJECT

public:
  explicit SkinCreatorDialog(data::SkinManager &skinManager,
                             QWidget *parent = nullptr);

private:
  void pickColor();
  void updateColorButton();

  data::SkinManager &mSkinManager;
  QColor mSelectedColor{200, 100, 255};

  QLineEdit *mNameEdit = nullptr;
  QPushButton *mColorButton = nullptr;
  Mascot *mPreviewMascot = nullptr;
  QPushButton *mSaveButton = nullptr;
};

} // namespace NomCool::gui

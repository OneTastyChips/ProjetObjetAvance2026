
#include "SkinCreatorDialog.hpp"

#include <QColorDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

namespace NomCool::gui {

SkinCreatorDialog::SkinCreatorDialog(data::SkinManager &skinManager,
                                     QWidget *parent)
    : QDialog(parent), mSkinManager(skinManager) {
  setWindowTitle("Créer un skin");
  setMinimumWidth(320);

  auto *mainLayout = new QVBoxLayout(this);
  mainLayout->setSpacing(16);
  mainLayout->setContentsMargins(24, 20, 24, 20);

  // Titre
  auto *title = new QLabel("Créer un skin personnalisé");
  title->setStyleSheet("font-size: 16px; font-weight: bold;");
  title->setAlignment(Qt::AlignCenter);
  mainLayout->addWidget(title);

  // Aperçu de la mascotte
  mPreviewMascot = new Mascot();
  mPreviewMascot->setSkin({QString(), mSelectedColor, 0});
  mainLayout->addWidget(mPreviewMascot, 0, Qt::AlignCenter);

  // Nom du skin
  auto *nameRow = new QHBoxLayout();
  auto *nameLabel = new QLabel("Nom :");
  nameLabel->setStyleSheet("font-weight: bold;");
  nameLabel->setFixedWidth(70);
  mNameEdit = new QLineEdit();
  mNameEdit->setPlaceholderText("Mon skin");
  mNameEdit->setMaxLength(24);
  connect(mNameEdit, &QLineEdit::textChanged, this, [this](const QString &t) {
    mSaveButton->setEnabled(!t.trimmed().isEmpty());
  });
  nameRow->addWidget(nameLabel);
  nameRow->addWidget(mNameEdit);
  mainLayout->addLayout(nameRow);

  // Sélecteur de couleur
  auto *colorRow = new QHBoxLayout();
  auto *colorLabel = new QLabel("Couleur :");
  colorLabel->setStyleSheet("font-weight: bold;");
  colorLabel->setFixedWidth(70);
  mColorButton = new QPushButton("Choisir");
  mColorButton->setFixedHeight(32);
  updateColorButton();
  connect(mColorButton, &QPushButton::clicked, this,
          &SkinCreatorDialog::pickColor);
  colorRow->addWidget(colorLabel);
  colorRow->addWidget(mColorButton);
  colorRow->addStretch();
  mainLayout->addLayout(colorRow);

  mainLayout->addStretch();

  // Boutons Annuler / Sauvegarder
  auto *buttonRow = new QHBoxLayout();
  auto *cancelButton = new QPushButton("Annuler");
  connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

  mSaveButton = new QPushButton("Sauvegarder");
  mSaveButton->setEnabled(false);
  mSaveButton->setStyleSheet(
      "font-weight: bold; background-color: #4CAF50; "
      "color: white; border-radius: 6px; padding: 8px 24px;");
  connect(mSaveButton, &QPushButton::clicked, this, [this] {
    mSkinManager.addCustomSkin(mNameEdit->text().trimmed(), mSelectedColor);
    accept();
  });

  buttonRow->addWidget(cancelButton);
  buttonRow->addWidget(mSaveButton);
  mainLayout->addLayout(buttonRow);
}

void SkinCreatorDialog::pickColor() {
  QColor color =
      QColorDialog::getColor(mSelectedColor, this, "Choisir une couleur");
  if (!color.isValid())
    return;
  mSelectedColor = color;
  updateColorButton();
  mPreviewMascot->setSkin({QString(), mSelectedColor, 0});
}

void SkinCreatorDialog::updateColorButton() {
  mColorButton->setStyleSheet(
      QString("background-color: %1; color: %2; "
              "border-radius: 6px; border: 1px solid #888; padding: 0 12px;")
          .arg(mSelectedColor.name())
          .arg(mSelectedColor.lightness() > 128 ? "#000000" : "#ffffff"));
  mColorButton->setText(mSelectedColor.name().toUpper());
}

} // namespace NomCool::gui

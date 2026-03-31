
#include "SettingsDialog.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSettings>
#include <QVBoxLayout>

namespace NomCool::gui {

static constexpr char KEY_MASCOT[] = "settings/mascotEnabled";
static constexpr char KEY_MUSIC[]  = "settings/musicEnabled";

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent) {
  setWindowTitle("Paramètres");
  setMinimumWidth(300);

  auto *mainLayout = new QVBoxLayout(this);
  mainLayout->setContentsMargins(24, 20, 24, 20);
  mainLayout->setSpacing(20);

  // Titre
  auto *title = new QLabel("Paramètres");
  title->setStyleSheet("font-size: 18px; font-weight: bold;");
  title->setAlignment(Qt::AlignCenter);
  mainLayout->addWidget(title);

  // --- Ligne mascotte ---
  auto *mascotRow = new QHBoxLayout();
  auto *mascotLabel = new QLabel("Afficher la mascotte");
  mascotLabel->setStyleSheet("font-size: 14px;");
  mMascotToggle = new ToggleSwitch();
  mMascotToggle->setChecked(mascotEnabled());
  connect(mMascotToggle, &ToggleSwitch::toggled, this, [](bool checked) {
    QSettings("NomCool", "NomCool").setValue(KEY_MASCOT, checked);
  });
  mascotRow->addWidget(mascotLabel);
  mascotRow->addStretch();
  mascotRow->addWidget(mMascotToggle);
  mainLayout->addLayout(mascotRow);

  // --- Ligne musique ---
  auto *musicRow = new QHBoxLayout();
  auto *musicLabel = new QLabel("Musique de fond");
  musicLabel->setStyleSheet("font-size: 14px;");
  mMusicToggle = new ToggleSwitch();
  mMusicToggle->setChecked(musicEnabled());
  connect(mMusicToggle, &ToggleSwitch::toggled, this, [this](bool checked) {
    QSettings("NomCool", "NomCool").setValue(KEY_MUSIC, checked);
    emit musicToggled(checked);
  });
  musicRow->addWidget(musicLabel);
  musicRow->addStretch();
  musicRow->addWidget(mMusicToggle);
  mainLayout->addLayout(musicRow);

  mainLayout->addStretch();

  // Bouton fermer
  auto *closeButton = new QPushButton("Fermer");
  closeButton->setMinimumHeight(36);
  connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
  mainLayout->addWidget(closeButton);
}

bool SettingsDialog::mascotEnabled() {
  return QSettings("NomCool", "NomCool").value(KEY_MASCOT, true).toBool();
}

bool SettingsDialog::musicEnabled() {
  return QSettings("NomCool", "NomCool").value(KEY_MUSIC, false).toBool();
}

} // namespace NomCool::gui

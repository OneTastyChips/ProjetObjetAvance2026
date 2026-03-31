
#pragma once

#include <QDialog>

#include <gui/ToggleSwitch.hpp>

namespace NomCool::gui {

class SettingsDialog : public QDialog {
  Q_OBJECT

public:
  explicit SettingsDialog(QWidget *parent = nullptr);

  static bool mascotEnabled();
  static bool musicEnabled();

Q_SIGNALS:
  void musicToggled(bool enabled);

private:
  ToggleSwitch *mMascotToggle = nullptr;
  ToggleSwitch *mMusicToggle = nullptr;
};

} // namespace NomCool::gui

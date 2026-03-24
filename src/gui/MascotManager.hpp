
#pragma once

#include <QWidget>

#include <gui/Mascot.hpp>

namespace NomCool::gui {

class MascotManager : public QWidget {
  Q_OBJECT

public:
  MascotManager();

private:
  Mascot *mMascot = nullptr;
};

} // namespace NomCool::gui

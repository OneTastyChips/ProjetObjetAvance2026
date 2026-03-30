
#pragma once

#include <QLabel>
#include <QWidget>

#include <data/Skin.hpp>

namespace NomCool::gui {

class Mascot : public QWidget {
  Q_OBJECT

public:
  Mascot();

  void setSkin(const data::Skin &skin);

private:
  QLabel *mImageLabel = nullptr;
};

} // namespace NomCool::gui

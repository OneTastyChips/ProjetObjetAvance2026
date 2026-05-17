
#pragma once

#include <QColor>
#include <QString>

namespace NomCool::data {

struct Skin {
  QString name;
  QColor tint;
  int price; // 0 pour le skin par defaut
};

} // namespace NomCool::data

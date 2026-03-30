
#pragma once

#include <QColor>
#include <QString>

namespace NomCool::data {

struct Skin {
  QString name;
  QColor tint;
  int price; // 0 = free (default skin)
};

} // namespace NomCool::data


#pragma once

#include <data/Difficulty.hpp>

namespace NomCool::data {

struct GameConfig {
  Difficulty difficulty = Difficulty::Normal;
  bool hasTimer = true;
  int questionCount = -1; // -1 = infini
};

} // namespace NomCool::data


#pragma once

#include <data/Difficulty.hpp>

namespace NomCool::data {

class Experience {
public:
  void recordCorrectAnswer(Difficulty difficulty);
  void recordWrongAnswer();

  int totalXP() const;
  int level() const;
  int xpInCurrentLevel() const;
  int xpForNextLevel() const;
  int streak() const;
  bool isHardUnlocked() const;

  int gold() const;
  void spendGold(int amount);

  void save() const;
  void load();

private:
  int mTotalXP = 0;
  int mGold = 0;
  int mStreak = 0;

  static int xpThresholdForLevel(int level);
};

} // namespace NomCool::data


#include "Experience.hpp"

#include <QSettings>

#include <algorithm>

namespace NomCool::data {

void Experience::recordCorrectAnswer(Difficulty difficulty) {
  int base = 0;
  switch (difficulty) {
  case Difficulty::Easy:
    base = 1;
    break;
  case Difficulty::Normal:
    base = 2;
    break;
  case Difficulty::Hard:
    base = 4;
    break;
  }

  ++mStreak;

  int streakBonus = std::min(mStreak, 5);
  int earned = base + streakBonus;
  mTotalXP += earned;
  mGold += earned;
  save();
}

void Experience::recordWrongAnswer() {
  mStreak = 0;
  save();
}

int Experience::totalXP() const { return mTotalXP; }

int Experience::level() const {
  int lvl = 1;
  while (mTotalXP >= xpThresholdForLevel(lvl + 1)) {
    ++lvl;
  }
  return lvl;
}

int Experience::xpInCurrentLevel() const {
  return mTotalXP - xpThresholdForLevel(level());
}

int Experience::xpForNextLevel() const {
  return xpThresholdForLevel(level() + 1) - xpThresholdForLevel(level());
}

int Experience::streak() const { return mStreak; }

bool Experience::isHardUnlocked() const { return level() >= 2; }

int Experience::gold() const { return mGold; }

void Experience::spendGold(int amount) {
  mGold -= amount;
  save();
}

void Experience::save() const {
  QSettings settings("NomCool", "NomCool");
  settings.setValue("experience/totalXP", mTotalXP);
  settings.setValue("experience/gold", mGold);
}

void Experience::load() {
  QSettings settings("NomCool", "NomCool");
  mTotalXP = settings.value("experience/totalXP", 0).toInt();
  mGold = settings.value("experience/gold", 0).toInt();
}

int Experience::xpThresholdForLevel(int level) {
  // Level 1: 0 XP, Level 2: 10 XP, Level 3: 30 XP, Level 4: 60 XP, ...
  // Formula: 5 * L * (L - 1)
  return 5 * level * (level - 1);
}

} // namespace NomCool::data


#include "Score.hpp"

namespace NomCool::data {

void Score::recordSuccess() {
  ++mCorrect;
  ++mTotal;
}

void Score::recordFailure() { ++mTotal; }

int Score::correct() const { return mCorrect; }
int Score::total() const { return mTotal; }

} // namespace NomCool::data

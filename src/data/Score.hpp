
#pragma once

namespace NomCool::data {

class Score {
public:
  void recordSuccess();
  void recordFailure();

  int correct() const;
  int total() const;

private:
  int mCorrect = 0;
  int mTotal = 0;
};

} // namespace NomCool::data

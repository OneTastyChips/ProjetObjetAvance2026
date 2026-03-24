
#pragma once

#include <data/Difficulty.hpp>
#include <data/Interrogation.hpp>

#include <random>

namespace NomCool::data {

class QuestionGenerator {
public:
  QuestionGenerator();

  Interrogation generate(Difficulty difficulty);

private:
  std::mt19937 mGen;
};

} // namespace NomCool::data

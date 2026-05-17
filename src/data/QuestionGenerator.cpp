
#include "QuestionGenerator.hpp"

#include <algorithm>

namespace NomCool::data {

QuestionGenerator::QuestionGenerator() : mGen(std::random_device{}()) {}

Interrogation QuestionGenerator::generate(Difficulty difficulty) {
  int max;
  switch (difficulty) {
  case Difficulty::Easy:
    max = 5;
    break;
  case Difficulty::Normal:
    max = 10;
    break;
  case Difficulty::Hard:
    max = 15;
    break;
  }

  std::uniform_int_distribution<> dis(1, max);
  int lhs = dis(mGen);
  int rhs = dis(mGen);
  int result = lhs * rhs;

  std::vector<std::pair<std::string, Response>> answers;

  if (difficulty == Difficulty::Hard) {
    // En difficile, les mauvaises reponses sont a +/- 1 du resultat
    int wrong1 = result + 1;
    int wrong2 = result > 1 ? result - 1 : result + 2;
    answers = {{std::to_string(result), "Correct"},
               {std::to_string(wrong1), "Incorrect"},
               {std::to_string(wrong2), "Incorrect"}};
  } else {
    // Sinon on decale un des facteurs pour obtenir des distracteurs
    auto next = [max](int value) { return value % max + 1; };
    answers = {{std::to_string(result), "Correct"},
               {std::to_string(lhs * next(rhs)), "Incorrect"},
               {std::to_string(next(lhs) * rhs), "Incorrect"}};
  }

  std::shuffle(answers.begin(), answers.end(), mGen);
  answers.push_back({"Je ne sais pas", "I don't know"});
  return {std::to_string(lhs) + " * " + std::to_string(rhs), answers};
}

} // namespace NomCool::data

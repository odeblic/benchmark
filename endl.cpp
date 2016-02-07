#include <iostream>
#include <sstream>

#include "benchmark.h"

int main()
{
  const unsigned long NB_ITERATIONS = 10000000;

  auto loopEmpty = []()
  {
    std::stringstream buffer;
    buffer << "x";
  };

  auto loopEndl = []()
  {
    std::stringstream buffer;
    buffer << "x" << std::endl;
  };

  auto loopChar = []()
  {
    std::stringstream buffer;
    buffer << "x" << '\n';
  };

  auto loopString = []()
  {
    std::stringstream buffer;
    buffer << "x" << "\n";
  };

  Bench{"endl", 3}.run(loopEmpty, loopEndl, NB_ITERATIONS);

  Bench{"character", 3}.run(loopEmpty, loopChar, NB_ITERATIONS);

  Bench{"string", 3}.run(loopEmpty, loopString, NB_ITERATIONS);

  return 0;
}


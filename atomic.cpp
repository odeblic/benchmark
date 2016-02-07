#include <iostream>
#include <atomic>

#include "benchmark.h"

int main()
{
  const unsigned long NB_ITERATIONS = 100000000;

  auto loopIntEmpty = []()
  {
    int st_int;
  };

  auto loopAtomicIntEmpty = []()
  {
    std::atomic<int> at_int;
  };

  auto loopInt = []()
  {
    int st_int;
    st_int++;
  };

  auto loopAtomicInt = []()
  {
    std::atomic<int> at_int;
    at_int++;
  };

  Bench{"int", 3}.run(loopIntEmpty, loopInt, NB_ITERATIONS);

  Bench{"atomic<int>", 3}.run(loopAtomicIntEmpty, loopAtomicInt, NB_ITERATIONS);

  return 0;
}


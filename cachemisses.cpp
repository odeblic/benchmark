#include <iostream>

#include "benchmark.h"

long long buffer[8*1024*1024];

int main()
{
  const unsigned long NB_ITERATIONS = 3;

  auto loopEmpty = []()
  {
  };

  auto loopBusy = []()
  {
    for(auto i = 0; i < sizeof(buffer) / sizeof(long long); ++i)
    {
      buffer[i] = 1;
    }
  };

  auto loopLazy = []()
  {
    for(auto i = 0; i < sizeof(buffer) / sizeof(long long); i += 32)
    {
      buffer[i] = 1;
    }
  };

  Bench{"full loop", 2}.run(loopEmpty, loopBusy, NB_ITERATIONS);

  Bench{"lazy loop", 2}.run(loopEmpty, loopLazy, NB_ITERATIONS);

  return 0;
}


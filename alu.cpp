#include <iostream>

#include "benchmark.h"

int main()
{
  const unsigned long NB_ITERATIONS = 10000000;

  auto loopEmpty = []()
  {
  };

  auto loopInteger = []()
  {
    long long array[10][10][10];
    
    long long sum;
    
    for(auto i = 0; i < 10; ++i)
    {
      for(auto j = 0; j < 10; ++j)
      {
        for(auto k = 0; k < 10; ++k)
        {
          sum += array[i][j][k];
        }
      }
    }
  };

  auto loopDouble = []()
  {
    double array[10][10][10];
    
    double sum;
    
    for(auto i = 0; i < 10; ++i)
    {
      for(auto j = 0; j < 10; ++j)
      {
        for(auto k = 0; k < 10; ++k)
        {
          sum += array[i][j][k];
        }
      }
    }
  };

  Bench{"long int", 1}.run(loopEmpty, loopInteger, NB_ITERATIONS);

  Bench{"double", 1}.run(loopEmpty, loopDouble, NB_ITERATIONS);

  return 0;
}


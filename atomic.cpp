#include <iostream>
#include <atomic>
#include <pthread.h>

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

  auto loopLockedIntEmpty = []()
  {
    int lck_int;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
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

  auto loopLockedInt = []()
  {
    int lck_int;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex);
    lck_int++;
    pthread_mutex_unlock(&mutex);
  };

  Bench{"int", 3}.run(loopIntEmpty, loopInt, NB_ITERATIONS);

  Bench{"atomic<int>", 3}.run(loopAtomicIntEmpty, loopAtomicInt, NB_ITERATIONS);

  Bench{"lock int unlock", 3}.run(loopLockedIntEmpty, loopLockedInt, NB_ITERATIONS);

  return 0;
}


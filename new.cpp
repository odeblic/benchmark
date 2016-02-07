#include <iostream>

#include "benchmark.h"

class Object
{
  public:

  explicit Object(int n)
  {
    ++countCtor;
    /*
    for(auto& c : buffer)
    {
      c = '_';
    }
    if(n < 0)
    {
      throw 0;
    }
    */
  }

  ~Object()
  {
    ++countDtor;
  }

  static long getCountCtor()
  {
    return countCtor;
  }

  static long getCountDtor()
  {
    return countDtor;
  }

  static void reset()
  {
    countCtor = 0;
    countDtor = 0;
  }

  private:

  static long countCtor;
  static long countDtor;

  char buffer[64];
};

long Object::countCtor = 0;
long Object::countDtor = 0;

int main(int argc, char ** argv)
{
  const unsigned long NB_ITERATIONS = 1000000000;

  auto loopEmpty = []()
  {
    Object * ptr;
  };

  auto loopNew = []()
  {
    Object * ptr;

    try
    {
      ptr = new Object(1);
      delete ptr;
    }
    catch(std::bad_alloc e)
    {
      std::cout << "Exception : " << e.what() << std::endl;
    }
  };

  auto loopNewNothrow = []()
  {
    Object * ptr;

    ptr = new(std::nothrow) Object(1);

    if(ptr)
    {
      delete ptr;
    }
    else
    {
      std::cout << "Error on memory allocation" << std::endl;
    }
  };

  auto loopNewPlacement = []()
  {
    char buffer[sizeof(Object)];
    Object * ptr;

    ptr = new(&buffer) Object(1);

    if(ptr)
    {
      ptr->~Object();
    }
    else
    {
      std::cout << "Error on object construction" << std::endl;
    }
  };

  Object::reset();
  Bench{"new", 3}.run(loopEmpty, loopNew, NB_ITERATIONS);
  std::cout << Object::getCountCtor() << " calls to constructor" << std::endl;
  std::cout << Object::getCountDtor() << " calls to destructor" << std::endl;

  Object::reset();
  Bench{"new nothrow", 3}.run(loopEmpty, loopNewNothrow, NB_ITERATIONS);
  std::cout << Object::getCountCtor() << " calls to constructor" << std::endl;
  std::cout << Object::getCountDtor() << " calls to destructor" << std::endl;

  Object::reset();
  Bench{"new placement", 3}.run(loopEmpty, loopNewPlacement, NB_ITERATIONS);
  std::cout << Object::getCountCtor() << " calls to constructor" << std::endl;
  std::cout << Object::getCountDtor() << " calls to destructor" << std::endl;

  return 0;
}


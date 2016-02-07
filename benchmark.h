#pragma once

#include <limits>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <cmath>

/*
enum class Colors
{
  RED,
  BLUE,
  CYAN,
  GREEN,
  GRAY,
  WHITE,
  BLACK,
  YELLOW,
  PURPLE,
};

enum class Traits
{
  FG,
  BG,
  BLINK,
  BOLD,
};

class Font
{
  std::string operator
};
*/

template<typename T = double, typename U = unsigned long>
class Statistics
{
  public:

  inline Statistics() : count(0), sum(0),
    min(std::numeric_limits<T>::max()),
    max(std::numeric_limits<T>::min())
  {
  }

  inline void addSample(T sample) noexcept
  {
    count++;
    sum += sample;

    if(sample < min)
    {
      min = sample;
    }
    else if(sample > max)
    {
      max = sample;
    }
  }

  inline U getCount() const noexcept
  {
    return count;
  }

  inline T getMean() const noexcept
  {
    return sum / count;
    //return sum / static_cast<T>(count);
  }

  inline T getMin() const noexcept
  {
    return min;
  }

  inline T getMax() const noexcept
  {
    return max;
  }

  private:

  U count;
  T sum;
  T min;
  T max;
};

class Bench
{
  public:

  // typedef action;

  Bench(std::string title = "unnamed", int noRuns = 1) : title(title), noRuns(noRuns)
  {
  }

  Bench(const Bench&) = delete;

  Bench& operator=(const Bench&) = delete;

  void run(void (*overhead)() noexcept, void (*operation)() noexcept, const unsigned long nbIterations)
  {
    const int N = 1000;

    std::cout << std::endl << "**************************************************************"
              << std::endl << "Bench \"" << title << '"'
              << std::endl << "**************************************************************"
              << std::endl << std::endl;

    std::cout << "[calibration] in progress..." << std::endl;

    for(int i = 1; i <= N; i++)
    {
      calibrate(overhead);
      calibrate(overhead);
      calibrate(overhead);
      
      usleep(rand() % 100 + 1);
    }

    std::cout << "  count\t=\t" << statOverheads.getCount() << " samples" << std::endl
              << "  min\t=\t"   << statOverheads.getMin()   << " ticks"   << std::endl
              << "  max\t=\t"   << statOverheads.getMax()   << " ticks"   << std::endl
              << "  mean\t=\t"  << statOverheads.getMean()  << " ticks"   << std::endl;

    std::cout << "[calibration] completed !" << std::endl << std::endl;

    std::cout << "[measure] in progress..." << std::endl;

    for(int i = 1; i <= N; i++)
    {
      measure(operation);
      measure(operation);
      measure(operation);
      
      usleep(rand() % 100 + 1);
    }

    std::cout << "  count\t=\t" << statOperations.getCount() << " samples" << std::endl
              << "  min\t=\t"   << statOperations.getMin()   << " ticks"   << std::endl
              << "  max\t=\t"   << statOperations.getMax()   << " ticks"   << std::endl
              << "  mean\t=\t"  << statOperations.getMean()  << " ticks"   << std::endl;

    std::cout << "[measure] completed !" << std::endl << std::endl;

    for(int n = 1; n <= noRuns; n++)
    {
      clock_t begin;
      clock_t end;
      double duration;

      std::cout << "[run " << n << '/' << noRuns << "] in progress..." << std::endl;

      begin = clock();

      for(unsigned long i = 0; i < nbIterations; i++)
      {
        operation();
      }

      end = clock();

      duration = double(end - begin) / CLOCKS_PER_SEC;

      std::cout << "  count\t=\t" << nbIterations << " iterations" << std::endl;
      std::cout << "  time\t=\t" << duration << " seconds" << std::endl;

      std::cout << "[run " << n << '/' << noRuns << "] completed !" << std::endl << std::endl;
    }
  }

  private:

  std::string title;
  int noRuns;

  Statistics<unsigned long, unsigned long> statOverheads;
  Statistics<unsigned long, unsigned long> statOperations;

  void calibrate(void (*overhead)() noexcept) noexcept
  {
    unsigned long begin = rdtsc();
    overhead();
    unsigned long end = rdtsc();
    unsigned long elapsed = end - begin;
    
    statOverheads.addSample(elapsed);
  }

  void measure(void (*operation)() noexcept) noexcept
  {
    unsigned long begin = rdtsc();
    operation();
    unsigned long end = rdtsc();
    double elapsed = end - begin;

    statOperations.addSample(elapsed - statOverheads.getMean());
  }

  static inline unsigned long rdtsc() throw()
  {
#if defined(__GNUG__) || defined(__x86_64__) || defined(__i386__)
    unsigned int lo, hi;
    asm volatile ( "rdtsc" : "=a" (lo), "=d" (hi) );
    return (unsigned long)( ((unsigned long)lo) | (((unsigned long)hi) << 32) );
#else
#error TSC cannot be read in this configuration
#endif
  }
};


cmake_minimum_required(VERSION 2.8)
project(benchmark)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY .)

add_definitions(-std=c++11)

include_directories(.)

add_executable(endl   endl.cpp)
add_executable(atomic atomic.cpp)
add_executable(new    new.cpp)

# remainging to implement :
#
# - colors in terminal output
# - reporting to CSV file
# - fixtures (setup, teardown)
# - comparison of results
# - other benches
# - enhancement of code


cmake_minimum_required(VERSION 3.28)
project(jeopardy)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(src)

enable_testing()
add_subdirectory(tests)
cmake_minimum_required(VERSION 3.5)
project(fuzzysearch)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp wordset.cpp wordset.h)
add_executable(fuzzysearch ${SOURCE_FILES})
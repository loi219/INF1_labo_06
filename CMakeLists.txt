cmake_minimum_required(VERSION 3.6)
project(INF1_labo_05b)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wconversion -Wextra -pedantic")

set(SOURCE_FILES  Labo_05b_Biefer_Rouvinez.cpp)
add_executable(INF1_labo_05b ${SOURCE_FILES})

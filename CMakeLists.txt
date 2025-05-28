cmake_minimum_required(VERSION 3.22)
project(game-of-life CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(Inc/)

add_library(Model Src/Model.cpp)
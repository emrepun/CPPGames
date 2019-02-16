cmake_minimum_required(VERSION 3.12)
project(RogueLike)

set(CMAKE_CXX_STANDARD 14)

add_executable(RogueLike main.cpp GameSystem.cpp GameSystem.h Player.cpp Player.h)
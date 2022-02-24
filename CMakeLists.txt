cmake_minimum_required(VERSION 3.21)
project(sekeletons_cx)

set(CMAKE_CXX_STANDARD 23)

add_library(sekeletons_cx SHARED project/entry.cpp project/cheat/helpers/cheat.cpp project/cheat/helpers/cheat.hpp)

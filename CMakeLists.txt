cmake_minimum_required(VERSION 3.21)
project(sekeletons_cx)

set(CMAKE_CXX_STANDARD 23)

add_library(sekeletons_cx SHARED project/entry.cpp project/cheat/helpers/cheat.cpp project/cheat/helpers/cheat.hpp project/cheat/globals/snakeify.hpp project/cheat/globals/globals.hpp)

link_directories("$ENV{DXSDK_DIR}/Lib/x86")

include_directories("$ENV{DXSDK_DIR}/Include")

find_library(D3D9_LIBRARY d3d9.lib PATHS "$ENV{DXSDK_DIR}/Lib/x86")
find_library(D3DX9_LIBRARY d3dx9.lib PATHS "$ENV{DXSDK_DIR}/Lib/x86")
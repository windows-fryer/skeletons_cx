cmake_minimum_required(VERSION 3.21)
project(skeletons_cx)

set(CMAKE_CXX_STANDARD 23)

add_library(skeletons_cx SHARED project/entry.cpp project/cheat/cheat.cpp project/cheat/cheat.hpp project/cheat/globals/snakeify.hpp project/cheat/globals/globals.hpp project/cheat/sdk/interfaces/i_engine_client.hpp project/cheat/sdk/include.hpp project/cheat/sdk/structs/vector.hpp project/cheat/sdk/structs/qangle.hpp project/cheat/helpers/math/math.hpp project/cheat/sdk/structs/matrix.hpp project/cheat/sdk/structs/color.hpp project/cheat/helpers/utilities/utilities.cpp project/cheat/helpers/utilities/utilities.hpp project/cheat/globals/interfaces/interfaces.cpp project/cheat/globals/interfaces/interfaces.hpp project/dependencies/fnv/fnv.hpp project/cheat/helpers/modules/module.hpp project/cheat/helpers/assertion/assertion.hpp project/cheat/helpers/console/console.hpp project/cheat/helpers/console/console.cpp project/cheat/helpers/assertion/assertion.cpp)

link_directories("$ENV{DXSDK_DIR}/Lib/x86")

include_directories("$ENV{DXSDK_DIR}/Include")

find_library(D3D9_LIBRARY d3d9.lib PATHS "$ENV{DXSDK_DIR}/Lib/x86")
find_library(D3DX9_LIBRARY d3dx9.lib PATHS "$ENV{DXSDK_DIR}/Lib/x86")
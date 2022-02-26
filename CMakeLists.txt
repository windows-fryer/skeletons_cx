cmake_minimum_required(VERSION 3.21)
project(skeletons_cx)

set(CMAKE_CXX_STANDARD 23)

add_library(skeletons_cx SHARED project/entry.cpp project/cheat/cheat.cpp project/cheat/cheat.hpp project/cheat/globals/snakeify.hpp project/cheat/globals/globals.hpp project/cheat/sdk/interfaces/i_engine_client.hpp project/cheat/sdk/include.hpp project/cheat/sdk/structs/vector.hpp project/cheat/sdk/structs/qangle.hpp project/cheat/helpers/math/math.hpp project/cheat/sdk/structs/matrix.hpp project/cheat/sdk/structs/color.hpp project/cheat/helpers/utilities/utilities.cpp project/cheat/helpers/utilities/utilities.hpp project/cheat/globals/interfaces/interfaces.cpp project/cheat/globals/interfaces/interfaces.hpp project/dependencies/fnv/fnv.hpp project/cheat/helpers/modules/modules.hpp project/cheat/helpers/assertion/assertion.hpp project/cheat/helpers/console/console.hpp project/cheat/helpers/console/console.cpp project/cheat/helpers/assertion/assertion.cpp project/dependencies/minhook/trampoline.c project/dependencies/minhook/trampoline.h project/dependencies/minhook/MinHook.h project/dependencies/minhook/buffer.c project/dependencies/minhook/buffer.h project/dependencies/minhook/hde/hde32.c project/dependencies/minhook/hde/hde32.h project/dependencies/minhook/hde/hde64.c project/dependencies/minhook/hde/hde64.h project/dependencies/minhook/hde/pstdint.h project/dependencies/minhook/hde/table32.h project/dependencies/minhook/hde/table64.h project/cheat/helpers/hooking/hooking.hpp project/cheat/helpers/hooking/hooking.cpp project/cheat/sdk/enums/buttons.hpp project/cheat/sdk/enums/cvar_flags.hpp project/cheat/sdk/enums/materialvar_flags.hpp project/cheat/sdk/enums/weapon_type.hpp project/cheat/sdk/enums/class_ids.hpp project/cheat/sdk/interfaces/i_client_mode.hpp project/cheat/sdk/interfaces/i_base_client_dll.hpp project/cheat/sdk/structs/client_class.hpp project/cheat/helpers/modules/modules.cpp project/cheat/helpers/patternscan/patternscan.hpp project/cheat/sdk/structs/usercmd.hpp project/cheat/helpers/netvars/netvars.hpp project/cheat/helpers/netvars/netvars.cpp project/cheat/sdk/interfaces/i_client_entity_list.hpp)

link_directories("$ENV{DXSDK_DIR}/Lib/x86")

include_directories("$ENV{DXSDK_DIR}/Include")

find_library(D3D9_LIBRARY d3d9.lib PATHS "$ENV{DXSDK_DIR}/Lib/x86")
find_library(D3DX9_LIBRARY d3dx9.lib PATHS "$ENV{DXSDK_DIR}/Lib/x86")
# thank you to cristeigabriel for helping me with this!
cmake_minimum_required(VERSION 3.21)
project(skeletons_cx)

set(CMAKE_CXX_STANDARD 23)

# we probably dont need this many, only 1 should be fine. this looks funni
file(GLOB_RECURSE SRC
        "project/*.h" ,
        "project/*.hpp" ,
        "project/*.cpp" ,
        "project/*.c" ,
        "project/**/*.h" ,
        "project/**/*.hpp" ,
        "project/**/*.c" ,
        "project/**/*.cpp" ,
        "project/**/**/*.h" ,
        "project/**/**/*.hpp" ,
        "project/**/**/*.c" ,
        "project/**/**/*.cpp" ,
        "project/**/**/**/*.h" ,
        "project/**/**/**/*.hpp" ,
        "project/**/**/**/*.c" ,
        "project/**/**/**/*.cpp" ,
        "project/**/**/**/**/*.h" ,
        "project/**/**/**/**/*.hpp" ,
        "project/**/**/**/**/*.c" ,
        "project/**/**/**/**/*.cpp" ,
        "project/**/**/**/**/**/*.h" ,
        "project/**/**/**/**/**/*.hpp" ,
        "project/**/**/**/**/**/*.c" ,
        "project/**/**/**/**/**/*.cpp" ,
        "project/**/**/**/**/**/**/*.h" ,
        "project/**/**/**/**/**/**/*.hpp" ,
        "project/**/**/**/**/**/**/*.c" ,
        "project/**/**/**/**/**/**/*.cpp"
        )


add_library(${PROJECT_NAME} SHARED ${SRC} project/cheat/sdk/definitions/c_tf_weapon_base.cpp project/cheat/hooks/functions/enumerate_leaves_in_box/enumerate_leaves_in_box.cpp project/cheat/hooks/functions/enumerate_leaves_in_box/enumerate_leaves_in_box.hpp project/cheat/sdk/interfaces/i_client_leaf_system.hpp project/cheat/sdk/structs/renderable_info.hpp project/cheat/hooks/functions/draw_model_execute/draw_model_execute.cpp project/cheat/hooks/functions/draw_model_execute/draw_model_execute.hpp project/cheat/sdk/interfaces/i_model_render.hpp project/cheat/sdk/structs/model_render_info.hpp project/cheat/sdk/structs/i_material.hpp project/cheat/sdk/definitions/i_material.cpp project/cheat/sdk/interfaces/i_material_system.hpp project/cheat/sdk/definitions/i_material_system.cpp)

find_library(D3D9_LIBRARY d3d9.lib PATHS "$ENV{DXSDK_DIR}/Lib/x86")
find_library(D3DX9_LIBRARY d3dx9.lib PATHS "$ENV{DXSDK_DIR}/Lib/x86")
target_link_libraries(${PROJECT_NAME} "${D3D9_LIBRARY}" "${D3DX9_LIBRARY}")
link_directories("$ENV{DXSDK_DIR}/Lib/x86")
include_directories("$ENV{DXSDK_DIR}/Include")

add_definitions(/MP)
add_compile_options(/DEBUG FULL)
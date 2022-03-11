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
        #        "project/**/**/*.h" ,
        #        "project/**/**/*.hpp" ,
        #        "project/**/**/*.c" ,
        #        "project/**/**/*.cpp" ,
        #        "project/**/**/**/*.h" ,
        #        "project/**/**/**/*.hpp" ,
        #        "project/**/**/**/*.c" ,
        #        "project/**/**/**/*.cpp" ,
        #        "project/**/**/**/**/*.h" ,
        #        "project/**/**/**/**/*.hpp" ,
        #        "project/**/**/**/**/*.c" ,
        #        "project/**/**/**/**/*.cpp" ,
        #        "project/**/**/**/**/**/*.h" ,
        #        "project/**/**/**/**/**/*.hpp" ,
        #        "project/**/**/**/**/**/*.c" ,
        #        "project/**/**/**/**/**/*.cpp" ,
        #        "project/**/**/**/**/**/**/*.h" ,
        #        "project/**/**/**/**/**/**/*.hpp" ,
        #        "project/**/**/**/**/**/**/*.c" ,
        #        "project/**/**/**/**/**/**/*.cpp"
        )


add_library(${PROJECT_NAME} SHARED ${SRC} project/cheat/hooks/functions/run_command/run_command.cpp project/cheat/hooks/functions/run_command/run_command.hpp project/cheat/sdk/structs/c_command_context.hpp project/cheat/hooks/functions/item_post_frame/item_post_frame.cpp project/cheat/hooks/functions/item_post_frame/item_post_frame.hpp project/cheat/hooks/functions/get_time/get_time.cpp project/cheat/hooks/functions/get_time/get_time.hpp)

find_library(D3D9_LIBRARY d3d9.lib PATHS "$ENV{DXSDK_DIR}/Lib/x86")
find_library(D3DX9_LIBRARY d3dx9.lib PATHS "$ENV{DXSDK_DIR}/Lib/x86")
target_link_libraries(${PROJECT_NAME} "${D3D9_LIBRARY}" "${D3DX9_LIBRARY}")
link_directories("$ENV{DXSDK_DIR}/Lib/x86")
include_directories("$ENV{DXSDK_DIR}/Include")

add_definitions(/MP)
add_compile_options(/DEBUG FULL)
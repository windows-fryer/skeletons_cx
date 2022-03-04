# thank you to cristeigabriel for helping me with this!
cmake_minimum_required(VERSION 3.21)
project(skeletons_cx)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SRC
        "project/**/*.c" ,
        "project/**/*.cpp"
        )


add_library(${PROJECT_NAME} SHARED ${SRC})

find_library(D3D9_LIBRARY d3d9.lib PATHS "$ENV{DXSDK_DIR}/Lib/x86")
find_library(D3DX9_LIBRARY d3dx9.lib PATHS "$ENV{DXSDK_DIR}/Lib/x86")
target_link_libraries(${PROJECT_NAME} "${D3D9_LIBRARY}" "${D3DX9_LIBRARY}")
link_directories("$ENV{DXSDK_DIR}/Lib/x86")
include_directories("$ENV{DXSDK_DIR}/Include")

add_definitions(/MP)
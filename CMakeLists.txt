cmake_minimum_required(VERSION 3.1)

project(realaenseCapture)
set(CMAKE_CXX_STANDARD 11)


set(OpenCV_STATIC ON)
set(OpenCV_DIR E:/thirdparty/build/install/win64)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(inc)

include_directories($ENV{RealSense_INCLUDE_DIR})
link_directories($ENV{RealSense_LIBRARY_DIRS})

if (NOT ROOT_DIR_DEFINED)
    add_definitions(-DROOT_DIR="${PROJECT_SOURCE_DIR}")
    set(ROOT_DIR_DEFINED ON)
endif()


FILE(GLOB_RECURSE CPP_SRC_LIST "src/*.cpp")

add_executable(realaenseCapture main.cpp ${CPP_SRC_LIST})
target_link_libraries(realaenseCapture ${OpenCV_LIBS} realsense2)

cmake_minimum_required(VERSION 2.9)
project(MatrixTransform)

set(CMAKE_CXX_STANDARD 11)
find_package(PCL 1.7 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(MatrixTransform main.cpp)

target_link_libraries(MatrixTransform ${PCL_LIBRARIES})
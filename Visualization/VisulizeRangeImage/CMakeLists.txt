cmake_minimum_required(VERSION 3.9)
project(VisulizeRangeImage)

set(CMAKE_CXX_STANDARD 11)

find_package(PCL 1.7 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(VisulizeRangeImage main.cpp)

target_link_libraries(VisulizeRangeImage ${PCL_LIBRARIES})
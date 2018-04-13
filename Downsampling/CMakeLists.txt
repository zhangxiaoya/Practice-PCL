cmake_minimum_required(VERSION 2.8)

project(downsampling)
find_package(PCL 1.2 REQUIRED)

add_compile_options(-std=c++11)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(downsampling main.cpp)

target_link_libraries(downsampling ${PCL_LIBRARIES})

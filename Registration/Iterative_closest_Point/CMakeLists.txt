cmake_minimum_required(VERSION 3.9)
project(Iterative_closest_Point)

set(CMAKE_CXX_STANDARD 11)

find_package(PCL 1.7 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(Iterative_closest_Point main.cpp)

target_link_libraries(Iterative_closest_Point ${PCL_LIBRARIES})
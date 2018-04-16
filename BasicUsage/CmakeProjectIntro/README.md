# 一个基本的CMakelists.txt文件

一个最简单的CMakeLists文件如下：
```
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(MY_GRAND_PROJECT)

find_package(PCL 1.7 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(pcd_write_test pcd_write.cpp)

target_link_libraries(pcd_write_test ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES})
```
当PCL库找到后，会给下面的变量赋值。
```
PCL_FOUND: set to 1 if PCL is found, otherwise unset
PCL_INCLUDE_DIRS: set to the paths to PCL installed headers and the dependency headers
PCL_LIBRARIES: set to the file names of the built and installed PCL libraries
PCL_LIBRARY_DIRS: set to the paths to where PCL libraries and 3rd party dependencies reside
PCL_VERSION: the version of the found PCL
PCL_COMPONENTS: lists all available components
PCL_DEFINITIONS: lists the needed preprocessor definitions and compiler flags
```

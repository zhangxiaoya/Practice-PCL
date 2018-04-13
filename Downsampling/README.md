# 使用Voxel降采样点云。
给定一个数据集，使用voxelized grid 的方法降采样点云数据集。
给定一个点云数据集，将这些点云数据集作为输入，创建一个3D Voxel Grid，可以理解Voxel Grid是由一些小的3D小块组成，然后在每个3D的小块中，用其中点的形心近似表示这些点，这种方法比使用Voxel的中心表示它们慢一点，但是对于下垫面的表达更准确。

首先在[这里](https://raw.github.com/PointCloudLibrary/data/master/tutorials/table_scene_lms400.pcd)下载点云的数据集。

读取点云：
```
 // 创建两个指向点云的指针
    pcl::PCLPointCloud2::Ptr cloud(new pcl::PCLPointCloud2());
    pcl::PCLPointCloud2::Ptr cloudFiltered(new pcl::PCLPointCloud2());

    std::string filename = "../table_scene_lms400.pcd";
    pcl::PCDReader reader;
    reader.read(filename,*cloud);
    std::cout << "Point Cl  oud before filter" << cloud->width * cloud->height << " Data Points (" << pcl::getFieldsList(*cloud) <<")."<< std::endl;
```

创建一个Voxel Grid，并设置在不同维度的leaf精度,最后输出滤波后的点云。
```
pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
    sor.setInputCloud(cloud);
    sor.setLeafSize(0.01f,0.01f,0.01f);
    sor.filter(*cloudFiltered);

    std::cout << "Point Cloud after filter" << cloudFiltered->width * cloudFiltered->height
              << " Data Points (" << pcl::getFieldsList(*cloudFiltered)
              << ")." << std::endl;

    pcl::PCDWriter writer;
    writer.write("table_scene_lms400_down_sampled.pcd", *cloudFiltered);
```

CMakeLists.txt文件
```
cmake_minimum_required(VERSION 2.8)

project(downsampling)
find_package(PCL 1.2 REQUIRED)

add_compile_options(-std=c++11)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(downsampling main.cpp)

target_link_libraries(downsampling ${PCL_LIBRARIES})
```

使用pcl_viewer查看点云。
```
pcl_viewer table_scene_lms400_down_sampled.pcd
```
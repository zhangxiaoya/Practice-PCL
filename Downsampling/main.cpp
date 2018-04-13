//
// Created by ynzhang on 18-4-13.
//

#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/voxel_grid.h>

int main()
{
    // 创建两个指向点云的指针
    pcl::PCLPointCloud2::Ptr cloud(new pcl::PCLPointCloud2());
    pcl::PCLPointCloud2::Ptr cloudFiltered(new pcl::PCLPointCloud2());

    std::string filename = "../table_scene_lms400.pcd";
    pcl::PCDReader reader;
    reader.read(filename,*cloud);
    std::cout << "Point Cl  oud before filter" << cloud->width * cloud->height << " Data Points (" << pcl::getFieldsList(*cloud) <<")."<< std::endl;

    // 创建一个Voxel滤波器
    pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
    sor.setInputCloud(cloud);
    sor.setLeafSize(0.01f,0.01f,0.01f);
    sor.filter(*cloudFiltered);

    std::cout << "Point Cloud after filter" << cloudFiltered->width * cloudFiltered->height
              << " Data Points (" << pcl::getFieldsList(*cloudFiltered)
              << ")." << std::endl;

    pcl::PCDWriter writer;
    writer.write("table_scene_lms400_down_sampled.pcd", *cloudFiltered);
    return 0;
}
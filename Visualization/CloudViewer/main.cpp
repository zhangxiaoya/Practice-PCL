#include <iostream>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>

int user_data;

void viewerOneOff(pcl::visualization::PCLVisualizer& viewer)
{
    viewer.setBackgroundColor(1.0, 0.5, 1.0);
    pcl::PointXYZ o;
    o.x = 1.0;
    o.y = 0;
    o.z = 0;
    viewer.addSphere(o, 0.25,"sphere", 0);
    std::cout << "i only run once" << std::endl;
}

void viewerPsycho(pcl::visualization::PCLVisualizer& viewer)
{
    static unsigned  count = 0;
    std::stringstream ss;
    ss << "Once per viewer loop: "<< count ++;
    viewer.removeShape("text", 0);
    viewer.addText(ss.str(), 200, 300, "text", 0);

    user_data ++;
}
int main()
{
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGBA>);
    pcl::io::loadPCDFile("../my_point_cloud.pcd", *cloud);
    pcl::visualization::CloudViewer viewer("Cloud Viewer");

    // 阻塞进程，直到点云数据被渲染完成
    viewer.showCloud(cloud);

    // 更高级的使用PCLVisualizer（PCLCloudViewer的后端）
    viewer.runOnVisualizationThreadOnce(viewerOneOff);

    viewer.runOnVisualizationThread(viewerPsycho);
    while(!viewer.wasStopped())
    {
        user_data++;
    }

    return 0;
}
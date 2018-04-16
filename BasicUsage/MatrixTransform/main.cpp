#include <iostream>
#include <pcl/io/ply_io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/console/parse.h>
#include <pcl/common/transforms.h>
#include <pcl/visualization/pcl_visualizer.h>

using namespace pcl;
using namespace std;

void showHelper(char* program_name)
{
    cout << endl;
    cout <<"Usage: " << program_name << " cloud_filename.[pcd][ply]" << endl;
    cout << "-h:  Show this help" << endl;
}
int main(int argc, char* argv[])
{
    if(console::find_switch(argc, argv, "-h") || console::find_switch(argc, argv, "--help"))
    {
        showHelper(argv[0]);
        return 0;
    }
    vector<int> filenames;
    bool file_is_pcd = false;

    filenames = console::parse_file_extension_argument(argc, argv, ".ply");
    if(filenames.size() != 1)
    {
        filenames = console::parse_file_extension_argument(argc, argv, ".pcd");
        if(filenames.size() != 1)
        {
            showHelper(argv[0]);
            return -1;
        }
        else
        {
            file_is_pcd = true;
        }
    }

    // 加载点云数据文件
    PointCloud<PointXYZ>::Ptr source_cloud(new PointCloud<PointXYZ>());
    if(file_is_pcd)
    {
        if(0 > io::loadPCDFile(argv[filenames[0]],*source_cloud))
        {
            cout << "Error loading point cloud" << argv[filenames[0]] << endl<< endl;
            showHelper(argv[0]);
            return  -1;
        }
    }
    else
    {
        if(0 > io::loadPLYFile(argv[filenames[0]], *source_cloud))
        {
            cout <<" Error loading point cloud" << argv[filenames[0]] << endl<< endl;
            showHelper(argv[0]);
            return -1;
        }
    }

    // 定义旋转矩阵
    Eigen::Matrix4f transform_1 = Eigen::Matrix4f::Identity();

    float theta = M_PI / 4;
    transform_1(0,0) = cos(theta);
    transform_1(0,1) = -sin(theta);
    transform_1(1,0) = sin(theta);
    transform_1(1,1) = cos(theta);

    // X 轴平移2.5
    transform_1(0,3) = 2.5;

    printf("Method #1: using a Matrix4f\n");

    Eigen::Affine3f transform_2 = Eigen::Affine3f::Identity();
    transform_2.translation() << 2.5 ,0.0,0.0;

    transform_2.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitZ()));

    printf("\nMethod #2 using an Affine3d\n");
    cout << transform_2.matrix()<<endl;

    PointCloud<PointXYZ>::Ptr transformed_cloud(new PointCloud<PointXYZ>());
    transformPointCloud(*source_cloud, *transformed_cloud, transform_2);

    printf("\n Point cloud colors: white = original point cloud\n"
           "                       red = transformed point cloud\n");
    visualization::PCLVisualizer viewer("Matrix transformation example");

    visualization::PointCloudColorHandlerCustom<PointXYZ> source_cloud_color_handler(source_cloud, 255,255,255);
    viewer.addPointCloud(source_cloud,source_cloud_color_handler, "original_cloud");

    visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> transformed_cloud_color_handler (transformed_cloud, 230, 20, 20); // Red
    viewer.addPointCloud (transformed_cloud, transformed_cloud_color_handler, "transformed_cloud");

    viewer.addCoordinateSystem(1.0, "cloud", 0);
    viewer.setBackgroundColor(0.05,0.05, 0.05,0);
    viewer.setPointCloudRenderingProperties(visualization::PCL_VISUALIZER_POINT_SIZE,2,"original_cloud");
    viewer.setPointCloudRenderingProperties(visualization::PCL_VISUALIZER_POINT_SIZE,2,"transformed_cloud");

    while(!viewer.wasStopped())
    {
        viewer.spinOnce();
    }
    return 0;
}
# 使用InteratIve Closenet Point估算两个点云数据集的刚体变换

# 代码解释

创建两个纸箱pcl::PointCloud<pcl::PointXYZ>的boost共享指针，并初始化指针，指向一个点云数据集的空间。
```
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_in (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_out (new pcl::PointCloud<pcl::PointXYZ>);     

```
这里的PointXYZ点类的结构如下所示：
```
struct PointXYZ
{
    float x;
    float y;
    float z;
}
```

向点云数据集中填充随机的点数据，设置逼近参数（数据集的宽和高，还有是否是稠密数据集），然后输出点云数据集中的点的数量，以及实际保存的数据。两个数据集是完全相同的。
```
 cloud_in->width    = 5;
  cloud_in->height   = 1;
  cloud_in->is_dense = false;
  cloud_in->points.resize (cloud_in->width * cloud_in->height);
  for (size_t i = 0; i < cloud_in->points.size (); ++i)
  {
    cloud_in->points[i].x = 1024 * rand () / (RAND_MAX + 1.0f);
    cloud_in->points[i].y = 1024 * rand () / (RAND_MAX + 1.0f);
    cloud_in->points[i].z = 1024 * rand () / (RAND_MAX + 1.0f);
  }
  std::cout << "Saved " << cloud_in->points.size () << " data points to input:"
      << std::endl;
  for (size_t i = 0; i < cloud_in->points.size (); ++i) std::cout << "    " <<
      cloud_in->points[i].x << " " << cloud_in->points[i].y << " " <<
      cloud_in->points[i].z << std::endl;
  *cloud_out = *cloud_in;
  std::cout << "size:" << cloud_out->points.size() << std::endl;
```
但是下面修改了输出数据集的数据值，在文档中描述的是进行了简单的刚体数值变换。
```
for (size_t i = 0; i < cloud_in->points.size (); ++i)
    cloud_out->points[i].x = cloud_in->points[i].x + 0.7f;
  std::cout << "Transformed " << cloud_in->points.size () << " data points:"
      << std::endl;
  for (size_t i = 0; i < cloud_out->points.size (); ++i)
    std::cout << "    " << cloud_out->points[i].x << " " <<
      cloud_out->points[i].y << " " << cloud_out->points[i].z << std::endl;
```
然后，使用ICP方法对两个数据集估计刚体变换矩阵。在文档中，source数据值设置的函数是setInputCloud，但是使用的时候，提示这个方法已经被遗弃了，使用setInputSource，应该是与算法描述对应起来。Source可以理解是开始，target理解为结束，即，从数据集source变换到数据集B的刚体变换。

```
    pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
    icp.setInputSource(cloud_in);
    icp.setInputTarget(cloud_out);
```
创建一个点云数据集Final，用来存放最终的结果。如果两个数据集能够正确的对其，也就是数据集可以经过变换矩阵变换，那么hasConverged函数返回1，然后输出适合分值和最终的变换信息。
```
pcl::PointCloud<pcl::PointXYZ> Final;
  icp.align(Final);
  std::cout << "has converged:" << icp.hasConverged() << " score: " <<
  icp.getFitnessScore() << std::endl;
  std::cout << icp.getFinalTransformation() << std::endl;
```
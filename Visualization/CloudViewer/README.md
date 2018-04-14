# 使用CloudViewer查看点云数据

CloudViewer是一个直接、简单使用的点云数据可视化工具，使用简短的代码就能查看点云数据，但是不能在多线程环境中使用。
比如下面的一段代码可视化点云数据。

```
pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud;
// 加载点云数据
pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");
viewer.showCloud(cloud);
while(!viewer.wasStopped())
{

}
```

PCLVisualizer类是CloudViewer类的后端，但是它运行在自己的线程中，要想访问它必须使用回调函数，来避免可视化的同步问题。然后，必须在代码中避免竞争条件，回调函数必须从visualization线程调用。
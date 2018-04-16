# 编译PCL的依赖项
主要有下面的几个：
1. boost库，在PCL中使用了大量的Boost智能指针
2. Eigen，是一个高效的矩阵计算库，图像类的开源库大部分都有它的影子，包括OpenCV
3. FLANN，一个最近邻搜索算法的实现库，几乎在所有的PCL库都有使用
4. VTK，在PCL Visualization中使用，用于可视化。
5. Qhull，一个图形库，在pcl surface中使用
6. OpenNI，读取深度相机的库
7. CUDA，用于并行加速的库。

其中后面的三个库是可选的。其他是必须的。
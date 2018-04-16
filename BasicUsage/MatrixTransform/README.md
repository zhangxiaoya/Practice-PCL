# 使用矩阵旋转一个点云

代码首先是检测参数输入，然后读取点云数据文件。

两种创建变换矩阵的方式，第一种是直接使用矩阵的形式；
```
  /* Reminder: how transformation matrices work :

           |-------> This column is the translation
    | 1 0 0 x |  \
    | 0 1 0 y |   }-> The identity 3x3 matrix (no rotation) on the left
    | 0 0 1 z |  /
    | 0 0 0 1 |    -> We do not use this line (and it has to stay 0,0,0,1)

    METHOD #1: Using a Matrix4f
    This is the "manual" method, perfect to understand but error prone !
  */
  Eigen::Matrix4f transform_1 = Eigen::Matrix4f::Identity();

  loat theta = M_PI/4; // The angle of rotation in radians
  transform_1 (0,0) = cos (theta);
  transform_1 (0,1) = -sin(theta);
  transform_1 (1,0) = sin (theta);
  transform_1 (1,1) = cos (theta);
  //    (row, column)

  // Define a translation of 2.5 meters on the x axis.
  transform_1 (0,3) = 2.5;

  // Print the transformation
  printf ("Method #1: using a Matrix4f\n");
  std::cout << transform_1 << std::endl;
```
使用Eigen定义一个4*4的矩阵，然后定义一个绕Z轴的一个45度旋转，和2.5个单位的平移。
```
    |  cos(θ) -sin(θ)  0.0 |
R = |  sin(θ)  cos(θ)  0.0 |
    |  0.0     0.0     1.0 |

t = < 2.5, 0.0, 0.0 >
```
第二种旋转矩阵是用EigenAffine3f定义的，简单容易理解。
```
  Eigen::Affine3f transform_2 = Eigen::Affine3f::Identity();

  // Define a translation of 2.5 meters on the x axis.
  transform_2.translation() << 2.5, 0.0, 0.0;

  // The same rotation matrix as before; theta radians around Z axis
  transform_2.rotate (Eigen::AngleAxisf (theta, Eigen::Vector3f::UnitZ()));

  // Print the transformation
  printf ("\nMethod #2: using an Affine3f\n");
  std::cout << transform_2.matrix() << std::endl;
```

然后，使用common模块中的变换函数，对点云数据应用变换。
最后显示原始的点云和变换后的点云。
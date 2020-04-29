# Delaunay_mesh_demo

本项目整合了项目 [delaunator-cpp](https://github.com/abellgithub/delaunator-cpp) 与项目 [delaunay-triangulation](https://github.com/Bl4ckb0ne/delaunay-triangulation)，并完成了以下工作：

## 简述
* 简化依赖，仅需opencv即可运行;
* 对比这两个工程实现的性能;
* 基于 `delaunator-cpp` 项目开发一个小demo，完成以下功能：
    * 输入单张图片，可以检测特征点，进行三角化，并显示;
    * 输入数字，随机生成点，进行三角化，并演示生成的过程。

## 如何使用

### 编译 
```
cd ${workplace}/delaunay-mesh
mkdir build
cd build
cmake ..
make -j4
```

### 运行
#### delaunator-cpp
```
${workplace}/delaunay-mesh/build/algor_1_test
```

#### delaunay-triangulation
```
${workplace}/delaunay-mesh/build/algor_2_test
```

### 对比程序
```
${workplace}/delaunay-mesh/build/compare_test

# 指定用于三角化的点的数量
${workplace}/delaunay-mesh/build/compare_test 100
```

### dmeo
```
${workplace}/delaunay-mesh/build/demo

# 指定用于三角化的点的数量
${workplace}/delaunay-mesh/build/demo 40

# 指定用于三角化的图片目录地址
${workplace}/delaunay-mesh/build/demo ../tese.png

```
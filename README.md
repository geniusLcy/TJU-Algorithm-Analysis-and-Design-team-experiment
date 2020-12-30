Note: Experiment has finished, this repository will be **archived**.

# 《算法分析与设计》小组上机实验

## 动态规划法、回溯法、分支限界法求解0/1背包问题

## General

```
./algorithm_exp/
├── README.md                   --README文件
├── backTracking_solution       --回溯法解决方案
├── branchAndBound_solution     --分支限界法解决方案
├── data_set                    --数据集：Florida State University
└── dp_solution                 --动态规划算法解决方案

4 directories, 1 file
```

数据集放置于 `data_set` 目录下，各个算法解决方案放置于 `*_solution` 目录下。所有 `*_solution` 目录下有 `*_file_ver.cpp` 和 `*_manual_ver.cpp` 2个文件 ，二者算法完全一致。前者预设路径，会自动从 `data_set` 读取数据并最终验证正确性输出结果；后者可以读取控制台键入的数据并运行算法求解，最后输出结果。

要通过数据集验证各个算法的正确性，只需编译运行 `*_file_ver.cpp` 即可。*为对应算法的名称。

```bash
cd .\*_solution\
g++ .\*_file_ver.cpp -o *_file_ver
.\*_file_ver.exe
```

## 编译运行环境说明

- OS: Windows 10
- g++ version: 8.1.0(MinGW-W64)

由于OS不同可能导致路径表示方式不同，在非 Windows 操作系统下请自行修改 `*_file_ver.cpp` 中的表示路径。

## 数据集说明

于 `data_set` 目录下，采用 Florida State University 提供的8个[数据集](https://people.sc.fsu.edu/~jburkardt/datasets/knapsack_01/knapsack_01.html)：

```
./data_set
├── P01
├── P02
├── P03
├── P04
├── P05
├── P06
├── P07
└── P08

8 directories, 0 files
```

`P01 - P08` 为对应的数据集，对于其中的每个数据集(以下均以P01为例)，目录结构如下：

``` bash
./data_set/P01
├── info.txt    --information of data sets
├── p01_c.txt   --the knapsack capacity
├── p01_p.txt   --the profits of each object
├── p01_s.txt   --the optimal selection of weights
└── p01_w.txt   --the weights of the objects

0 directories, 5 files
```

`info.txt` 为自行添加的描述文件，记录对于数据集的具体描述，不包含于原 Florida State University 所提供的数据集中。查看 `info.txt` 可以得到对于当前数据集以及其中各个文件的解释：

``` 
P01 is a set of 10 weights and profits for a knapsack of capacity 165.
.
├── p01_c.txt, the knapsack capacity
├── p01_w.txt, the weights of the objects
├── p01_p.txt, the profits of each object
└── p01_s.txt, the optimal selection of weights

```

## 动态规划算法解决方案

于 `dp_solution` 目录下:

```
./dp_solution           --核心算法为 solution 函数
├── dp_file_ver.cpp     --自动从 data_set 读取数据集进行测试，打印输出结果
└── dp_manual_ver.cpp   --可以手动键入数据测试算法

0 directories, 2 files
```

## 回溯法解决方案

于 `backTracking_solution` 目录下:

```
./backTracking_solution/
├── backTracking_file_ver.cpp     --自动从 data_set 读取数据集进行测试，打印输出结果
└── backTracking_manual_ver.cpp   --可以手动键入数据测试算法

0 directories, 2 files
```

## 分支限界算法解决方案

于 `branchAndBound_solution` 目录下:

```
./branchAndBound_solution/
├── branchAndBound_file_ver.cpp     --自动从 data_set 读取数据集进行测试，打印输出结果
└── branchAndBound_manual_ver.cpp   --可以手动键入数据测试算法

0 directories, 2 files
```

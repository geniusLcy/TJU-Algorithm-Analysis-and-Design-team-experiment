# 《算法分析与设计》上机实验选题及要求

## 1. 实验目的

- 掌握利用算法进行问题求解的实验流程

- 强化对课堂所学算法原理的理解

- 提升利用算法原理进行编码实践的能力

- 了解算法研究的前沿动态，拓展算法改进的思路

## 2. 实验内容及要求

实验采取自由分组的方式完成，每组至多5人，编程语言推荐但不限于`c/c + +`。要求每组从下列主题中选择1 项作为实验内容，完成实验设计、过程实现、结果分析、实验总结及实验报告撰写。

### 2.3 问题求解类

- 对于01背包问题的至少2个数据集，利用动态规划、回溯及分支限界三种算法进行求解

要求：分析不同算法解决01背包问题的复杂度，归纳不同求解算法的优缺点。

## 3. 实验报告要求

- 题目：60 字以内，如：“动态规划算法问题求解性能比较”

- 摘要：300 字左右，如：“本实验针对... 问题，利用... 算法，对.... 数据集进行性能分析。实验结果表明...”

- 正文：5-8 ⻚，包括实验目的、实验设计流程、代码实现、实验结果及复杂性分析

- 总结：200 字左右，包括实验过程总结和得出的主要结论。

## 4. 附件1: 问题求解数据集

### 4.1 0/1 背包问题

- Florida State University: 8 个数据集。[Link](https://people.sc.fsu.edu/~jburkardt/datasets/knapsack_01/knapsack_01.html)

- Unicauca University: 31 个数据集。[Link](http://artemisa.unicauca.edu.co/~johnyortega/instances_01_KP/)

----------

# 小组选题任务: 动态规划法、回溯法、分支限界法求解0/1背包问题


## 数据集说明

于 `data_set` 目录下，采用 Florida State University 提供的8个数据集：

``` bash
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


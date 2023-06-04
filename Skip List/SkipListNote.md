# SkipList

#### 散列：循值访问

//基本原理掌握

主要思想：减而治之

### 跳转表：结构

 //基本数据结构

![跳转表结构](https://github.com/starCloudXY/SE-ADS/blob/main/Pictures/01-01.png)

#### 跳转表：算法

 // 理解代码，不需要复杂度分析

header:最左侧表头

forward[i]:第i层右侧的节点

![查找](https://github.com/starCloudXY/SE-ADS/blob/main/Pictures/01-02.png)

- 查找
  
  ![](https://github.com/starCloudXY/SE-ADS/blob/main/Pictures/01-03.png)

- 插入
  
  找到对应位置加入节点，从最底层（从1开始）到level层逐渐更新指针
  
  ![跳表插入](https://github.com/starCloudXY/SE-ADS/blob/main/Pictures/01-04.png)

- 删除
  
  ![删除](https://github.com/starCloudXY/SE-ADS/blob/main/Pictures/01-05.png)

#### 应用：LSM算法

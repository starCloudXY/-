# 并行编程

### 串线程同步-互斥锁//掌握

lock()的在语义上只能让一个调用者返回，另一个调用者必须阻塞，直到拿到改锁的调用者调用 unlock()之后，才能从 lock()中返回

### 并发List// 理解

插入时，用互斥锁来保护对head指针的操作

<img title="" src="./Pictures/parallel_1.png" alt="" width="249">

查找时用粗粒度的锁保护整个函数

<img title="" src="./Pictures/parallel_2.png" alt="" width="440">

### 并发散列表 //理解

基于并发链表设计并发散列表，每个散列桶各使用自己的锁。

<img title="" src="./Pictures/parallel_3.png" alt="" width="421">

### 死锁//理解

![](./Pictures/parallel_4.png)

t1拿到了mtx1()的锁，t2拿到了mtx2()的锁，t1阻塞在第11行，t2阻塞在第19行。

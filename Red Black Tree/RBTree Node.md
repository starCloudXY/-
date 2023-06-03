# 红黑树

- ### 定义与性质
  
  - 红黑树是一种含有红黑结点并能自平衡的二叉查找树
  - 任意结点都有颜色，红色或者黑色
  - 红黑树中根节点一定是黑色的
  - 红黑树中的 null 位置看作是黑色
  - 红黑树中红色不能与红色相邻
  - 从根到所有 null 的路径上黑色结点的个数相同
  - 红黑树中，最长的路径的长度，不会超过最短的路径的长度的2倍
  - 时间复杂度：Olog（n）

- ### 插入操作过程遵循的原则
  
  - start：一颗红黑树
  - 按照搜索树的特征进行插入
  - 插入时：插入的结点一定是红色的，如果为黑色，会破坏第五条规则
    - 如果插入的结点是根节点，将颜色改为黑色
    - 插入/调整的结点的父结点是黑色的，则插入完成
    - 插入的结点的父结点是红色的，则需要修复，且继续向上调整，直到为根或满足规则
    - 如果根修改之后为红色，一定要改过来，改为黑色
  - end：一颗红黑树

- ### 修复方法
  
  - 前提条件：插入的结点（cur）是红色，cur的父结点（parent）是红色的，这样的需要修复
  
  - 修复要点：保证修复操作前和修复操作后的黑色结点的数量不变
  
  - 可推断出：cur 的祖父结点即父亲的父亲（grandpa）一定是黑色，否则插入当前结点之前已经违反了红黑树的规则
  
  - 如图：![在这里插入图片描述](https://img-blog.csdnimg.cn/20200407161859775.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjEyNTMxMA==,size_16,color_FFFFFF,t_70)
  
  - 分情况讨论：
    
    - **情况1：uncle 存在（uncle != null），并且 uncle 的颜色是红色**
      
      - 修复方法：grandpa 由黑变红，parent & uncle 由红变黑；
      - eg：  
        ![在这里插入图片描述](https://img-blog.csdnimg.cn/20200407162019915.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjEyNTMxMA==,size_16,color_FFFFFF,t_70)
    
    - **情况2**：uncle 不存在，或者 uncle 存在但是颜色是黑色
      
      - **情况2.1：cur 是 parent 左孩子，且 parent 是 grandpa 的左孩子****
        
        - 修复方法： grandpa 右旋之后颜色变为红色，parent 的颜色变为黑色
        - eg：![在这里插入图片描述](https://img-blog.csdnimg.cn/20200407162212713.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjEyNTMxMA==,size_16,color_FFFFFF,t_70)
      
      - **情况2.2：cur 是 parent 的右孩子，且 parent 是grandpa 的右孩子**
        
        - 修复方法：grandpa 左旋后颜色变为红色，parent 颜色变为黑色
        - eg:![在这里插入图片描述](https://img-blog.csdnimg.cn/20200407162258775.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjEyNTMxMA==,size_16,color_FFFFFF,t_70)
    
    - **情况2.3：cur 是 parent 的右孩子 ，parent 是 grandpa 的左孩子**
      
      - 修复方法：对 parent 左旋之后将 parent 和 cur 的名称交换，再按照2.1的情况处理
      - eg:![在这里插入图片描述](https://img-blog.csdnimg.cn/20200407162350203.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjEyNTMxMA==,size_16,color_FFFFFF,t_70)
    
    - **情况2.4： cur 是 parent 的左孩子 ，parent 是 grandpa 的右孩子**
      
      - 修复方法：对 parent 右旋之后将 parent 和 cur 的名称交换，再按照2.2的情况处理
      - eg:![在这里插入图片描述](https://img-blog.csdnimg.cn/20200407162603794.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjEyNTMxMA==,size_16,color_FFFFFF,t_70)

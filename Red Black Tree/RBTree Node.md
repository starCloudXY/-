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
      
      - **情况2.1：cur 是 parent 左孩子，且 parent 是 grandpa 的左孩子**
        
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
        
        ## 红黑树到2-3树的转化
        
        ![](https://pic3.zhimg.com/80/v2-41c2111d38d3495093b735e748524bfa_1440w.webp)
        
        ---
        
        相关题目:
        
        请分析红黑树相比于平衡二又树插入及查找的操作过程，并分析二者在插入和查找操作上的效率对比(可从树结构、旋转次数的角度考虑)。另外测试时同学们发现顺序插入往往比乱序插入要快，请分析原因。
        
        ##### 顺序较快原因：
        
        红黑树和平衡二叉树具有自平衡特性，在顺序插入的情况下，每次插入操作后，树的不平衡程度相对较小，需要进行的旋转次数也较少。
        
        ##### 操作过程以及效率对比：
        
        插入操作：
        
        - 平衡二叉树的插入操作：在平衡二叉树中，插入新节点后，可能会导致树失去平衡，需要通过旋转操作来重新平衡树。平衡二叉树在插入节点后，可能需要进行多次旋转操作来维持平衡性。
        - 红黑树的插入操作：红黑树通过一系列的规则来保持平衡，插入节点时，首先按照二叉搜索树的规则将节点插入。然后，通过颜色变换和旋转操作来满足红黑树的五个性质，保持树的平衡。红黑树在插入操作中最多需要进行三次旋转。
        1. 查找操作：
           
           - 平衡二叉树的查找操作：在平衡二叉树中，查找操作与普通二叉搜索树相同，通过比较节点值，根据二叉搜索树的性质进行查找。由于平衡二叉树保持了平衡，其查找操作的时间复杂度为O(log n)，其中n是树中节点的数量。
           - 红黑树的查找操作：红黑树的查找操作与普通二叉搜索树相同，时间复杂度也是O(log n)。红黑树的平衡性质可以保证树的高度较小，因此查找操作通常比较高效。
        
        效率对比：
        
        - 在插入操作上，红黑树相对于平衡二叉树的优势在于它的插入过程中最多只需要进行三次旋转操作，而平衡二叉树可能需要多次旋转来维持平衡。因此，在插入大量节点的情况下，红黑树的性能可能更好。
        - 在查找操作上，两者的时间复杂度相同，都是O(log n)。红黑树的旋转操作可能稍微多一些，但由于树的高度较小，查找操作的效率通常是可接受的。

---

旋转次数最多的情况：

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200407162019915.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjEyNTMxMA==,size_16,color_FFFFFF,t_70)

此时若祖父结点的父节点也为红色则需进行旋转操作：最多的情况为进行一次染色后，先进行一次右旋，再进行一次左旋并改变颜色。

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200407162603794.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjEyNTMxMA==,size_16,color_FFFFFF,t_70)![在这里插入图片描述](https://img-blog.csdnimg.cn/20200407162212713.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80MjEyNTMxMA==,size_16,color_FFFFFF,t_70)

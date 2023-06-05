### 3.Splay Trees

avl:

– zig  
• The target node is the child of the current node

– zig-zig  
• The three nodes of interest form a straight line  
– zig-zag  
• The three nodes of interest form a zig-zag line

本质上是把所要查找的点提到顶端

![](C:\Users\BOOK3\Desktop\高级数据结构\Pictures\2023-06-02-17-25-11-image.png)  

![](C:\Users\BOOK3\Desktop\高级数据结构\Pictures\2023-06-02-17-15-14-image.png)

![](C:\Users\BOOK3\Desktop\高级数据结构\Pictures\2023-06-02-17-23-35-image.png)

算法：

> ```c
> 描述：在查询一个节点后进行伸展旋转，将其推到根节点位置
> 输入：查找的节点的值x，伸展树树根root
> 输出：新的树根
> 初始化leftHeader=headerNode，rightHeader=headerNode
> 初始化leftMax=leftHeader,rightMin=rightHeader
> 循环
>     if x<root节点的值，说明在左子树
>         if root.left为null，说明左子树为空，查找失败
>             调整结束，跳出循环
>         if x小于root.left的值，一字型情况
>             root=rotateWithLeftChild(root)，将root的左孩子调整到root的位置
>         //不论是x小于还是大于root.left的值，下一步都是将root作为R的最左孩子的左儿子
>         rightMin.left=root
>         rightMin=root//调整最左孩子
>         root=root.left
>     if x>root节点的值，说明在右子树
>         如果root.right等于null,说明右子树为空，查找失败
>             调整结束，跳出循环
>         如果x大于root.right的值，右一字型情况
>             root=rotateWithRightChilde(root)
>         leftMax.right=root
>         leftMax=root
>         root=root.right
>     else 等于的情况
>         中树根已经为x，直接跳出循环
> 开始合并
> leftMax.right=root.left
> rightMin.left=root.right
> root.left=leftHeader.right
> root.right=rightHeader.left
> return root
> ```

相关代码:

```cpp
#include <iomanip>
#include <iostream>
using namespace std;
/*
 * 旋转key对应的节点为根节点，并返回值为根节点。
 *
 * 注意：
 *   (a)：伸展树中存在"键值为key的节点"。
 *          将"键值为key的节点"旋转为根节点。
 *   (b)：伸展树中不存在"键值为key的节点"，并且key < tree->key。
 *      b-1 "键值为key的节点"的前驱节点存在的话，将"键值为key的节点"的前驱节点旋转为根节点。
 *      b-2 "键值为key的节点"的前驱节点存在的话，则意味着，key比树中任何键值都小，那么此时，将最小节点旋转为根节点。
 *   (c)：伸展树中不存在"键值为key的节点"，并且key > tree->key。
 *      c-1 "键值为key的节点"的后继节点存在的话，将"键值为key的节点"的后继节点旋转为根节点。
 *      c-2 "键值为key的节点"的后继节点不存在的话，则意味着，key比树中任何键值都大，那么此时，将最大节点旋转为根节点。
 */
template <class T>
SplayTreeNode<T>* SplayTree<T>::splay(SplayTreeNode<T>* tree, T key)
{
    SplayTreeNode<T> N, *l, *r, *c;

    if (tree == NULL)
        return tree;

    N.left = N.right = NULL;
    l = r = &N;

    for (;;)
    {
        if (key < tree->key)
        {
            if (tree->left == NULL)
                break;
            if (key < tree->left->key)
            {
                c = tree->left;                           /* zig:rotate right */
                tree->left = c->right;
                c->right = tree;
                tree = c;
                if (tree->left == NULL)
                    break;
            }
            r->left = tree;                               /* link right */
            r = tree;
            tree = tree->left;
        }
        else if (key > tree->key)
        {
            if (tree->right == NULL)
                break;
            if (key > tree->right->key)
            {
                c = tree->right;                          /* zig:rotate left */
                tree->right = c->left;
                c->left = tree;
                tree = c;
                if (tree->right == NULL)
                    break;
            }
            l->right = tree;                              /* link left */
            l = tree;
            tree = tree->right;
        }
        else
        {
            break;
        }
    }

    l->right = tree->left;                                /* assemble */
    r->left = tree->right;
    tree->left = N.right;
    tree->right = N.left;

    return tree;
}
```

```cpp
/*
 * (递归实现)查找"伸展树x"中键值为key的节点
 */
template <class T>
SplayTreeNode<T>* SplayTree<T>::search(SplayTreeNode<T>* x, T key) const
{
    if (x==NULL || x->key==key)
        return x;

    if (key < x->key)
        return search(x->left, key);
    else
        return search(x->right, key);
}

template <class T>
SplayTreeNode<T>* SplayTree<T>::search(T key)
{
    return search(mRoot, key);
}

/*
 * 查找最小结点：返回tree为根结点的伸展树的最小结点。
 */
template <class T>
SplayTreeNode<T>* SplayTree<T>::minimum(SplayTreeNode<T>* tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->left != NULL)
        tree = tree->left;
    return tree;
}

template <class T>
T SplayTree<T>::minimum()
{
    SplayTreeNode<T> *p = minimum(mRoot);
    if (p != NULL)
        return p->key;

    return (T)NULL;
}

/*
 * 查找最大结点：返回tree为根结点的伸展树的最大结点。
 */
template <class T>
SplayTreeNode<T>* SplayTree<T>::maximum(SplayTreeNode<T>* tree)
{
    if (tree == NULL)
        return NULL;

    while(tree->right != NULL)
        tree = tree->right;
    return tree;
}

template <class T>
T SplayTree<T>::maximum()
{
    SplayTreeNode<T> *p = maximum(mRoot);
    if (p != NULL)
        return p->key;

    return (T)NULL;
}



template <class T>
void SplayTree<T>::splay(T key)
{
    mRoot = splay(mRoot, key);
}

/*
 * 将结点插入到伸展树中，并返回根节点
 *
 * 参数说明：
 *     tree 伸展树的根结点
 *     key 插入的结点的键值
 * 返回值：
 *     根节点
 */
template <class T>
SplayTreeNode<T>* SplayTree<T>::insert(SplayTreeNode<T>* &tree, SplayTreeNode<T>* z)
{
    SplayTreeNode<T> *y = NULL;
    SplayTreeNode<T> *x = tree;

    // 查找z的插入位置
    while (x != NULL)
    {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else if (z->key > x->key)
            x = x->right;
        else
        {
            delete z;
            return tree;
        }
    }

    if (y==NULL)
        tree = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    return tree;
}

template <class T>
void SplayTree<T>::insert(T key)
{
    SplayTreeNode<T> *z=NULL;

    // 如果新建结点失败，则返回。
    if ((z=new SplayTreeNode<T>(key,NULL,NULL)) == NULL)
        return ;

    // 插入节点
    mRoot = insert(mRoot, z);
    // 将节点(key)旋转为根节点
    mRoot = splay(mRoot, key);
}

/*
 * 删除结点(节点的键值为key)，返回根节点
 *
 * 参数说明：
 *     tree 伸展树的根结点
 *     key 待删除结点的键值
 * 返回值：
 *     根节点
 */
template <class T>
SplayTreeNode<T>* SplayTree<T>::remove(SplayTreeNode<T>* &tree, T key)
{
    SplayTreeNode<T> *x;

    if (tree == NULL)
        return NULL;

    // 查找键值为key的节点，找不到的话直接返回。
    if (search(tree, key) == NULL)
        return tree;

    // 将key对应的节点旋转为根节点。
    tree = splay(tree, key);

    if (tree->left != NULL)
    {
        // 将"tree的前驱节点"旋转为根节点
        x = splay(tree->left, key);
        // 移除tree节点
        x->right = tree->right;
    }
    else
        x = tree->right;

    delete tree;

    return x;

}

template <class T>
void SplayTree<T>::remove(T key)
{
    mRoot = remove(mRoot, key);
}

/*
 * 销毁伸展树
 */
template <class T>
void SplayTree<T>::destroy(SplayTreeNode<T>* &tree)
{
    if (tree==NULL)
        return ;

    if (tree->left != NULL)
        destroy(tree->left);
    if (tree->right != NULL)
        destroy(tree->right);

    delete tree;
}

template <class T>
void SplayTree<T>::destroy()
{
    destroy(mRoot);
}


#endif //SPLAYTREE_SPLAYTREE_H
```

![](C:\Users\BOOK3\AppData\Roaming\marktext\images\2023-06-05-21-38-08-image.png)

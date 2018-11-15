#### 1. 二叉查找树（Binary Search Tree）

二叉查找树是二叉树中最常用的一种类型，也叫二叉搜索树。二叉查找树是为了实现快速查找而生的，它不仅仅支持快速查找一个数据，还支持快速地插入、删除一个数据。

二叉查找树要求，在树中的任意一个节点，**其左子树中的每个节点的值，都要小于这个节点的值，而右子树节点的值都大于这个节点的值**。

![](https://upload-images.jianshu.io/upload_images/11895466-b6cf6d0bc43d61a3.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

##### 1.1. 二叉查找树的查找操作

在二叉查找树中查找时，我们先取根节点，如果其值正好等于要查找的数，就直接返回；如果大于要查找的数，我们就递归在左子树中进行查找；如果小于要查找的数，我们就递归在右子树中进行查找。

![](https://upload-images.jianshu.io/upload_images/11895466-1314d33bea0f68f1.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```c++
int Find_Tree(TreeNode *tree, int data)
{
    TreeNode *temp = tree;
    while(temp != NULL)
    {
        if (temp->val < data) temp = temp->right;
        else if (temp->val > data) temp = temp->left;
        else return temp->val;
    }
    return -1;
}
```

##### 1.2. 二叉查找树的插入操作

二叉查找树的插入操作和查找操作类似，新插入的数据一般都是在叶子节点上，因此我们需要从根节点开始，依次比较新插入的数据和节点数据的大小关系。

如果节点的数据小于新插入的数据，并且节点的右子树为空，我们就将新数据插入到右子节点的位置；如果右子树不为空，我们就继续递归查找右子树，直到找到正确的位置。同理，如果节点的数据大于新插入的数据，并且节点的左子树为空，我们就将新数据插入到左子节点的位置；如果左子树不为空，我们就继续递归查找左子树，直到找到正确的位置。


![](https://upload-images.jianshu.io/upload_images/11895466-837773fa36aa86c3.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```c++
void Insert_Tree(TreeNode *tree, int data)
{
    TreeNode *temp = tree;

    if (tree == NULL)
    {
        tree = new TreeNode(data);
        return;
    }

    while (temp != NULL)
    {
        if (temp->val < data)
        {
            if (temp->right == NULL)
            {
                temp->right = new TreeNode(data);
                return;
            }
            temp = temp->right;
        }
        else
        {
            if (temp->left == NULL)
            {
                temp->left = new TreeNode(data);
                return;
            }
            temp = temp->left;
        }
    }
}
```

##### 1.3. 二叉查找树的删除操作

二叉查找树的删除操作相对查找和插入操作来说比较复杂，可以分为以下几种情况。

如果待删除的节点没有子节点，我们直接删除掉这个节点，让父节点指向这个节点的指针指向 NULL 即可，如下图中的节点 55。

如果待删除的节点只有一个子节点，我们需要删除掉这个节点，然后让其子节点移到该节点位置，也即让父节点指向该节点的指针重新指向该节点的子节点，如下图中的节点 13。

如果待删除的节点同时具有左右子节点，我们需要找到这个节点的右子树中最小的节点，把它替换到待删除的节点上，然后再删除这个最小节点。因为这个最小节点肯定没有左子节点，因此我们可以应用上面的两条规则来删除这个最小节点。如下图中的节点 18。

![](https://upload-images.jianshu.io/upload_images/11895466-5524b4546e753e2c.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


```c++
void Delete_Tree(TreeNode *tree, int data)
{
    TreeNode *deleted_node = tree;      // 指向待删除节点
    TreeNode *parent = NULL;    // 指向待删除节点的父节点
    TreeNode *child = NULL;     // 指向待删除节点的子节点

    while (deleted_node != NULL && deleted_node->val != data)
    {
        parent = deleted_node;
        if (deleted_node->val < data) deleted_node = deleted_node->right;
        else deleted_node = deleted_node->left;
    }

    if (deleted_node == NULL) return; // 待删除节点为空，没找到

    TreeNode *min_node = tree;      // 指向右子树最小节点
    TreeNode *min_parent = NULL;    // 指向待右子树最小节点的父节点

    // 待删除节点有左右子节点，查找右子树的最小节点
    if (deleted_node->right != NULL && deleted_node->left != NULL)
    {
        min_node = deleted_node->right;
        while (min_node->left != NULL)
        {
            min_parent = min_node;
            min_node = min_node->left;
        }

        deleted_node->val = min_node->val; // 待删除节点的值等于右子树最小节点的值
        // 接下来删除最小节点即可
        deleted_node = min_node;
        parent = min_parent;
    }

    // 待删除结点只有一个子结点或者是叶节点没有子节点
    else if(deleted_node->right == NULL) child = deleted_node->left;
    else if(deleted_node->left == NULL) child = deleted_node->right;
    else child = NULL;

    if (deleted_node == tree) tree = child; // 待删除节点是根节点
    else if (parent->left == deleted_node)   parent->left = child;
    else   parent->right = child;
}
```

另外，我们还可以只将待删除节点标记为“已删除”，而不是真正从树中删除掉这个节点，这样操作就会简单很多，但比较浪费内存。

##### 1.4. 二叉查找树的其它操作

除了查找、插入和删除操作，二叉查找树还可以支持快速地**查找最大节点和最小节点、前驱节点和后继节点**。此外，如果我们**中序遍历二叉查找树，就可以输出一个有序的数据序列，时间复杂度为 O(n)**，非常高效。

#### 2. 支持重复数据的二叉查找树

我们前面讲的二叉查找树，其节点存储的都是数字。在实际开发中，二叉查找树中存储的都是一个包含很多字段的对象，我们利用对象的其中一个字段作为键值（key）来构建二叉查找树，而其它字段称为卫星数据。

而且，上面的分析我们都是针对不存在键值相同的情况，如果键值相同的话，我们有以下两种解决办法。

第一种方法比较简单，就是在每个节点不会仅存储一个数据，还会通过链表和支持动态扩容的数组等数据结构，把值相同的数据都存储在同一个节点上。

第二种方法不好理解，但更加优雅。如果插入的时候遇到一个和当前节点值相同的数据，我们就把这个值相同的数据放到这个节点的右子树中去，也就是当作大于这个节点的值来处理。

![](https://upload-images.jianshu.io/upload_images/11895466-d8cd281107f72733.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

查找的时候，遇到值相同的节点，我们并不停止查找，而是继续在右子树中查找，直到遇到叶子节点才停止，这样就可以把所有键值等于要查找值的节点都找出来。

![](https://upload-images.jianshu.io/upload_images/11895466-a8eda1848f866553.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

对于删除操作，我们也需要查找到所有要删除的节点，然后再按照前面讲的删除节点的方法，依次对节点进行删除。

![](https://upload-images.jianshu.io/upload_images/11895466-2228787027cee0d9.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 3. 二叉查找树的时间复杂度分析

实际上，二叉查找树的形态各式各样。对于同一组数据，我们可以构造出下面这三种二叉查找树。
![](https://upload-images.jianshu.io/upload_images/11895466-c7dd83dc4dde49d0.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

不同的二叉树结构，其查找、插入和删除操作的执行效率都是不一样的。针对第一个二叉树，根节点的左右子树严重不平衡，已经退化成了链表，所以查找的时间复杂度就变成了 O(n)。

相反，如果是最理想的情况，二叉查找树就是一棵完全二叉树（或满二叉树），这时候，其时间复杂度是多少呢？

由前面的代码和图中都可以看出，二叉查找树的时间复杂度其实都和树的高度成正比，而树的高度也就是树的层数减一。

针对一个包含 n 个节点的完全二叉树，第一层包含 1 个节点，第二层包含 2 个节点，以此类推，第 k 层就包含 $2^{k-1}$ 个节点。除了最后一层，因为完全二叉树的最后一层可能包含 $[1, 2^{L-1}]$ 个节点，L 为最大层数。因此，二叉树的节点个数 n 和二叉树的最大层数 L 之间存在如下关系：

```txt
n >= 1+2+4+8+...+2^(L-2)+1
n <= 1+2+4+8+...+2^(L-2)+2^(L-1)
```
我们可以计算出 L 的范围为 $[log_2(n+1), log_2(n)+1]$，也就是说二叉树的高度小于等于 $log_2n$。因此，极度不平衡的二叉查找树，它的查找性能肯定不能满足我们的要求。我们需要构建一种不管怎么删除、插入数据，它都能保持任意节点左右子树都比较均衡的二叉查找树。

#### 4. 散列表和二叉查找树的对比

散列表的插入、删除和查找操作的时间复杂度都可以做到常量级，但二叉查找树在最好情况下也才是 O(logn)，那我们为什么还要用二叉查找树呢？

- 散列表中的数据时无序存储的，要输出有序的数据则需要先进行排序，而二叉查找树则可以通过中序遍历在 O(n) 时间复杂度内输出有序的数据。

- 散列表扩容耗时很多，而且遇到散列冲突时，性能不稳定，但实际中我们最常用的二叉平衡查找树的性能非常稳定，时间复杂度稳定在 O(logn)。

- 由于哈希冲突的存在，散列表实际的查找速度可能并不一定比 O(logn) 快，再加上散列函数的计算耗时，其效率也就不一定比平衡二叉查找树要好。

- 散列表的构造比较复杂，要考虑散列函数的设计、散列冲突的解决、扩容、缩容等问题，而平衡二叉树只需要考虑平衡性这一个问题，而且这个问题解决方案也比较成熟、固定。

- 为了避免过多的散列冲突，散列表装载因子一般不能太大，特别是基于开放寻址法解决冲突的散列表，这样就会浪费一定的存储空间。

因此，在实际的开发过程中，我们需要结合具体的需求来选择使用哪一种数据结构。


[参考资料-极客时间专栏《数据结构与算法之美》](https://time.geekbang.org/column/126)

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

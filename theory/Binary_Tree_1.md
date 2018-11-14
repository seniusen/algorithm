#### 1. 树（Tree）

首先我们来看几个树的例子。

![](https://upload-images.jianshu.io/upload_images/11895466-e8dc690245e1d392.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

在一个树结构里，每个元素我们称之为**节点**，从上到下相邻节点连线的关系，我们称之为**父子关系**。

![](https://upload-images.jianshu.io/upload_images/11895466-89921ff7d1ff9adb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

在上面的图中，A 节点就是 B 节点的父节点，B 节点就是 A 节点的子节点。B、C、D 这三个节点的父节点是同一个节点，所以它们之间互称为**兄弟节点**。另外，如果一个节点没有父节点，我们称之为**根节点**，比如上图中的 E 节点。没有子节点的节点称为**叶子节点**或者**叶节点**，比如上图中的 G、H、I、J、K、L 节点。

还有几个关于树的比较重要的概念：高度（Height）、深度（Depth）、层（Level），它们的定义如下。

![](https://upload-images.jianshu.io/upload_images/11895466-fa288cbb5aa57aeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

高度其实就是从下往上计量，最下面的叶节点高度为 0，每向上一个节点，高度加 1。深度则是从上往下计量，根节点深度为 0，每向下一个节点，深度加 1。层则和深度类似，只不过根节点的层为 1，计数从 1 开始罢了。

![](https://upload-images.jianshu.io/upload_images/11895466-30985aa303ef0278.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 2. 二叉树（Binary Tree）

树的结构多种多样，但我们最常用的还是二叉树。

二叉树，顾名思义，就是说每个节点最多有两个分叉，也就是两个子节点，分别为左子节点和右子节点。不过，二叉树并不要求每个结点都有两个子节点，而是最多只能有两个子节点。以此类推，四叉树、八叉树也和二叉树同理。

![](https://upload-images.jianshu.io/upload_images/11895466-380ac81eea4f795a.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

上图中，第 2 个二叉树中的叶子节点全都在最底层，而且，除了叶子节点外，每个节点都有左右两个子节点，这种二叉树就叫作**满二叉树**。

第 3 个二叉树中的叶子节点都在最底下两层，最后一层的叶子节点都靠左排列，并且除了最后一层，其它层的节点个数都要达到最大，这种二叉树就叫作**完全二叉树**。

![](https://upload-images.jianshu.io/upload_images/11895466-f7369a22f394e167.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

完全二叉树为什么最后一层的叶子节点要靠左排列呢？这个定义有什么由来或者说目的在哪里呢？我们要从二叉树的存储方式来了解。想要存储一棵二叉树，我们有两种方法，一种是基于指针或者引用的二叉链式存储法，一种是基于数组的顺序存储法。

我们先来看比较简单、直观的链式存储法。其中，每个节点有三个字段，其中一个存储数据，另外两个分别是指向左右子节点的指针。

![](https://upload-images.jianshu.io/upload_images/11895466-e48c25a65197466b.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

再来看基于数组的顺序存储法。我们把根节点存储在下标为 i = 1 的位置，左子节点就存储在下标为 2 * i = 2 的位置，右子节点就存储在下标为 2 * i + 1 = 3 的位置。以此类推，B 节点的左子节点 就存储在 2 * 2 = 4 的位置，右子节点就存储在 2 * 2 + 1 = 5 的位置。

![](https://upload-images.jianshu.io/upload_images/11895466-60ce1b7b9183d2b5.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

也就是说，如果节点 X 存储在下标为 i 的位置，那下标为 2 * i 的位置存储的就是左子节点，下标为 2 * i + 1 的位置存储的就是右子节点，而且下标为 i / 2 的位置存储的就是其父节点。以这种方式存储，我们就可以通过根节点的位置很容易地把整棵树都串起来。

不过，刚才的情况是一棵完全二叉树，我们就浪费了数组中一个下标为 0 的位置。如果是一个非完全二叉树，那就会浪费比较多的数组存储空间。

![](https://upload-images.jianshu.io/upload_images/11895466-252cc83bdee748ac.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

所以，如果某棵树是完全二叉树，那用数组来存储无疑是最节省内存的方式，因为数组不需要额外的指针来指向左右子节点。因此，这也就是为什么完全二叉树会要求最后一层的子节点都靠左的原因。

#### 3. 二叉树的遍历

二叉树的遍历有三种经典方法，前序遍历、中序遍历和后序遍历，其中，前、中、后序指的是节点和它的左右子树节点打印的先后顺序。

- 前序遍历，就是对于树中的任意节点来说，先打印这个节点，然后再打印它的左子树，最后打印它的右子树。

- 中序遍历，就是对于树中的任意节点来说，先打印它的左子树，然后再打印这个节点，最后打印它的右子树。

- 后序遍历，就是对于树中的任意节点来说，先打印它的左子树，然后再打印它的右子树，最后打印这个节点。

![](https://upload-images.jianshu.io/upload_images/11895466-97a6c8dae4caa8d6.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

可以看到，二叉树的遍历其实就是一个递归的过程。比如前序遍历，其实就是先打印根节点，然后再递归地打印左子树，最后递归地打印右子树。

```c
void preOrder(Node* root) {
  if (root == null) return;
  print root // 此处为伪代码，表示打印 root 节点
  preOrder(root->left);
  preOrder(root->right);
}

void inOrder(Node* root) {
  if (root == null) return;
  inOrder(root->left);
  print root // 此处为伪代码，表示打印 root 节点
  inOrder(root->right);
}

void postOrder(Node* root) {
  if (root == null) return;
  postOrder(root->left);
  postOrder(root->right);
  print root // 此处为伪代码，表示打印 root 节点
}
```

在遍历的过程中，每个节点最多会被访问两次，所以遍历的时间复杂度与节点的个数成正比，为 O(n)。

[参考资料-极客时间专栏《数据结构与算法之美》](https://time.geekbang.org/column/126)

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

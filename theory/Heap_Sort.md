
#### 1. 堆的概念

堆是一种特殊的树，一个堆需要满足如下两个条件：

- 一个堆是一个完全二叉树；

- 堆中每个节点的值都必须大于等于或者小于等于其子树中的每个节点。

第一条，完全二叉树要求，除了最后一层，其它层的节点个数都是满的，并且最后一层的节点都靠左排列。

第二条，也等价于，每个节点的值大于等于或者小于等于其左右子节点的值。节点值大于等于其子树中每个节点值的堆称为 “大顶堆”，节点值小于等于其子树中每个节点值的堆称为 “小顶堆”。

![](https://upload-images.jianshu.io/upload_images/11895466-e0b631c6fbd8e191.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

上图中，第 1 个和第 2 个是大顶堆，第 3 个是小顶堆，第 4 个不是堆。而且，可以看到，对于同一组数据，我们可以构建多种不同形态的堆。

#### 2. 堆的实现

之前我们知道，完全二叉树比较适合用数组来存储，这样非常节省空间，因为不需要额外的空间来存储左右子节点的指针，单纯通过下标我们就可以找到一个节点的左右子节点。

![](https://upload-images.jianshu.io/upload_images/11895466-8df8f79615d1bc0b.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

可以看到，下标为 $i$ 的节点的左子节点下标为 $2i$，右子节点下标为 $2i+1$，而父节点下标就为  $\frac{i}{2}$。

##### 2.1. 往堆中插入一个元素

往堆中插入一个元素后，我们需要继续保持堆满足它的两个特性。

如果我们将新插入的元素放到堆的最后，此时，这依旧还是一棵完全二叉树，但就是节点的大小关系不满足堆的要求。因此，我们需要对节点进行调整，使之满足堆的第二个特性，这个过程称为**堆化**（heapify）。

![](https://upload-images.jianshu.io/upload_images/11895466-abc58f353d54ad38.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

堆化非常简单，就是顺着节点所在的路径，向上或者向下，对比然后交换。

我们从新插入的节点开始，依次与其父结点进行比较，如果不满足子节点值小于等于父节点值，我们就互换两个节点，直到满足条件为止。这个过程是自下向上的，称为**从下往上的堆化**方法。

![](https://upload-images.jianshu.io/upload_images/11895466-0d098cd2391c2ef9.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```java
public class Heap {
  private int[] a; // 数组，从下标 1 开始存储数据
  private int n;  // 堆可以存储的最大数据个数
  private int count; // 堆中已经存储的数据个数

  public Heap(int capicity) {
    a = new int[capicity + 1];
    n = capicity;
    count = 0;
  }

  public void insert(int data) {
    if (count >= n) return; // 堆满了
    ++count;
    a[count] = data;
    int i = count;
    while (i/2 > 0 && a[i] > a[i/2]) { // 自下往上堆化
      swap(a, i, i/2); // swap() 函数作用：交换下标为 i 和 i/2 的两个元素
      i = i/2;
    }
  }
 }
```

##### 2.2. 删除堆顶元素

假设我们构建的是大顶堆，那么堆顶元素就是最大值。当我们删除堆顶元素后，就需要把第二大元素放到堆顶，而第二大元素肯定是其左右子节点中的一个。然后，我们再迭代地删除第二大节点，以此类推，直到叶子节点被删除。

但是，这个方法有点问题，删除堆顶元素后堆就不满足完全二叉树的条件了。

![](https://upload-images.jianshu.io/upload_images/11895466-7eb7aac21ff1032c.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

实际上，我们稍微改变一下思路，就可以解决这个问题。删除堆顶元素后，我们将最后一个结点放到堆顶，然后再依次进行对比，将这个结点交换到正确的位置即可。这个过程是自上而下的，称为**从上往下的堆化**方法。

![](https://upload-images.jianshu.io/upload_images/11895466-b40a114be58132dd.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```java
public void removeMax() {
  if (count == 0) return -1; // 堆中没有数据
  a[1] = a[count];
  --count;
  heapify(a, count, 1);
}

private void heapify(int[] a, int n, int i) { // 自上往下堆化
  while (true) {
    int maxPos = i;
    if (i*2 <= n && a[i] < a[i*2]) maxPos = i*2;
    if (i*2+1 <= n && a[maxPos] < a[i*2+1]) maxPos = i*2+1;
    if (maxPos == i) break;
    swap(a, i, maxPos);
    i = maxPos;
  }
}
```

一棵包含 $n$ 个节点的完全二叉树，树的高度不会超过 $log_2n$。而堆化的过程是顺着结点所在的路径进行比较交换的，所以堆化的时间复杂度和树的高度成正比，也就是 $O(logn)$，也即往堆中插入和删除元素的时间复杂度都为 $O(logn)$。

#### 3. 堆排序的实现

借助于堆这种数据结构实现的排序算法，叫作堆排序，堆排序的时间复杂度非常稳定，为 $O(nlogn)$，而且是一种原地排序算法。堆排序大致可以分为两个步骤，**建堆**和**排序**。

##### 3.1. 建堆

我们首先将数组原地建成一个堆，所谓原地，就是不借助另外一个数组直接在原数组上进行操作，这有两种思路。

第一种思路就是借助于我们前面往堆中插入一个元素的思想。首先，我们假设下标为 1 的元素就是堆顶，然后依次将数组后面的数据插入到这个堆中即可。这种思路从前往后处理数据，而且每次插入数据时，都是从下往上堆化。

第二种实现思路和第一种截然相反，我们从后往前处理数据，每个数据从上往下堆化。因为叶子节点无法再往下继续堆化，我们从第一个非叶子节点开始，依次往前对数据进行堆化即可。

![](https://upload-images.jianshu.io/upload_images/11895466-27d040510fe581a4.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](https://upload-images.jianshu.io/upload_images/11895466-d303b0f992d0a363.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```java
private static void buildHeap(int[] a, int n) {
  for (int i = n/2; i >= 1; --i) {
    heapify(a, n, i);
  }
}

private static void heapify(int[] a, int n, int i) {
  while (true) {
    int maxPos = i;
    if (i*2 <= n && a[i] < a[i*2]) maxPos = i*2;
    if (i*2+1 <= n && a[maxPos] < a[i*2+1]) maxPos = i*2+1;
    if (maxPos == i) break;
    swap(a, i, maxPos);
    i = maxPos;
  }
}
```

这里，我们对下标为 $\frac{n}{2}$ 到 1 的数据进行堆化，下标为 $\frac{n}{2}+1$ 到 $n$ 的节点是叶子结点，不需要进行堆化。 

下面我们来看一下建堆过程的时间复杂度是多少。因为叶子结点不需要建堆，所以需要堆化的节点从倒数第二层开始，而每个节点建堆时需要交换和比较的次数，和这个节点的高度成正比。

![](https://upload-images.jianshu.io/upload_images/11895466-5b1642979119a34b.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

因此，我们只需要将每个需要建堆的节点高度求和，即可得出建堆的时间复杂度。

![](https://upload-images.jianshu.io/upload_images/11895466-a427c12f090f88dc.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

这个求和需要点技巧，我们将式子乘以 2 后再减去这个式子，可得。

![](https://upload-images.jianshu.io/upload_images/11895466-3ef9104a9e21673a.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](https://upload-images.jianshu.io/upload_images/11895466-aee4960ec466cef0.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

节点的最大高度 $h=log_2n$，因此可以得出建堆的时间复杂度为 $O(n)$。

##### 3.2. 排序

建堆结束之后，堆顶元素就是最大元素，我们将其和最后一个元素进行交换，那最大元素就放到了下标为 $n$ 的位置。然后，我们再对前面 $n-1$ 个元素进行堆化，然后将堆顶元素放到下标为 $n-1$ 的位置，重复这个过程，直到堆中剩余一个元素，排序也就完成了。

![](https://upload-images.jianshu.io/upload_images/11895466-f11e204edc821139.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```java
// n 表示数据的个数，数组 a 中的数据从下标 1 到 n 的位置。
public static void sort(int[] a, int n) {
  buildHeap(a, n);
  int k = n;
  while (k > 1) {
    swap(a, 1, k);
    --k;
    heapify(a, k, 1);
  }
}
```

整个堆排序过程中，我们都只需要常量级别的临时空间，所以堆排序是原地排序算法。堆排序中建堆过程的时间复杂度为 $O(n)$，排序过程的时间复杂度为 $O(nlogn)$，因此整体的时间复杂度为 $O(nlogn)$。

堆排序不是稳定的排序算法，因为在排序的时候，我们将堆顶元素和最后一个元素进行了交换，这就有可能改变了值相同元素的原始相对位置。

另外，前面我们都假设堆中的数据从下标为 1 的位置开始存储，如果是从下标为 0 的位置开始存储，我们就需要重新计算子节点和父节点的小标位置。

下标为 $i$ 的节点的左子节点下标为 $2i+1$，右子节点下标为 $2i+2$，而父节点下标就为  $\frac{i-1}{2}$。

#### 4. 为什么说堆排序没有快速排序快？

- 堆排序数据访问的方式没有快速排序好

可以看到，堆排序数据的访问不是像快速排序那样按顺序访问的，这对 CPU 缓存是不友好的。下面的这个例子，要对堆顶结点进行堆化，我们要依次访问下标为 1,2,4,8 的元素。

![](https://upload-images.jianshu.io/upload_images/11895466-d308b8a401f56274.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 同样的数据，堆排序的数据交换次数多于快速排序

快速排序的交换次数不会比逆序数多，但是堆排序的建堆过程会打乱原有数据的先后顺序，导致数据的有序度降低。比如，针对一组已经有序的数据，建堆之后，数据反而变得更无序了。

![](https://upload-images.jianshu.io/upload_images/11895466-b2ffa5ad8550495a.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
















[参考资料-极客时间专栏《数据结构与算法之美》](https://time.geekbang.org/column/126)

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

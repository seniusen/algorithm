> 二分查找（Binary Search）的思想非常简单，但看似越简单的东西往往越难掌握好，想要灵活运用就更加困难。

### 1. 二分查找的思想？

生活中二分查找的思想无处不在。一个最常见的就是猜数游戏，我随机写一个 0 到 99 的数，然后你来猜我写的是什么。猜的过程中，我会告诉你每次是猜大了还是猜小了，直到猜中为止。假如我写的数是 23，猜数过程如下所示。

![](https://upload-images.jianshu.io/upload_images/11895466-d13b7b437a051023.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

最多只需要 7 次就猜出来了，这个过程是很快的。同理，要查找某个数据是否在给定的数组中，我们同样也可以利用这个思想。

![](https://upload-images.jianshu.io/upload_images/11895466-b9e016270fc97605.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

二分查找针对的是一个**有序的数据集合，查找思想有点类似于分治**，每次都通过和中间元素进行比较，将待查找区间缩小为之前的一半，直到找到要查找的元素或者区间缩小为 0 为止。

### 2. 二分查找的时间复杂度？

我们假设数据大小为 n，每次查找数据大小都会缩小为原来的一半，最坏情况下，直到查找区间缩小为空时停止查找。

![](https://upload-images.jianshu.io/upload_images/11895466-b8db1aa35eae481b.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

若经过 k 次区间缩小最后变为空，则 $\frac{n}{2^k} = 1, k = log_2n$，所以二分查找的时间复杂度为 $O(logn)$。

这种对数时间复杂度的算法是一种非常高效的算法，有时候甚至比时间复杂度为常量级的算法还要高效。因为常量级的时间复杂度对应的常数可能非常大，比如 O(100), O(1000)，因此这些算法有时候可能还没有 $O(logn)$ 的算法执行效率高。

### 2. 简单二分查找的算法实现？

循环法
```c
float Binary_Search(float data[], int left, int right, float value)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (value == data[mid])
        {
            return mid;
        }
        else if (value < data[mid])
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    return -1;
}
```

递归法
```c
float Binary_Search(float data[], int left, int right, float value)
{
    if (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (value == data[mid])
        {
            return mid;
        }
        else if (value < data[mid])
        {
           return Binary_Search(data, left, mid-1, value);
        }
        else
        {
            return Binary_Search(data, mid+1, right, value);
        }
    }

    return -1;
}
```

注意事项
- 循环退出条件 **left <= right**
- **mid = left + ((right-left) >> 1)**，用移位运算优化计算性能
- left 和 right 的更新分别是 **mid+1 和 mid-1**

### 3. 二分查找的应用场景？

二分查 找依赖的是顺序表结构，也就是数组，需要能够按照下标**随机访问元素**。

二分查找针对的是**有序数据**，如果数据无序，需要先进行排序。而如果有频繁的插入、删除操作，则每次查找前都需要再次排序，这时候，二分查找将不再适用。

**数据量太小可以直接遍历查找**，没有必要用二分查找。但如果数据之间的比较操作非常耗时，比如数据为长度超过 300 的字符串，则不管数据量大小，都推荐使用二分查找。

而如果数据量过大，则意味着我们需要用非常大的连续内存空间来存储这些数据，**内存开销可能无法满足**。

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

> 最简单的二分查找情况下，我们假设数组中没有重复元素，因此很容易实现。如果数组中存在重复元素，二分查找就没有想象中那么容易了。

![](https://upload-images.jianshu.io/upload_images/11895466-1052c09c05b5583d.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


### 1. 查找第一个值等于给定值的元素？

如果数据中存在相同的元素，但我们要查找第一个值等于给定值的元素，如果直接用最简单的二分查找，显然是不满足的。

看下面的例子，有 3 个等于 8 的元素，简单二分查找会返回 7，但第一个值等于 8 的元素应该是 a[5]。

![](https://upload-images.jianshu.io/upload_images/11895466-a6589342767566e0.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

其实，只要我们在简单二分查找的基础上再多加上一点限制即可。

当我们发现 a[mid] = val 时，我们需要继续确认 a[mid] 左边还有没有等于 val 的元素。**若 mid 左边没有和 a[mid] 相等的元素**，则此时 a[mid] 就是我们要找的第一个值等于给定值的元素。另外，**若 mid 到了第一个元素的位置，说明左边已经没有元素**，此时  a[mid] 也即是我们要找的元素。否则，我们就需要继续向左边查找。

```c
float Binary_Search(float data[], int left, int right, float value)
{
    int begin = left;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (value == data[mid])
        {
            if (mid == begin || a[mid - 1] != a[mid]) return mid;
            else right = mid - 1;
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

### 2. 查找最后一个值等于给定值的元素？

这个问题和上面要查找第一个值等于给定值的问题思路一样，只不过是查找的方向改变了。

当我们发现 a[mid] = val 时，我们需要继续确认 a[mid] 右边还有没有等于 val 的元素。**若 mid 右边没有和 a[mid] 相等的元素**，则此时 a[mid] 就是我们要找的最后一个值等于给定值的元素。另外，**若 mid 到达了最后一个元素的位置，说明右边已经没有元素**，此时  a[mid] 也即是我们要找的元素。否则，我们就需要继续向右边查找。

```c
float Binary_Search(float data[], int left, int right, float value)
{
    int end = right;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (value == data[mid])
        {
            if (mid == end || a[mid + 1] != a[mid]) return mid;
            else left = mid + 1;
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

### 3. 查找第一个大于等于给定值的元素？

当我们发现 a[mid] >= val 时，我们需要继续确认 a[mid] 左边还有没有大于等于 val 的元素。**若 mid 左边的值小于 a[mid]**，则此时 a[mid] 就是我们要找的第一个大于等于给定值的元素。另外，**若 mid 到达了第一个元素的位置，说明左边已经没有元素**，此时  a[mid] 也即是我们要找的元素。否则，我们就需要继续向左边查找。

```c
float Binary_Search(float data[], int left, int right, float value)
{
    int begin = left;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (data[mid] >= value)
        {
            if (mid == begin || a[mid - 1] < a[mid]) return mid;
            else right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }      
    }

    return -1;
}
```

### 4. 查找最后一个小于等于给定值的元素？

当我们发现 a[mid] <= val 时，我们需要继续确认 a[mid] 右边还有没有小于等于 val 的元素。**若 mid 右边的值大于 a[mid]**，则此时 a[mid] 就是我们要找的最后一个小于等于给定值的元素。另外，**若 mid 到达了最后一个元素的位置，说明右边已经没有元素**，此时  a[mid] 也即是我们要找的元素。否则，我们就需要继续向右边查找。

```c
float Binary_Search(float data[], int left, int right, float value)
{
    int end = right;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (data[mid] <= value)
        {
            if (mid == end || a[mid + 1] > a[mid]) return mid;
            else left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }      
    }

    return -1;
}
```

### 5. 如何快速定位 IP 对应的省份？

![](https://upload-images.jianshu.io/upload_images/11895466-4bf4954cb4248d6e.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

当我们要查找 202.102.133.13 这个 IP 地址的归属地时，我们就在地址库中搜索，发现这个 IP 位于 [202.102.133.0, 202.102.133.255] 这个范围内，我们就可以找到对应的归属地——山东东营。

```
[202.102.133.0, 202.102.133.255]  山东东营市 
[202.102.135.0, 202.102.136.255]  山东烟台 
[202.102.156.34, 202.102.157.255] 山东青岛 
[202.102.48.0, 202.102.48.255] 江苏宿迁 
[202.102.49.15, 202.102.51.251] 江苏泰州 
[202.102.56.0, 202.102.56.255] 江苏连云港
```

因此，我们可以按照 IP 地址库的起始地址对所有区间进行排序，然后问题就转化为了找到**最后一个起始地址小于等于给定 IP 地址的区间**，ranho


[参考资料-极客时间专栏《数据结构与算法之美》](https://time.geekbang.org/column/126)

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

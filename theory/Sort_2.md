> 冒泡排序、插入排序、选择排序这三种算法的时间复杂度都为 $O(n^2)$，只适合小规模的数据。今天，我们来认识两种时间复杂度为 $O(nlogn)$ 的排序算法——归并排序（Merge Sort）和快速排序（Quick Sort），他们都用到了**分治思想**，非常巧妙。

### 1. 归并排序（Merge Sort）？

#### 1.1. 归并排序算法实现

- **归并排序**的核心思想其实很简单，如果要排序一个数组，我们先把数组从中间分成前后两部分，然后分别对前后两部分进行排序，再将排好序的两部分数据合并在一起就可以了。

![归并排序](https://upload-images.jianshu.io/upload_images/11895466-aad42ed1ab26aead.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 归并排序使用的是分治思想，分治也即是分而治之，将一个大问题分解为小的子问题来解决。分治算法一般都是用递归来实现的。**分治是一种解决问题的处理思想，递归是一种编程技巧**。

- 如果要对数组区间 [p, r] 的数据进行排序，我们先将数据拆分为两部分 [p, q] 和 [q+1, r]，其中 q 为中间位置。对两部分数据排好序后，我们再将两个子数组合并在一起。当数组的起始位置小于等于终止位置时，说明此时只有一个元素，递归也就结束了。
```
递推公式：
merge_sort(p…r) = merge(merge_sort(p…q), merge_sort(q+1…r))

终止条件：
p >= r 不用再继续分解
```

- 对两个子数组进行合并的过程如下所示，我们先建立一个临时数组，然后从两个子数组的起始位置开始比较，将较小的元素一个一个放入临时数组，直到其中一个子数组比较完毕，再将剩下的另一个子数组余下的值全部放到临时数组后面。最后我们需要将临时数组中的数据拷贝到原数组对应的位置。

![数组合并](https://upload-images.jianshu.io/upload_images/11895466-ae9680da11d2a2ad.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 代码实现
```c
// O(n(logn))
void Merge_Sort(float data[], int left, int right, float sorted_data[])
{
    if(left < right)
    {
        int mid = (left + right) / 2;
        Merge_Sort(data, left, mid, sorted_data);
        Merge_Sort(data, mid+1, right, sorted_data);
        Merge_Array(data, left, mid, right, sorted_data);
    }
}

void Merge_Array(float data[], int left, int mid, int right, float temp[])
{
    int i = left, j = mid + 1;
    int k = 0;

    // 从子数组的头开始比较
    while(i <= mid && j <= right)
    {
        if (data[i] <= data[j])
        {
            temp[k++] = data[i++];
        }
        else
        {
            temp[k++] = data[j++];
        }
    }

    // 判断哪个子数组还有元素，并拷贝到 temp 后面
    while(i <= mid)
    {
        temp[k++] = data[i++];
    }
    while(j <= right)
    {
        temp[k++] = data[j++];
    }

    // 将 temp 中的数据拷贝到原数组对应位置
    for(i = 0; i < k; i++)
    {
        data[left+i] = temp[i];
    }
}
```
#### 1.2. 归并排序算法分析

- 归并排序是一个**稳定的排序算法**，在进行子数组合并的时候，我们可以设置当元素大小相等时，先将前半部分的数据放入临时数组，这样就可以保证相等元素在排序后依然保持原来的顺序。

- **不仅递归求解的问题可以写成递推公式，递归代码的时间复杂度也可以写成递归公式**。
- 如果我们对 $n$ 个元素进行归并排序所需要的时间是  $T(n)$，那分解成两个子数组排序的时间都是 $T(\frac{n}{2})$，而合并两个子数组的时间复杂度为 $O(n)$。所以，归并排序的时间复杂度计算公式为：
>$$ T(1) = C $$
$$T(n) = 2*T(\frac{n}{2}) + n,  n>1$$
- n = 1 时，只需要常量级的执行时间，所以表示为 C。
>$$T(n) = 2*T(\frac{n}{2}) + n $$
    $$ = 2*[2*T(\frac{n}{4}) + \frac{n}{2}] + n = 4*T(\frac{n}{4}) + 2*n $$
    $$ = 4*[2*T(\frac{n}{8}) + \frac{n}{4}] + 2*n = 8*T(\frac{n}{8}) + 3*n $$
    $$ ......$$
    $$ = 2^k * T(\frac{n}{2^k}) + k * n$$
    $$ ......$$
当 $\frac{n}{2^k} = 1$时， $k = log_2n$，代入上式得：
$$ T(n) = n * C + nlog_2n$$
用大 O 标记法来表示，归并排序的时间复杂度为 $O(nlogn)$。

- 从我们的分析可以看出，归并排序的执行效率与原始数据的有序程度无关，其时间复杂度是非常稳定的，**不管是最好情况、最坏情况，还是平均情况，时间复杂度都是 $O(nlogn)$**。

- 归并排序有一个缺点，那就是它**不是原地排序算法**。在进行子数组合并的时候，我们需要临时申请一个数组来暂时存放排好序的数据。因为这个临时空间是可以重复利用的，因此归并排序的空间复杂度为 $O(n)$，最多需要存放 $n$ 个数据。

---


### 2. 快速排序（Quick Sort）？
#### 1.1. 快速排序算法实现

- **快速排序**的思想是这样的，如果要对数组区间 [p, r] 的数据进行排序，我们先选择其中任意一个数据作为 pivot（分支点），一般为区间最后一个元素。然后遍历数组，将小于 pivot 的数据放到左边，将大于 pivot 的数据放到右边。接着，我们再递归对左右两边的数据进行排序，直到区间缩小为 1 ，说明所有的数据都排好了序。
![快速排序](https://upload-images.jianshu.io/upload_images/11895466-189091568d88ee9a.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```
递推公式：
quick_sort(p…r) = quick_sort(p…q-1) + quick_sort(q+1, r)

终止条件：
p >= r
```

- 归并排序是由下向上的，先处理子数组然后再合并。而快速排序正好相反，它的过程是由上向下的，先分出两个子区间，再对子区间进行排序。归并排序是稳定的时间复杂度为 $O(n)$，但它是非原地算法，而快排则是原地排序算法。

![归并排序和快速排序](https://upload-images.jianshu.io/upload_images/11895466-824e3d85de10519b.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 快速排序的分区过程如下所示，从左到右依次遍历数组，如遇到小于 pivot 的元素，则进行数据交换 ，否则继续往前进行，最后再放置 pivot。
![快排分区](https://upload-images.jianshu.io/upload_images/11895466-40cf4293fc60c7c4.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 代码实现
```c
// O(n(logn))
void Quick_Sort(float data[], int left, int right)
{
    if (left < right)
    {
        int i = left, j = left;
        int pivot = data[right];

        for (j = left; j < right; j++)
        {
            if (data[j] < pivot)
            {
                int temp = data[i];
                data[i] = data[j];
                data[j] = temp;
                i++;
            }
        }

        data[j] = data[i];
        data[i] = pivot;
        Quick_Sort(data, left, i-1);
        Quick_Sort(data, i+1, right);
    }
}
```

- 快速排序的另一种实现方式如下所示，先取出一个元素作为 pivot（假设是最后一个），这时 pivot 位置可以看作为空，然后从左到右查找第一个比 pivot 大的元素放在 pivot 的位置，此时空的地方变成了这第一个比 pivot 大的元素位置。然后从右到左查找第一个比 pivot 小的元素放在刚才空的位置，依次循环直到从左到右和从右到左都查找到了同一位置，这时候再把 pivot 放置在最后一个空位。这个过程可以形象的被称为“挖坑填坑”。

![快速排序](https://upload-images.jianshu.io/upload_images/11895466-a6bc3020b5270aef.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


- 代码实现
```c
// O(n(logn))
void Quick_Sort(float data[], int left, int right)
{
    if (left < right)
    {
        int i = left, j = right;
        int pivot = data[i];
        while(i < j)
        {
            while(i < j && data[i] <= pivot) // 从左往右找到第一个比 pivot 大的数
            {
                i++;
            }
            if(i < j)
            {
                data[j--] = data[i];
            }
            while(i < j && data[j] >= pivot) // 从右往左找到第一个比 pivot 小的数
            {
                j--;
            }
            if(i < j)
            {
                data[i++] = data[j];
            }
        }
        data[i] = pivot; // i=j
        Quick_Sort(data, left, i-1);
        Quick_Sort(data, i+1, right);
    }
}

```
#### 2.2. 快速排序算法分析
- 如果快速排序每次都将数据分成相等的两部分，则快排的时间复杂度和归并排序相同，也是 $O(nlogn)$，但这种情况是很难实现的。如果数据原来已经是有序的，则每次的分区都是不均等的，我们需要进行 n 次分区才能完成整个排序，此时快排的时间复杂度就退化成了 $O(n^2)$。

- 平均时间复杂度的求解也可以通过递归树来分析，这个问题留待我们以后再解决。我们现在只需要知道，**在大部分情况下，快速排序的时间复杂度都可以做到 $O(nlogn)$，只有在极端情况下，才会退化成 $O(n^2)$**。

- 快速排序是一个**原地排序算法，是一个不稳定的排序算法**，因为其在数据交换过程中可能会改变相等元素的原始位置。

---

### 3. 小结

- 归并排序和快速排序都是利用分治的思想，代码都通过递归来实现，过程非常相似。
- 归并排序非常稳定，时间复杂度始终都是 $O(nlogn)$，但不是原地排序；快速排序虽然最坏情况下时间复杂度为 $O(n^2)$，但平均情况下时间复杂度为 $O(nlogn)$，最坏情况发生的概率也比较小，而且是原地排序算法，因此应用得更加广泛。

---

[参考资料-极客时间专栏《数据结构与算法之美》](https://time.geekbang.org/column/126)

获取更多精彩，请关注「seniusen」! 
![seniusen](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)



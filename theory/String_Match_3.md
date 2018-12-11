> 在所有的字符串匹配算法中，KMP 算法是最知名的，实际上，它和 [BM 算法](https://blog.csdn.net/seniusen/article/details/84886840)的本质是一样的。


### 1. KMP 算法基本原理

KMP 算法是根据三位作者（D.E.Knuth，J.H.Morris 和 V.R.Pratt）的名字来命名的，算法的全称是 Knuth Morris Pratt 算法，简称为 KMP 算法。

KMP 算法的核心思想和 BM 算法非常相近，就是在遇到不可匹配字符的时候，我们希望能将模式串向后多滑动几位，跳过那些肯定不会匹配的情况。

在 KMP 算法中，我们从前向后对模式串和主串进行对比，不能匹配的字符仍然叫作**坏字符**，而前面已经匹配的字符串叫作**好前缀**。

![](https://upload-images.jianshu.io/upload_images/11895466-6eb6353aaf0df5e5.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

那遇到坏字符时，我们怎么决定模式串该向后移动几位呢？

我们需要在好前缀的所有后缀子串中，找到一个最长的可以和好前缀的前缀子串匹配的子串。假设这个最长的可匹配的前缀子串为 {v}，长度为 k，而坏字符在主串中对应的位置为 i，在模式串中对应的位置为 j，那么我们就需要将模式串后移 j-k 位，也就相当于把 j 更新为 k（注意下图的错误）， i 不变，然后继续比较。

![](https://upload-images.jianshu.io/upload_images/11895466-d8c1157671b7644a.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

我们把好后缀的所有后缀子串中，最长的可以和好前缀的前缀子串匹配的子串，叫作**最长可匹配后缀子串**，对应的前缀子串，叫作**最长可匹配前缀子串**。

![](https://upload-images.jianshu.io/upload_images/11895466-2ba1cdc65b5e3520.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


类似 BM 算法，我们也可以先对模式串进行预处理，定义一个数组来存储模式串中每个前缀（这些前缀都有可能是好前缀）的最长可匹配前缀子串的结尾字符下标。我们把这个数组定义为 **next 数组**，很多书中还给这个数组起了一个名字，叫**失效函数**（failure function）。

数组的下标是每个前缀结尾字符的下标，数组的值是这个前缀的最长可以匹配的前缀子串的结尾字符下标。

![](https://upload-images.jianshu.io/upload_images/11895466-1b4180bbf9669668.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

有了 next 数组，KMP 算法就很容易实现，下面我们先给出一个程序的框架，假设 next 数组已经计算好了。

```c
int KMP(char str1[], int n, char str2[], int m)
{
    int next[m];
    GenerateNext(str2, next, m);

    int j = 0;

    for (int i = 0; i < n; i++)
    {
        while (j > 0 && str1[i] != str2[j])
        {
            j = next[j-1] + 1; // j 更新为最长可匹配前缀子串的长度 k
        }
        if (str1[i] == str2[j]) j++;
        if (j == m) return i - m + 1;
    }

    return -1;
}
```

### 2. 失效函数计算方法

我们可以用非常笨拙的方法来计算 next 数组。比如，如果要计算下面这个模式串 b 的 next[4]，我们就把 b[0, 4] 的所有后缀子串列举出来，逐个看是否能和模式串的前缀子串匹配。这种方法虽然也可以计算出 next 数组，但是效率非常低。

![](https://upload-images.jianshu.io/upload_images/11895466-7f5ac2c399697b8f.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

我们按照下标从小到大，依次计算 next 数组的值。当我们要计算 next[i] 的时候，前面的 next[0] 到 next[i-1] 都已经计算出来了，我们可以利用前面的值来快速推导出 next[i] 的值。

如果 next[i-1] = k-1，也就是说，子串 b[0, k-1] 是 b[0, i-1] 的最长可匹配前缀子串。如果子串 b[0, k-1] 的下一个字符 b[k]，与 b[0, i-1] 的下一个字符 b[i] 匹配，那么子串 b[0, k] 也就是 b[0, i] 的最长可匹配前缀子串。所以 next[i] = k。但是，如果子串 b[0, k-1] 的下一个字符 b[k] 与 b[0, i-1] 的下一个字符 b[i] 不匹配，那就不能简单地通过 next[i-1] 来得到 next[i] 了。

![](https://upload-images.jianshu.io/upload_images/11895466-6a79437726938afb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

我们假设 b[0, i] 的最长可匹配后缀子串是 b[r, i]。如果我们把最后一个字符去掉，那 b[r, i-1] 肯定是 b[0, i-1] 的可匹配后缀子串，但不一定是最长可匹配子串。

所以，既然 b[0, i-1] 最长可匹配后缀子串对应的模式串的前缀子串的下一个字符并不等于 b[i]，那么我们就可以考察 b[0, i-1]  的次长可匹配后缀子串 b[x, i-1] 对应的可匹配前缀子串 b[0, i-1-x] 的下一个字符 b[i-x] 是否等于 b[i]。如果相等，那么 b[x, i] 就是 b[0, i] 的最长可匹配后缀子串。

![](https://upload-images.jianshu.io/upload_images/11895466-dce168a90b9813eb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

可是，如何求得 b[0, i-1] 的次长可匹配后缀子串呢？次长可匹配后缀子串肯定被包含在最长可匹配后缀子串中，而最长可匹配后缀子串又对应最长可匹配前缀子串 b[0, y]。于是，查找 b[0, i-1] 的次长可匹配后缀子串，这个问题就变成了，查找 b[0, y] 的最长可匹配后缀子串。

![](https://upload-images.jianshu.io/upload_images/11895466-8e6f9ac4bcf08159.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

因此，我们可以考察所有的 b[0, i-1] 的可匹配后缀子串 b[y, i-1]，直到找到一个可匹配的后缀子串，它对应的前缀子串的下一个字符等于 b[i]，那这个 b[y, i] 就是 b[0, i] 的最长可匹配后缀子串。

```c
void GenerateNext(char str[], int next[], int m)
{
    next[0] = -1;
    int k = -1;

    for (int i = 1; i < m; i++)
    {
        while (k != -1 && str[k+1] != str[i])
        {
            k = next[k];
        }
        if (str[k+1] == str[i]) k++;
        next[i] = k;
    }
}
```

### 3. KMP 算法复杂度分析

空间复杂度很容易分析，KMP 算法只用到了一个额外的数组 next，其大小与模式串长度 m 相同，因此空间复杂度为 O(m)。

KMP 算法包括两部分，第一部分是构建 next 数组，第二部分是借助 next 数组进行匹配。

先看第一部分，这部分代码由两个循环组成。我们观察变量 i 和 k 的值，i 从 1 增长到 m，而 k 并不是每次在 for 循环里都增加，k 的值不可能大于 m。在 while 循环里， k = next[k]，其值是在减小的，总的减小次数也肯定小于 m。所以 next 数组计算的时间复杂度为 O(m)。

再看第二部分，方法是类似的。i 从 0 增长到 n，而 j 并不是每次在 for 循环里都增加，j 的值不可能大于 n。在 while 循环里， j = next[j-1] + 1，其值是在减小的，总的减小次数也肯定小于 n。所以匹配的时间复杂度为 O(n)。

综上所述，KMP 算法总的时间复杂度为 O(m+n)。

[参考资料-极客时间专栏《数据结构与算法之美》](https://time.geekbang.org/column/126)

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

> 文本编辑器中的查找功能是如何实现的呢？

文本编辑器中的查找功能本质上就是一个字符串匹配过程，因此可以用[ BF 算法和 RK 算法](https://blog.csdn.net/seniusen/article/details/84841213) 实现，但是在某些极端情况下，BF 算法性能会退化得比较严重，而 RK 算法需要用到哈希算法，设计一个可以适用于各种字符的哈希算法并不是那么简单。

### 1. BM 算法的核心思想

模式串和主串的匹配，可以看作是模式串在子串中不断向后滑动的过程。如果遇到两个子串不匹配， BF 算法和 RK 算法的做法就是将模式串向后移动一个字符的位置，然后继续进行比较。

![](https://upload-images.jianshu.io/upload_images/11895466-340d3fab7df5758a.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

在上面的例子中，c 和 d 不匹配，我们就将模式串向后移动一位。但是，我们发现，模式串中根本不存在字符 c，因此，我们可以直接将模式串向后多移动几位。

![](https://upload-images.jianshu.io/upload_images/11895466-55bb37dd8ea58481.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

同样地，在遇到类似情况的时候，我们是不是都可以一次性将模式串向后多移动几位呢？ BM 算法其实就是在寻找这些规律，借助这些规律，字符串匹配的效率也就会大大提高。


### 2. BM 算法原理分析

BM 算法包含两部分，分别是**坏字符规则**（bad character rule）和**好后缀规则**（good suffix shift）。

##### 2.1. 坏字符规则

首先，BM 算法**针对两个子串的比较是从后向前进行的**，也就是按照下标从大到小进行比较。

![](https://upload-images.jianshu.io/upload_images/11895466-1d9d324a1ad9060c.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![](https://upload-images.jianshu.io/upload_images/11895466-0757c9ef96135ccd.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

我们从模式串的末尾向前比较，当发现某个字符没法匹配的时候，这个无法匹配的字符就叫作**坏字符**（主串中的字符）。

![](https://upload-images.jianshu.io/upload_images/11895466-669e390f14c85bbb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

我们拿坏字符 c 在模式串中查找，发现模式串中根本不存在这个字符。此时，我们就可以直接将模式串向后移动三个位置，再继续进行比较。 

![](https://upload-images.jianshu.io/upload_images/11895466-3a076388d9a69f0a.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

此时，最后一个字符 a 和 d 还是无法匹配。但是，坏字符 a 存在于模式串中，我们不能直接向后移动 3 位 ，而是应该让主串中的字符 a 和模式串中的 a 对齐，然后再继续进行比较。

![](https://upload-images.jianshu.io/upload_images/11895466-96d535b876c3d463.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

可以看到，模式串的移动位数在不同情况下是不一样的，它们有什么规律呢？我们将坏字符对应于模式串中的下标记为 si，将坏字符在模式串中从前往后第一次出现的位置记为 xi，如果坏字符在模式串中不存在，那么其值就为 -1。然后，模式串应该向后移动的位数就等于 si - xi。

![](https://upload-images.jianshu.io/upload_images/11895466-b43587556e100092.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

利用坏字符规则，BM 算法在最好情况下的时间复杂度非常低，为 O(n/m)。比如，主串是 aaabaaabaaabaaab，模式串是 aaaa，每次匹配都可以直接向后移动 4 位，非常高效。

不过，只单纯利用坏字符规则是不够的。因为根据 si-xi 计算出来的移动位数，有可能是负数。比如，主串是 aaaaaaaaaaaaaaaa，模式串是 baaa，不但不会向后移动，还会倒退。

##### 2.1. 好后缀规则

实际上，好后缀规则和坏字符规则的思路很类似。

![](https://upload-images.jianshu.io/upload_images/11895466-24fa1707da145523.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

在上面的例子中，坏字符后面的字符 bc 是匹配的，它们就称之为好后缀，记作 {u}。我们拿它在模式串中查找，如果找到了另一个和 {u} 匹配的子串 {u\*}，那我们就将模式串滑动到子串  {u\*} 与主串 {u} 对齐的位置。

![](https://upload-images.jianshu.io/upload_images/11895466-4815a017e02e077f.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

如果在模式串中找不到另一个等于 {u} 的子串，我们就直接将模式串移动到主串 {u} 的后面，因为中间的滑动过程都无法和 {u} 匹配上。

![](https://upload-images.jianshu.io/upload_images/11895466-62e9678411b9efdd.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

不过，当模式串中不存在等于 {u} 的子串时，直接将模式串移动到主串 {u} 的后面是有问题的，我们有可能会错过主串和模式串匹配的情况。

![](https://upload-images.jianshu.io/upload_images/11895466-166b12d9c7a2c22c.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

事实上，当模式串中不存在等于 {u} 的子串时，只要 {u} 和模式串完全重合，那肯定模式串和主串就不可能匹配，但若是 {u} 和模式串部分重合，那就有可能会存在模式串和主串匹配的情况。

![](https://upload-images.jianshu.io/upload_images/11895466-9cf7d6b08849f7f4.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

所以，针对这种情况，我们不仅要考虑好后缀是否存在于模式串中，还要考虑**好后缀的后缀子串是否和模式串的前缀子串匹配**。所谓好后缀的后缀子串，即是和好后缀最后一个字符对齐的子串，比如 abc 的后缀子串就是 c、bc。所谓前缀子串，即是和模式串第一个字符对齐的子串，比如 abc 的前缀子串就是 a、ab。

我们从好后缀的后缀子串中，找到一个最长的并且能和模式串前缀子串匹配的子串，假设是 {v}，然后将模式串滑动到好后缀的后缀子串与模式串的前缀子串对齐的位置。

![](https://upload-images.jianshu.io/upload_images/11895466-2f072bb87ccef1c6.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

最后，当模式串和主串中的某个字符不匹配的时候，我们**分别利用坏字符规则和好后缀规则计算出两个数字，选取较大的那个数作为模式串应该往后移动的位数**。

### 3. BM 算法代码实现

首先，我们应该怎么查找坏字符在模式串中的位置呢？如果每次都要在模式串中遍历查询，那肯定效率非常低。这时候，散列表就派上用场了。我们可以将模式串中的字符及其在模式串中的位置存储在散列表中，这样查找坏字符位置的时候就直接从散列中取出即可。

假设字符串的字符集不是很大，每个字符长度是 8 个字节，那么我们就可以用一个大小为 256 的数组来实现散列表的功能，数组下标就是对应字符的 ASCII 码，数组中的数据就是该字符在模式串中出现的位置。

![](https://upload-images.jianshu.io/upload_images/11895466-00ffa89aa98d59c6.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```c
# define SIZE 256

// 生成坏字符对应的散列表
void GenerateBC(char str[], int m, int bc[])
{
    // 所有字符初始化为 -1
    for (int i = 0; i < SIZE; i++)
    {
        bc[i] = -1;
    }

    for (int i = 0; i < m; i++)
    {
        int ascii = str[i] - '\0'; // 求出字符对应的 ASCII 码
        bc[ascii] = i;
    }
}
```

接下来，我们先把 BM 算法的大框架写好，只考虑坏字符规则，且不考虑移动位数为负的情况。

```c
int BM(char str1[], int n, char str2[], int m)
{
    int bc[SIZE]; // 记录每个字符在模式串中最后出现的位置，作为坏字符散列表
    GenerateBC(str2, m, bc);

    int i = 0; // 表示主串和模式串对齐时第一个字符的位置
    int si = 0; // 坏字符对应于模式串中的位置
    int xi = -1; // 坏字符在模式串中出现的位置

    while (i <= n-m)
    {
        int j = 0;
        // 从后向前进行匹配
        for (j = m-1; j >= 0; j--)
        {
            // 找到了第一个不匹配的字符
            if (str1[i+j] != str2[j]) break;
        }

        if (j < 0) return i; // 匹配成功

        si = j;
        xi = bc[str1[i+j] - '\0'];
        i = i + si - xi; // 将模式串后移 si-xi 个位置
    }

    return -1;
}
```

![](https://upload-images.jianshu.io/upload_images/11895466-5719d01929682728.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

这样我们就实现了包含坏字符规则的框架代码，接下来，我们只需要向其中填入好后缀规则即可。好后缀处理过程中最核心的两点是：

- 在模式串中，查找和好后缀匹配的另一个子串；

- 在好后缀的的后缀子串中，查找最长的能和模式串前缀子串匹配的后缀子串。

因为**好后缀也是模式串本身的后缀子串**，因此，我们就可以在模式串和主串匹配之前通过预处理，来预先计算出模式串的每个后缀子串，对应的另一个与之匹配子串的位置。

因为后缀子串的最后一个字符位置固定，因此，要表示模式串的后缀子串，我们只需要记录其长度即可。

![](https://upload-images.jianshu.io/upload_images/11895466-5cf3ea77d5b508a2.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

接下来，我们引入 suffix 数组，其**下标表示后缀子串的长度，而数组里面存储的是与这个后缀子串匹配的另一个子串在模式串中的起始位置**，如下所示。

![](https://upload-images.jianshu.io/upload_images/11895466-de4495ea516bacff.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

另外，为了避免模式串滑动过头，如果有多个子串都和后缀子串匹配，我们需要记录**最靠后的那个子串的起始位置**。此时，我们已经找出了和后缀子串匹配的子串，但最终我们需要的是好后缀子串和模式串的前缀子串匹配的位置。因此，只有这一个数组是不够的，我们引入另外一个布尔型数组 prefix，来记录模式串的后缀子串是否能匹配其前缀子串。

![](https://upload-images.jianshu.io/upload_images/11895466-295e7d2aa030c2e9.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

我们拿模式串中下标从 0 到 i 的子串（i 可以是 0 到 m-2）与整个模式串，求公共后缀子串。如果公共后缀子串的长度为 k，那我们就记录 suffix[k] = j（j 表示公共后缀子串的起始下标）。如果 j=0，也就说公共后缀子串也是模式串的前缀子串，我们就记录 prefix[k]=true。

![](https://upload-images.jianshu.io/upload_images/11895466-f543f4d7c525f9e3.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```c
// 生成好后缀数组
void GenerateGS(char str[], int m, int suffix[]， bool prefix[])
{
    for (int i = 0; i < m; i++)
    {
        suffix[i] = -1;
        prefix[i] = false;
    }

    // [0, i] 的子串和模式串求公共后缀子串
    for (int i = 0; i < m-1; i++)
    {
        int j = i;
        int k = 0;
        while (j>=0 && str[j] == str[m-1-k]) // 下标都向前移动
        {
            j--;
            k++;
        }

        if (k != 0) suffix[k] = j + 1; // 公共后缀子串的起始位置
        if (j == -1) prefix[k] = true; // 公共后缀子串同时也是模式串的前缀子串
    }
}
```

接下来，我们来看遇到不匹配的字符时，如何根据好后缀规则，计算模式串向后移动的位数？

假设好后缀的长度是 k，我们首先检查 suffix[k] 是否为 -1。如果不为 -1，那 x=suffix[k] 就代表与好后缀匹配的前缀子串在模式串中的起始位置，我们就需要将模式串向后移动 j-x+1 个位置，j 为坏字符对应于模式串中的位置。如果为 -1 则说明不存在匹配的子串，我们就寻找是否存在与好后缀的后缀子串匹配的前缀子串。

![](https://upload-images.jianshu.io/upload_images/11895466-e3b6daf1841f580a.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

好后缀的后缀子串 b[r, m-1] 的长度为 k=m-r，其中 r 取值为 [j+2, m-1]，如果 prefix[k]=true，表示长度为 k 的后缀子串有可匹配的前缀子串，我们就需要将模式串向后移动 r 个位置。

![](https://upload-images.jianshu.io/upload_images/11895466-5e674575b6fa1d3d.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


如果上面两种情况都不满足，那我们就需要将模式串向后移动 m 个位置，即移动到好后缀后面的位置。下图中应该是写错了，注意！！！

![](https://upload-images.jianshu.io/upload_images/11895466-ff626184979d19bb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```c
// 判断好后缀规则应该移动的位数
int MoveByGS(int j, int m, int suffix[], bool prefix[])
{
    int k = m - j - 1; // 好后缀长度
    if (suffix[k] != -1) return j + 1 - suffix[k];

    for (int r = j + 2; r < m; r++)
    {
        if (prefix[m-r] == true) return r;
    }

    return m;
}

int BM(char str1[], int n, char str2[], int m)
{
    int bc[SIZE]; // 记录每个字符在模式串中最后出现的位置，作为坏字符散列表
    GenerateBC(str2, m, bc);

    int suffix[m];
    bool prefix[m];
    GenerateGS(str2, m, suffix, prefix);

    int i = 0; // 表示主串和模式串对齐时第一个字符的位置
    int si = 0; // 坏字符对应于模式串中的位置
    int xi = -1; // 坏字符在模式串中最后出现的位置

    while (i <= n-m)
    {
        int j = 0;
        // 从后向前进行匹配
        for (j = m-1; j >= 0; j--)
        {
            // 找到了第一个不匹配的字符
            if (str1[i+j] != str2[j]) break;
        }

        if (j < 0) return i; // 匹配成功

        si = j;
        xi = bc[str1[i+j] - '\0'];
        int x = si - xi; // 坏字符规则应该向后移动的位数
        int y = 0; // 好后缀规则应该向后移动的位数

        if (j < m-1) y = MoveByGS(j, m, suffix, prefix);

        x = x > y ? x : y;
        i = i + x;
    }

    return -1;
}
```

### 4. BM 算法性能分析及优化

整个算法用到了额外的三个数组，bc 与字符集的大小有关，suffix 和 prefix 与模式串大小有关。如果我们处理字符集很大的字符串匹配问题，bc 数组对内存的消耗就会比较多。因为好后缀规则和坏字符规则是独立的，如果我们对运行的环境内存要求比较苛刻，那么就可以只使用好后缀规则。不过，这样 BM 算法的效率就会有一些下降。

另外，在极端情况下，预处理计算 suffix 和 prefix 数组的性能会比较差，比如模式串是 aaaaaa 这种包含很多重复字符的模式串，预处理的时间复杂度就是 $O(m^2)$。当然，大部分情况下，时间复杂度不会这么差。现有一些论文证明了在最坏情况下， BM 算法的比较次数上限是 3n。


[参考资料-极客时间专栏《数据结构与算法之美》](https://time.geekbang.org/column/126)

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

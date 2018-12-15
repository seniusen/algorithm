> 网站上的敏感词过滤是怎么实现的呢？

实际上，这些功能最基本的原理就是字符串匹配算法，也就是通过维护一个敏感词的字典，当用户输入一段文字内容后，通过字符串匹配算法来检查用户输入的内容是否包含敏感词。

BF、RK、BM、KMP 算法都是针对只有一个模式串的字符串匹配算法，而要实现一个高性能的敏感词过滤系统，就需要用到**多模式匹配算法**了。

### 1. 基于单模式和 Trie 树实现的敏感词过滤

多模式匹配算法，就是在多个模式串和一个主串之间做匹配，也就是在一个主串中查找多个模式串。

敏感词过滤，也可以通过单模式匹配算法来实现，那就是针对每个敏感值都做一遍单模式匹配。但如果敏感词很多，并且主串很长，那我们就需要遍历很多次主串，显然这种方法是非常低效的。

而多模式匹配算法只需要扫描一遍主串，就可以一次性查找多个模式串是否存在，匹配效率就大大提高了。那如何基于 Trie 树实现敏感词过滤功能呢？

我们可以首先对敏感词字典进行预处理，构建成 Trie 树。这个预处理的操作只需要做一次，如果敏感词字典动态更新了，我们只需要在 Trie 树中添加或删除一个字符串即可。

用户输入一个文本内容后，我们把用户输入的内容作为主串，从第一个字符开始在 Trie 树中进行匹配。当匹配到叶子节点或者中途遇到不匹配字符的时候，我们就将主串的匹配位置后移一位，重新进行匹配。

基于 Trie 树的这种处理方法，有点类似单模式匹配的 BF 算法。我们知道 KMP 算法在 BF 算法基础上进行了改进，每次匹配失败时，尽可能地将模式串往后多滑动几位。同样，在这里，我们是否也可以对多模式串 Trie 树进行同样的改进呢？这就要用到 AC 自动机算法了。

### 2.  AC 自动机多模式匹配算法

AC 自动机算法，全称是 Aho-Corasick 算法。**AC 自动机实际上就是在 Trie 树之上，加了类似于 KMP 算法的 next 数组，只不过此处的数组是构建在树上罢了**。

```c
class ACNode
{
public:

    char data;
    bool is_ending_char;   // 是否结束字符
    int length;            // 当前节点为结束字符时记录模式串长度
    ACNode *fail;          // 失败指针
    ACNode *children[26];  // 字符集只包含 a-z 这 26 个字符

    ACNode(char ch)
    {
        data = ch;
        is_ending_char = false;
        length = -1;
        fail = NULL;
        for (int i = 0; i < 26; i++)
            children[i] = NULL;
    }
};
```

AC 自动机的构建包含两个操作：

- 将多个模式串构建成 Trie 树；

- 在 Trie 树上构建失败指针，就相当于[ KMP 算法](https://blog.csdn.net/seniusen/article/details/84961129)中的失效函数 next 数组。

构建 Trie 树的过程可以参考 [Trie 树——搜索关键词提示](https://blog.csdn.net/seniusen/article/details/85008972)，这里只是多了一个模式串的长度而已。假设我们的 4 个模式串分别为 c，bc，bcd，abcd，那么构建好的 Trie 树如下所示。

![](https://upload-images.jianshu.io/upload_images/11895466-0f9d8b9104a1468a.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

Trie 树中的每一个节点都有一个失败指针，它的作用和构建过程，和 KMP 算法中 next 数组极其相似。

假设我们沿着 Trie 树走到 p 节点，也就是下图中的紫色节点，那 p 的失败指针也就是从根节点走到当前节点所形成的字符串 abc，和所有模式串前缀匹配的最长可匹配后缀子串，这里就是 bc 模式串。

字符串 abc 的后缀子串有 c 和 bc，我们拿它们和其它模式串进行匹配，如果能够匹配上，那这个后缀就叫作可匹配后缀子串。在一个字符串的所有可匹配后缀子串中，长度最长的那个叫作最长可匹配后缀子串。我们就将一个节点的失败指针指向其最长可匹配后缀子串对应的模式串前缀的最后一个节点。

![](https://upload-images.jianshu.io/upload_images/11895466-a18824968d689c47.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

其实，如果我们把树中相同深度的节点放到同一层，那么某个节点的失败指针只有可能出现在它所在层的上面。因此，我们可以像 KMP 算法那样，利用已经求得的、深度更小的那些节点的失败指针来推导出下面节点的失败指针。

首先，根节点的失败指针指向 NULL，第一层节点的失败指针都指向根节点。然后，继续往下遍历，如果 p 节点的失败指针指向 q，那么我们需要看节点 p 的子节点 pc 对应的字符，是否也可以在节点 q 的子节点 qc 中找到。如果找到了一个子节点 qc 和 pc 的字符相同，则将 pc 的失败指针指向 qc。

![](https://upload-images.jianshu.io/upload_images/11895466-952e51ab3e514653.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

如果找不到一个子节点 qc 和 pc 的字符相同，那么我们继续令 q = q->fail，重复上面的查找过程，直到 q 为根节点为止。如果还没有找到，那就将 pc 的失败指针指向根节点。

![](https://upload-images.jianshu.io/upload_images/11895466-25c9657833b86aec.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```c
// 构建失败指针
    void build_failure_pointer()
    {
        queue<ACNode *> AC_queue;
        AC_queue.push(root);

        while (!AC_queue.empty())
        {
            ACNode *p = AC_queue.front();
            AC_queue.pop();
            for (int i = 0; i < 26; i++)
            {
                ACNode *pc = p->children[i];

                if (pc == NULL) continue;
                if (p == root) pc->fail = root;
                else
                {
                    ACNode *q = p->fail;
                    while (q != NULL)
                    {
                        ACNode *qc = q->children[pc->data - 'a'];
                        if (qc != NULL)
                        {
                            pc->fail = qc;
                            break;
                        }
                        q = q->fail;
                    }

                    if (q == NULL) pc->fail = root;
                }
                AC_queue.push(pc);
            }
        }
    }
```

通过按层来计算每个节点的子节点的失败指针，例中最后构建完之后的 AC 自动机就是下面这个样子。

![](https://upload-images.jianshu.io/upload_images/11895466-fa9da13b39e1b1f8.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

接下来，我们看如何在 AC 自动机上匹配子串？首先，主串从 i=0 开始，AC 自动机从指针 p=root 开始，假设模式串是 b，主串是 a。

- 如果 p 指向的节点有一个等于 a[i] 的子节点 x，我们就更新 p 指向 x，这时候我们还要**检查这个子节点的一系列失败指针对应的路径是否为一个完整的模式串**，之后我们将 i 增 1，继续重复这两个过程；

- 如果 p 指向的节点没有等于 a[i] 的子节点，我们就更新 p = p->fial，继续重复这两个过程。

```c
    // 在 AC 自动机中匹配字符串
    void match_string(const char str[])
    {
        ACNode *p = root;
        for (unsigned int i = 0; i < strlen(str); i++)
        {
            int index = int(str[i] - 'a');
            while (p->children[index] == NULL && p != root)
            {
                p = p->fail;
            }
            p = p->children[index];

            if (p == NULL) p = root; // 没有可匹配的，从根节点开始重新匹配
            ACNode *temp = p;
            while (temp != root)
            {
                if (temp->is_ending_char == true)
                {
                    int pos = i - temp->length + 1;
                    cout << "Fing a match which begins at position " << pos << ' '
                    << "and has a length of " << temp->length << '!'<< endl;
                }
                temp = temp->fail;
            }
        }
    }
```

全部代码如下：

```c
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

class ACNode
{
public:

    char data;
    bool is_ending_char;   // 是否结束字符
    int length;            // 当前节点为结束字符时记录模式串长度
    ACNode *fail;          // 失败指针
    ACNode *children[26];  // 字符集只包含 a-z 这 26 个字符

    ACNode(char ch)
    {
        data = ch;
        is_ending_char = false;
        length = -1;
        fail = NULL;
        for (int i = 0; i < 26; i++)
            children[i] = NULL;
    }
};

class AC
{
private:

    ACNode *root;

public:

    // 构造函数，根节点存储无意义字符 '/'
    AC()
    {
        root = new ACNode('/');
    }

    // 向 Trie 树中添加一个字符串
    void insert_string(const char str[])
    {
        ACNode *cur = root;
        for (unsigned int i = 0; i < strlen(str); i++)
        {
            int index = int(str[i] - 'a');
            if (cur->children[index] == NULL)
            {
                ACNode *temp = new ACNode(str[i]);
                cur->children[index] = temp;
            }
            cur = cur->children[index];
        }
        cur->is_ending_char = true;
        cur->length = strlen(str);
    }

    // 构建失败指针
    void build_failure_pointer()
    {
        queue<ACNode *> AC_queue;
        AC_queue.push(root);

        while (!AC_queue.empty())
        {
            ACNode *p = AC_queue.front();
            AC_queue.pop();
            for (int i = 0; i < 26; i++)
            {
                ACNode *pc = p->children[i];

                if (pc == NULL) continue;
                if (p == root) pc->fail = root;
                else
                {
                    ACNode *q = p->fail;
                    while (q != NULL)
                    {
                        ACNode *qc = q->children[pc->data - 'a'];
                        if (qc != NULL)
                        {
                            pc->fail = qc;
                            break;
                        }
                        q = q->fail;
                    }

                    if (q == NULL) pc->fail = root;
                }
                AC_queue.push(pc);
            }
        }
    }

    // 在 AC 自动机中匹配字符串
    void match_string(const char str[])
    {
        ACNode *p = root;
        for (unsigned int i = 0; i < strlen(str); i++)
        {
            int index = int(str[i] - 'a');
            while (p->children[index] == NULL && p != root)
            {
                p = p->fail;
            }
            p = p->children[index];

            if (p == NULL) p = root; // 没有可匹配的，从根节点开始重新匹配
            ACNode *temp = p;
            while (temp != root)
            {
                if (temp->is_ending_char == true)
                {
                    int pos = i - temp->length + 1;
                    cout << "Fing a match which begins at position " << pos << ' '
                    << "and has a length of " << temp->length << '!'<< endl;
                }
                temp = temp->fail;
            }
        }
    }
};

int main()
{
    //char str[][8] = {"how", "he", "her", "hello", "so", "see", "however"};
    char str[][5] = {"abce", "bcd", "ce"};

    AC test;
    for (int i = 0; i < 7; i++)
    {
        test.insert_string(str[i]);
    }

    test.build_failure_pointer();
    //test.match_string("however, what about her boyfriend?");
    test.match_string("abcfabce");

    return 0;
}
```

### 3. AC 自动机的复杂度分析

首先，构建 Trie 树的时间复杂度为 O(m*len)，其中 len 表示敏感词的平均长度，m 表示敏感词的个数。

其次，假设 Trie 树中总共有 k 个节点，每个节点在构建失败指针的时候，最耗时的就是 while 循环部分，这里 q = q->fail，每次节点的深度都在减小，树的最大深度为 len，因此每个节点构建失败指针的时间复杂度为 O(len)，整个失败指针构建过程的时间复杂度为 O(k*len)。不过，AC 自动机的构建过程都是预先处理好的，构建好之后并不会频繁更新。

最后，假设主串的长度为 n，匹配的时候每一个 for 循环里面的时间复杂度也为 O(len)，总的匹配时间复杂度就为 O(n*len)。因为敏感词不会很长，而且这个时间复杂度只是一个非常宽泛的上限，实际情况下，可能近似于 O(n)，所以，AC 自动机匹配的效率非常高。

从时间复杂度上看，AC 自动机匹配的效率和 Trie 树一样，但是一般情况下，大部分节点的失败指针都指向根节点，AC 自动机实际匹配的效率要远高于 O(n*len)。只有在极端情况下，AC 自动机的性能才会退化为和 Trie 树一样。

![](https://upload-images.jianshu.io/upload_images/11895466-5a2f86eacd644f04.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


[参考资料-极客时间专栏《数据结构与算法之美》](https://time.geekbang.org/column/126)

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

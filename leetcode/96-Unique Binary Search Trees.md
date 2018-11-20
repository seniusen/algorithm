
#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-1de09ea17992f8ee.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 2. 解答

以 $1, 2, \cdots, n$ 构建二叉搜索树，其中，任意数字都可以作为根节点来构建二叉搜索树。当我们将某一个数字作为根节点后，其左边数据将构建为左子树，右边数据将构建为右子树。因此，这是一个递归问题。

若以第 $i$ 个数据为根节点，其左边数据有 $i-1$ 个，左子树可能情况为 left_num，右边数据有 $n-i$ 个，右子树可能情况为 right_num，因此以当前数据为根节点可以构建出 left_num * right_num 个二叉搜索树。

所以，我们要做的就是遍历 $i = 1\cdots n$，统计出每个数据作为根节点可以构建出的二叉搜索树总个数即可。

- 递归法

```c
class Solution {
public:
        
       int numTrees(int n) {

        int sum = 0;

        if (n <= 1) return 1;

        // 以当前的数为根节点，左右两边的数分别构建子树
        for (int i = 1; i <= n; i++)
        {
            int left_num = numTrees(i - 1); // 左边的数可以构建多少个二叉搜索树

            int right_num = numTrees(n - i); // 右边的数可以构建多少个二叉搜索树

            sum += left_num * right_num;
        }

        return sum;
    }
};
```

但是上面的程序运行时超时了，其实我们只需要统计一半数据就可以了，因为两边是对称的。

比如我们有 1,2,3,4,5 五个数，以 2 作为根节点，左边有 1 个数，右边有 3 个数。以 4 作为根节点，左边有 3 个数，右边有 1 个数。这两种情况是一样的，因此如果数据个数为偶数，我们只需要统计一半数据即可，而为奇数的话我们就要再多统计一个中间数据。

```c
class Solution {
public:
    
    int numTrees(int n) {
        
        int sum = 0;
          
        if (n <= 1) return 1;
        
        int is_odd = n % 2;
        int mid = n / 2;
        
        // 以当前的数为根节点，左右两边的数分别构建子树
        for (int i = 1; i <= mid; i++)
        {
            int left_num = numTrees(i - 1); // 左边的数可以构建多少个二叉搜索树
            
            int right_num = numTrees(n - i); // 右边的数可以构建多少个二叉搜索树
            
            sum += left_num * right_num;
        }
        
        sum = sum * 2;
        
        if (is_odd) sum = sum + numTrees(mid) * numTrees(n - mid - 1);
            
        return sum;
    }
};
```

此外，我们还可以定义一个全局变量，来存放已经计算过的数值，避免在递归过程中大量地重复计算。

```c
class Solution {
public:
    
    #define MAX 1000
    
    int nums[MAX]; // 存放已经计算过的数值

    int numTrees(int n) {

        int sum = 0;

        //if (n <= 0) return 1;
        if (n <= 1) return 1;

        // 以当前的数为根节点，左右两边的数分别构建子树
        for (int i = 1; i <= n; i++)
        {
            if (nums[i-1] == 0) nums[i-1] = numTrees(i - 1); // 左边的数可以构建多少个二叉搜索树
            int left_num = nums[i-1];

            if (nums[n-i] == 0) nums[n-i] = numTrees(n - i); // 右边的数可以构建多少个二叉搜索树
            int right_num = nums[n-i]; 

            sum += left_num * right_num;
        }

        return sum;
    }
};
```

- 迭代法
 还可以将递归改写为循环，避免函数多次调用执行效率较低。

```c
class Solution {
public:
    
    int numTrees(int n) {

        int nums[n+1] = {0};

        nums[0] = 1;
        nums[1] = 1;
       
        if (n <= 1) return 1;
        
        for (int i = 2; i <= n; i++)
        {
            // 从 n=2 开始统计可以构建多少个不同的二叉搜索树
            for (int j = 1; j <= i; j++)
            {
                nums[i] += nums[j-1] * nums[i-j];
            }
        }

        return nums[n];
    }
};      
```


获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-d1412c91e9ba0d5a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

### 2. 解答

### 2.1. 方法一
题目要求不能使用乘法、除法和除余运算，但我们可以将**除法转移到对数域**。

$$ \frac{a}{b} = e^{\frac{lna}{lnb}} = e^{lna - lnb}$$

这样就转化为指数、对数和减法运算了。因为只能对正整数取对数，因此我们首先要将两个数都取绝对值，最后再加上符号。

同时，题目要求只能存储 32 位有符号整数，因此，当数据大于上边界时，需要进行特殊处理。
```c
class Solution {
public:
     
    int divide(int dividend, int divisor) {
        if(dividend == 0)  return 0;

        double a = fabs(dividend);
        double b = fabs(divisor);
        
        long result = exp(log(a) - log(b));
        
        if ((dividend < 0) ^ (divisor < 0)) result = -result;
        
        if (result > INT_MAX) result = INT_MAX;
        
        return result;
    }
};
```
### 2.2. 方法二

**利用移位操作**。看下面的例子：

$$ 10  \implies  2^1 * 3 + 2^0 * 3 \to \frac{10} {3} = 2^1 + 2^0 = 3$$
$$ 10  \implies  2^2 * 2 + 2^0 * 2 \to \frac{10} {2} = 2^2 + 2^0 = 5$$
$$ 10  \implies  2^3 * 1 + 2^1 * 1 \to \frac{10} {3} = 2^3 + 2^1 = 10$$

我们可以对被除数进行分解。以 10 和 3 为例，首先我们确定 3 的最高次系数，$ 10 > 3*2^1 $ && $ 10 < 3*2^2$，因此最高次系数为 2。然后我们用 10 减去 $3*2^1$，继续进行刚才的过程，$ 4 > 3*2^0 $ && $ 4 < 3*2^1$，第二高次系数为 1。我们循环进行这个过程，直到最后的数小于除数为止，这些除数前面所有系数的和即为所求。



```c
class Solution {
public:
     
    int divide(int dividend, int divisor) {
  
        long a = labs(dividend); // long 型数据占 8 个字节，labs() 函数对 long 求绝对值
        long b = labs(divisor);
        long temp = b;
        
        long result = 0;
        long cnt = 1;
        
        while (a >= b)
        {
            cnt = 1;
            temp = b;
            while (a >= (temp << 1))
            {
                temp  = temp << 1;
                cnt = cnt << 1; // 表征除数前面的各次系数
            }
            
            a -= temp;
            result += cnt;          
        }
        
        if ((dividend < 0) ^ (divisor < 0)) result = -result;
          
        if (result > INT_MAX) result = INT_MAX; // INT_MAX = 2^32 - 1
        
        return result;*/
    }
};
```


获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

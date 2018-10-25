#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-99b8edc2baf59d08.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)



#### 2. 解答

```c

class Solution {
public:
    double myPow(double x, int n) {
                
        if (n >= 0)
        {
            return Pow(x, n);
        }
        else
        {
            return 1 / Pow(x, -n);
        }
    }
    
    double Pow(double x, int n)
    {
        if (n == 0)
        {
            return 1;
        }
        else if(n == 1)
        {
            return x;
        }
        else
        {
            if (n % 2 == 0)
            {
                return Pow(x, n / 2) * Pow(x, n / 2);
            }
            else
            {
                return Pow(x, n / 2) * Pow(x, n / 2) * x;
            } 
        }
    }
    
};
```

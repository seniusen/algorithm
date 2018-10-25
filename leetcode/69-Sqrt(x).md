#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-b867bdcf74967551.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 2. 解答

```c

class Solution {
public:
    int mySqrt(int x) {
        
        int left = 0; 
        int right = x;
        long mid = 0;
        long square = 0;
        
        while(left <= right)
        {
            mid = left + (right - left) / 2; // 注意整数的范围
            
            square = mid * mid; // 注意整数的范围
            
            if (square == x)
            {
                return mid;
            }
            else if (square > x)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
  
        return left - 1;
    }
};

```

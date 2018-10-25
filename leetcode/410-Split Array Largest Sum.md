#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-f0ab3bb9674faa47.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)



#### 2. 解答

```c

class Solution {
public:
    
    // 若分割数组的最大值为 value，判断能否进行划分
    bool cansplit(vector<int>& nums, int value, int m)
    {  
        int len = nums.size();
        int i = 0;
        int sum = 0;
        int split_count = 0; // 分割次数
        
        // 依次往后求和，若和小于等于 value，则继续加；
        // 若和大于 value，则分割次数加 1，从当前位置开始将和清零，重新开始
        for (i = 0; i < len; i++)
        {
            if (sum + nums[i] <= value)
            {
                sum += nums[i];
            }
            else
            {
                split_count++;
                sum = nums[i];
            }
            
            if (split_count == m)  // 分割次数超出 m, 不满足划分
            {
                return false;
            }
        }
        
        return true;           
    }
    
    int splitArray(vector<int>& nums, int m) {
        
        int len = nums.size();
        int i = 0;    
        // 分割数组的最大值介于数组的最大元素和数组所有元素的和之间
        int max = nums[0];
        int sum = 0;
        for (i = 0; i < len; i++)
        {
            if (nums[i] > max)
            {
                max = nums[i];
            }
            sum += nums[i];
        }
        
        int left = max;
        int right = sum;
        int mid = 0;
        while(left < right)
        {
            mid = left + (right - left) / 2;
            
            if (cansplit(nums, mid, m)) // 能划分，继续找有没有更小的值
            {
                right = mid; //不减是因为无法确保减一之后的数是否满足划分
            } 
            else // 不能划分，增大数值继续寻找
            {
                left = mid + 1;
            }
        }
        
        return left; 
        // 最终 left = right 结束，left 值就是所求
        
    }
};

```

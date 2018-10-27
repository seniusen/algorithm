#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-1ff6efa376e73eff.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 2. 解答

##### 2.1. 方法一

基于 [LeetCode 33——搜索旋转排序数组](https://blog.csdn.net/seniusen/article/details/83447729) 中的方法二。

当 nums[mid] = nums[right] 时，比如 [1, 1, 2, 1, 1]，[1, 1, 0, 1, 1]，为了找到正确的转折点，**我们查看 [mid, right] 之间有没有不等于 nums[mid] 的值**，若有，则继续向右查找；否则向左查找。

```c

class Solution {
public:

    int Binary_Search(vector<int>& nums, int left, int right, int target) 
    {
        int mid = 0;
        
        while(left <= right)
        {
            mid = left + (right - left) / 2;
            if (nums[mid] == target)
            {
                return mid;
            }
            else if(nums[mid] < target)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
            
       return -1;     
    }
        
    bool search(vector<int>& nums, int target) {
        
        if (nums.size() == 0) return 0; // 数组为空
        
        int left = 0;
        int right = nums.size() - 1;
        int mid = 0;
        
        while(left < right)
        {
            mid = left + (right - left) / 2;
            
            if (nums[mid] > nums[right])
            {
                left = mid + 1;
            }
            else if (nums[mid] < nums[right])
            {
                right = mid;
            }
            else // nums[mid] = nums[right]
            {  
                int flag = 1;
                
                for (int i = mid; i < right; i++)
                {
                    int temp = nums[mid];
                    if (nums[i] != temp) // mid 到 right 之间有不等于 nums[mid] 的值，向右边查找
                    {
                        flag= 0;
                        left = mid + 1;
                        break;
                    }   
                }
                
                if (flag)
                {
                    right = mid; // mid 到 right 之间没有小于 nums[mid] 的值，向左边查找
                }
            }
        }
                        
        int a = Binary_Search(nums, 0, right-1, target);
        int b = Binary_Search(nums, right, nums.size() - 1, target);
                
        return a == -1 && b == -1 ? false : true;
        
    }
};

```

##### 2.2. 方法二

基于 [LeetCode 33——搜索旋转排序数组](https://blog.csdn.net/seniusen/article/details/83447729) 中的方法三。 

当 nums[mid] = nums[right] 时，比如 [1, 1, 2, 1, 1]，[1, 1, 0, 1, 1]，**我们直接将右边界 right 减一**，然后继续查找。

```c
class Solution {
public:

    bool search(vector<int>& nums, int target) {
        
       int left = 0;
        int right = nums.size() - 1;
        int mid = 0;
        
        while(left <= right)
        {
            mid = left + (right - left) / 2;
            
            if (nums[mid] == target)
            {
                return true;
            }
            else if (nums[mid] < nums[right])  // nums[mid] 在右边升序的数据区间内    
            {
                if (nums[mid] < target && target <= nums[right]) left = mid + 1;
                else    right = mid - 1;
            }
            else if (nums[mid] > nums[right]) // nums[mid] 在左边升序的数据区间内    
            {
                if (nums[left] <= target && target < nums[mid]) right = mid - 1;
                else    left = mid + 1;
            }
            else // nums[mid] = nums[right]
            {
                right--;
            }
        }
        
        return false;
    }
};

```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-5d6a80e66bc4c378.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 2. 解答

##### 2.1. 方法一

>直接进行二分查找，在判断查找方向的时候详细分类。

当 nums[mid] < target 时，
- 若 nums[left] <= nums[mid]，此时，target 一定在nums[mid] 右边，继续向右查找。
- 若 nums[left] > nums[mid] < nums[right]，此时 nums[mid] 两边都有较大的元素，我们要进一步确定查找的方向。
    - 若 target <= nums[right]，则向右查找。
    - 若 target >= nums[left]，则向左查找。
    - 若 nums[right] < target < nums[left]，则不存在。

当 nums[mid] > target 时，
- 若 nums[mid] <= nums[right]，此时，target 一定在nums[mid] 左边，继续向左查找。
- 若 nums[left] <= nums[mid] > nums[right]，此时 nums[mid] 两边都有较小的元素，我们要进一步确定查找的方向。
    - 若 target <= nums[right]，则向右查找。
    - 若 target >= nums[left]，则向左查找。
    - 若 nums[right] < target < nums[left]，则不存在。

```c

class Solution {
public:
    
       int search(vector<int>& nums, int target) {
        
        if (nums.size() == 0) return -1; // 数组为空
        
        int left = 0;
        int right = nums.size() - 1;
        int mid = 0;

        while(left <= right)
        {
            mid = left + (right - left) / 2;
            
            if (nums[mid] == target)
            {
                return mid;
            }
            else if (nums[mid] < target)
            {
                if (nums[left] <= nums[mid]) // l <= m < r
                {
                    left = mid + 1;
                }
            
                else if (nums[left] > nums[mid] && nums[mid] < nums[right])
                {
                    if (nums[left] <= target)
                    {
                        right = mid - 1;
                    }
                    else if (nums[right] >= target)
                    {
                        left = mid + 1;
                    }
                    else
                    {
                        return -1;
                    }
                }    
            }
            else
            {
                if (nums[mid] <= nums[right]) // = 是只有一个元素的情况
                {
                    right = mid - 1;
                }
                else if (nums[left] <= nums[mid] && nums[mid] > nums[right]) // = 是因为 mid 等于 left 的情况
                {
                    if (nums[left] <= target)
                    {
                        right = mid - 1;
                    }
                    else if (nums[right] >= target)
                    {
                        left = mid + 1;
                    }
                    else
                    {
                        return -1;
                    }
                } 
            }
        }
        
        return -1;

```

##### 2.2. 方法二

>先利用二分查找确定转折点，然后对转折点两侧的数据分别再进行二分查找。

当 nums[mid] > nums[right] 时，说明 nums[mid] 在转折点左侧，继续向右查找。

当 nums[mid] < nums[right] 时，向左缩小区间，直到 left = right 时，此时 right 即为转折点的位置。

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
        
    int search(vector<int>& nums, int target) {
        
        if (nums.size() == 0) return -1; // 数组为空
        
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
            else
            {
                right = mid;
            }
        }
                
        int a = Binary_Search(nums, 0, right-1, target);
        int b = Binary_Search(nums, right, nums.size() - 1, target);
                
        return a > b ? a : b;
    }
};

```

##### 2.3. 方法三

>nums[mid] 要么**落在左边升序的数据区间内，要么落在右边升序的数据区间内**。

当 nums[mid] 在右边升序的数据区间内
  
-  若 nums[mid] < target <= nums[right]，则向右查找；否则向左查找。

当 nums[mid] 在左边升序的数据区间内
  
-  若 nums[left] <= target < nums[mid]，则向左查找；否则向右查找。
    

```c

class Solution {
public:

    int search(vector<int>& nums, int target) {
        
        int left = 0;
        int right = nums.size() - 1;
        int mid = 0;
        
        while(left <= right)
        {
            mid = left + (right - left) / 2;
            
            if (nums[mid] == target)
            {
                return mid;
            }
            else if (nums[mid] < nums[right])  // nums[mid] 在右边升序的数据区间内    
            {
                if (nums[mid] < target && target <= nums[right]) left = mid + 1;
                else    right = mid - 1;
            }
            else // nums[mid] 在左边升序的数据区间内    
            {
                if (nums[left] <= target && target < nums[mid]) right = mid - 1;
                else    left = mid + 1;
            }
        }
        
        return -1;
    }
};

```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

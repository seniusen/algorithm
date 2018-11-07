
#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-83d1a09dc6b1bc8f.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 2. 解答

##### 2.1. 方法一

由于两个数组都是排好序的，因此首先可以想到的思路就是利用归并排序把两个数组合并成一个有序的长数组，然后直接取出中位数即可。

```python
class Solution:
    def findMedianSortedArrays(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: float
        """
        
        len1 = len(nums1)
        len2 = len(nums2)
        nums = []
        
        i = 0
        j = 0
        
        while (i < len1 and j < len2):
            
            if (nums1[i] <= nums2[j]):
                nums.append(nums1[i])
                i += 1
            
            else:
                nums.append(nums2[j])
                j += 1
        
        if (i < len1):
            while(i < len1):
                nums.append(nums1[i])
                i += 1
            
        if (j < len2):
            while(j < len2):
                nums.append(nums2[j])
                j += 1
        
        odd = (len1 + len2) % 2 # 长度是否为奇数
        mid = (len1 + len2 - 1) // 2
        if (odd):
            return nums[mid]
        else:
            return (nums[mid] + nums[mid+1]) / 2
```

因为要遍历两个数组，所以时间复杂度为 $O(m+n)$，而题目中要求算法的时间复杂度为 $O(log (m+n))$，因此应该是有更高效的算法，借助于二分查找。

##### 2.2. 方法二

> 所谓中位数，就是将 K 个数据分为长度相等的两组，左边的数据小于等于右边的数据。

如果我们要在任意位置 $i$ 处将长度为 $m$ 的数组 $A$ 分为两部分，则共有 $m+1$ 种分法，$i=[0, m]$。

$$  left\_part \quad | \quad right\_part$$
$$ A[0], A[1], \cdot \cdot \cdot, A[i-1] \quad | \quad A[i], A[i+1], \cdot \cdot \cdot, A[m-1]$$

$i=0$ 说明左半部分没有元素，反之 $i=m$ 说明右半部分没有元素。左半边元素个数为 $i$ ，右半边元素个数为$m-i$。

同理，我们可以在任意位置 $j$ 处将长度为 $n$ 的数组 $B$ 分为两部分，则共有 $n+1$ 种分法，$j=[0, n]$。

$$ B[0], B[1], \cdot \cdot \cdot, B[j-1] \quad | \quad B[j], B[j+1], \cdot \cdot \cdot, B[n-1]$$

针对划分完后的数组 $A$ 和 $B$，如果满足：

- 左边部分的长度等于右边部分的长度（偶数情况），$i+j = m-i + n-j$；或者等于右边部分的长度加 1（奇数情况） ,$i+j = m-i + n-j+1$。

- 左边的最大元素小于等于右边的最小元素，$A[i-1] <= B[j] \quad and \quad B[i-1] <= A[j]$。

那我们也就找到了中位数，$median = \frac{max(left\_part) + min(right\_part)}{2}$。

所以，我们要做的就是在 $i=[0, m]$ 区间搜索一个 $i$ 值，使得上面的条件得到满足。也即

$$ A[i-1] <= B[j] \quad and \quad B[i-1] <= A[j] ，其中 \quad j = \frac{m+n+[1]}{2}-i$$

**加不加 1 取决于总的长度是奇数还是偶数，同时，为了保证 $j$  的范围在 $[0, n]$，我们必须要求 $n\geqslant m$**。

接下来，我们就在 $i=[0, m]$ 区间进行二分查找。

- 1. 如果满足条件，则直接返回求取中位数。
- 2. 如果 $i > 0 \quad and \quad A[i-1] > B[j]$，则减小 $i$。如果增加 $i$，则 $j$ 减小，左边序列数组 $A$ 的值会更大，右边序列数组 $B$ 的值会更小。
- 3. 如果 $i < m \quad and \quad B[i-1] > A[j]$，则增加 $i$。如果减小 $i$，则 $j$ 增加，左边序列数组 $A$ 的值会更小，右边序列数组 $B$ 的值会更大。

最后，我们求得左半部分的最大值以及右半部分的最小值，然后就可以求出中位数了。

因为，要查找的范围为 $i=[0, m]$，而且每次查找缩小区间为原来的一半，因此时间复杂度为 $O(log(min(m, n))$，空间复杂度为  $O(1)$。

```c
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        
        
        int m = nums1.size();
        int n = nums2.size();
        int len = m + n;
        int odd = len % 2;
        
        int left = 0;
        int i = 0, j = 0;  
        vector<int>::iterator A = nums1.begin();
        vector<int>::iterator B = nums2.begin();
        
        // 确保数组 A 的长度小于等于数组 B 的长度
        if (m > n)
        {
            int temp = m;
            m = n;
            n = temp;
            A = nums2.begin();
            B = nums1.begin();
        }
        
        int right = m;
                
        while(left <= right)
        {
            i = left + (right - left) / 2;
            j = (len + odd) / 2 - i;
                        
            if (i > 0 && A[i-1] > B[j])
            {
                right = i - 1;
            }
            else if(i < m && B[j-1] > A[i])
            {
                left = i + 1;
            }
            else
            {
                break;
            } 
        }
         
        int left_max = 0;
        int right_min = 0;
        
        // 左半部分的最大值
        if (i == 0) left_max = B[j-1];
        else if (j == 0) left_max = A[i-1];
        else  left_max = A[i-1] <= B[j-1] ? B[j-1] : A[i-1];

        // 右半部分的最小值
        if (i == m) right_min = B[j];
        else if (j == n) right_min = A[i];
        else    right_min = A[i] <= B[j] ? A[i] : B[j];

        if (odd)
        {
            return left_max;
        }
        else
        {
            return float(left_max + right_min) / 2;
        }
    }
};
```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

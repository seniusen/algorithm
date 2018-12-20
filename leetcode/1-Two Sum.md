#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-772ff54ed41d43ea.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 2. 解答

- C++

遍历数组，将数组中的元素和索引分别作为 unordered_map 的键和值，如果目标值和当前元素的差已经存于在map 的键中，即找到结果。

```c
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        
        unordered_map<int, int> tabel;
        vector<int> index;
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            int val = target - nums[i];
            
            if (tabel.count(val) == 1)
            {
                index.push_back(tabel[val]);
                index.push_back(i);
                return index;
            }
            else
            {
                tabel[nums[i]] = i;
            }
        }
    }
};
```

- Python

遍历数组，将数组中的元素和索引分别作为字典的键和值，如果目标值和当前元素的差已经存于在字典的键中，即找到结果。

```python
class Solution:
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        hash_table = {}       
        
        for index, value in enumerate(nums):
            
            num = target - value
            
            if num in hash_table:
                return [hash_table[num], index]
            
            hash_table[value] = index
```


获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


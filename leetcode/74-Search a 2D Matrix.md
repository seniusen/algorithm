#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-1c37d25788f69039.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 2. 解答

- 若矩阵为空，比如 [], [[]]，此时直接返回 false。
- 若目标值小于矩阵第一个元素或者大于矩阵最后一个元素，则目标值不在矩阵范围内，直接返回 false。
- 其他情况下，则从矩阵第一行开始逐行扫描。若目标值位于矩阵某一行数值范围内，再针对矩阵的某一行用二分查找精准定位。

```c

class Solution {
public:
    
    bool binary_search(vector<int>& data, int target)
    {
        int left = 0;
        int right = data.size() - 1;
        int mid = 0;

        while(left <= right)
        {
            mid = left + (right - left) / 2;

            if (data[mid] == target)
            {
                return true;
            }
            if (data[mid] < target)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        return false;
    }

    bool searchMatrix(vector< vector<int> > & matrix, int target) {

        int row = matrix.size();
        if (row == 0) return false; // [] 矩阵为空，直接返回

        int col = matrix[0].size(); // [[]] 矩阵为空，直接返回
        if (col == 0) return false;

        if (target < matrix[0][0] || target > matrix[row-1][col-1]) return false; // 目标值小于第一个元素或者大于最后一个元素，直接返回

        // 按照矩阵的行依次扫描
        for (int i = 0; i < row; i++)
        {
            if (target == matrix[i][0])
            {
                return true;
            }
            else if (target == matrix[i][col-1])
            {
                return true;
            }
            else if (matrix[i][0] < target && target < matrix[i][col-1])
            {
                return binary_search(matrix[i], target);
            }
            else
            {
                continue;
            }
        }
        
        return false;
    }
};

```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

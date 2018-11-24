
#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-15031f145a101f92.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 2. 解答

##### 2.1. 方法一 

从矩阵的左下角开始比较
- 目标值等于当前元素，返回 true；
- 目标值大于当前元素，j 增 1，向右查找，排除掉此列上边的数据（都比当前元素更小）；
- 目标值小于当前元素，i 减 1，向上查找，排除掉此行右边的数据（都比当前元素更大）。

````
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        
        int i = matrix.size() - 1;
        int j = 0;
        while (i >=0 && j < matrix[0].size())
        {
            if (target == matrix[i][j]) return true;
            else if (target > matrix[i][j]) j++;
            else i--;
        }   
        return false;
    }
}；
````
##### 2.2. 方法二

$$\begin{array} {ccc|cc}1&4&7&11&15 \\ 2&5&8&12&19   \\ 3&6&\boxed9&16&22 \\  \hline 10&13&14&\boxed{17}&24 \\ 18&21&23&26&30 \end{array}$$

我们先沿着对角线的方向，找到第一个大于目标值的数字。比如目标值 14，我们发现 9<14<17。然后左上角和右下角的元素都可以排除掉了。我们只需再对左下角剩余的行和右上角剩余的列分别进行二分查找即可。

```c
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        
        int m = matrix.size();
        if (m == 0) return false;
        int n = matrix[0].size();
        if (n == 0) return false;
        
        if (m == 1) return binary_row_search(matrix, 0, n-1, target);
        if (n == 1) return binary_col_search(matrix, 0, m-1, target);
        
        int square = m <= n ? m : n;
        int i = 0;
        for (i = 0; i < square - 1; i++)
        {
            if (target == matrix[i][i] || target == matrix[i+1][i+1]) return true;
            else if (target > matrix[i][i] && target < matrix[i+1][i+1]) break;     
        }
        
        for (int row = i+1; row < m; row++)
        {
            if (binary_row_search(matrix, row, i, target)) return true;
        }
        
        for (int col = i+1; col < n; col++)
        {
            if (binary_col_search(matrix, col, i, target)) return true;
        }
        
        return false;
    }
    
    // 行搜索
    bool binary_row_search(vector<vector<int>>& matrix, int row, int end, int target)
    {
        int start = 0;
        while (start <= end)
        {
            int mid = start + ((end - start) >> 2); // 右移运算优先级小于加法，切记加括号！！！
            if (matrix[row][mid] == target) return true;
            else if (matrix[row][mid] < target) start = mid + 1;
            else end = mid - 1;
        }
        return false;
    }
    
    // 列搜索
    bool binary_col_search(vector<vector<int>>& matrix, int col, int end, int target)
    {
        int start = 0;
        while (start <= end)
        {
            int mid = start + ((end - start) >> 2); 
            if (matrix[mid][col] == target) return true;
            else if (matrix[mid][col] < target) start = mid + 1;
            else end = mid - 1;
        }
        return false;
    }
};
```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

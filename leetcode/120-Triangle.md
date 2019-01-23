#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-ba415e0eb68129fe.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 2. 解答

详细解答方案可参考[北京大学 MOOC 程序设计与算法（二）算法基础之动态规划部分](https://www.icourse163.org/course/PKU-1001894005)。

从三角形倒数第二行开始，某一位置只能从左下方或者右下方移动而来，因此，我们只需要求出这两者的较小值然后再加上当前元素，即可得出从某一位置到最下边的最小路径和。以此类推，我们就可以求出最上边元素的最小路径和。过程如下所示：

 | 2 |  |  |  |
 |  :------:| :------: | :------: | :------: |
 | 3 | 4 |  | |
| 6| 5 |7 | |
| 4 | 1 |8 |3 |
 
- 第三行到最下边的最小元素和

 | 7 | 6  | 10   |  3|
 |  :------:| :------: | :------: | :------: |
| min(4, 1) + 6| min(1, 8) + 5 | min(8, 3) + 7 |  |

- 第二行到最下边的最小元素和

| 9 | 10  | 10   | 3 |
 |  :------:| :------: | :------: | :------: |
| min(7, 6) + 3| min(6, 10) + 4 |  |  |

- 第一行到最下边的最小元素和

| 11 | 10  | 10   | 3 |
 |  :------:| :------: | :------: | :------: |
| min(9, 10) + 2| |  |  |

11 即为所求，同时可以看到，我们只需在原数组的最后一行进行计算即可，不用新建内存。

```c
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        
        int row = triangle.size() - 1;        
        
        for (int i = row - 1; i >=0; i--)
        {
            int col = triangle[i].size();
            for (int j = 0; j < col; j++)
            {
                triangle[row][j] = min(triangle[row][j], triangle[row][j+1]) + triangle[i][j];
            }
        }
        
        return triangle[row][0];
    }
};
```


获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

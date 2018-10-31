
#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-5f407822a048e560.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 2. 解答

将数独中数字的 ASCII 码值转化到 0-8 之间作为散列值，建立一个散列表，然后分别逐行、逐列、逐宫（3*3小块）统计每个数字的出现次数，若出现次数大于 1，则数独无效。

```c
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {

        int table[9] = {0};
        int i = 0, j = 0;
        int index = 0;
        
        // 逐行扫描，判断数字 1-9 在每一行是否只出现一次
        for (i = 0; i < 9; i++)
        {
            for (int m = 0; m < 9; m++)
            {
                table[m] = 0;
            }
            for (j = 0; j < 9; j++)
            {
                if (board[i][j] != 46) 
                {
                    index = board[i][j] - 49; // 将数字的 ASCII 转化为 1-9
                    table[index]++;
                    if (table[index] > 1)
                    {
                        return false;
                    }
                } 
            }
        }
        
        // 逐列扫描，判断数字 1-9 在每一列是否只出现一次
        for (i = 0; i < 9; i++)
        {
            for (int m = 0; m < 9; m++)
            {
                table[m] = 0;
            }
            for (j = 0; j < 9; j++)
            {
                if (board[j][i] != 46)
                {
                    index = board[j][i] - 49;
                    table[index]++;
                    if (table[index] > 1)
                    {
                        return false;
                    }
                }
            }
        }
        
        // 逐块扫描，判断数字 1-9 在每一块是否只出现一次
        int row = 0;
        int col = 0;
        
        for (int m = 0; m < 3; m++)
        {
            row = m * 3;
            for (int n = 0; n < 3; n++)
            {
                col = n * 3;
                for (int k = 0; k < 9; k++)
                {
                    table[k] = 0;
                }
                for (i = row; i < row+3; i++)
                {
                    for (j = col; j < col+3; j++)
                    {
                        if (board[i][j] != 46)
                        {
                            index = board[i][j] - 49;
                            table[index]++;
                            if (table[index] > 1)
                            {
                                return false;
                            }
                        }
                    }
                }
            }
        }
        
        return true;
    }
};
```
上面的方法需要对数独遍历三次，我们也可以做到在遍历一次的情况下判断数独是否有效。

针对每行、每列和每宫分别建立一个散列表，然后在遍历数独的时候，根据下标 $i, j$ 的变化确定三个散列表的值，若其中一个值大于 1，则数独无效。

其中，通过下标 $i, j$ 来获取如下宫的顺序可以通过 $i / 3 * 3 + j / 3$ 来获取。
![](https://upload-images.jianshu.io/upload_images/11895466-ae165de94e2d3e00.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

|  | $j / 3 = 0$ |$j / 3 = 1$ | $j / 3 = 2$ |
|  :------: |  :------:| :------: | :------: |
| $i / 3 = 0$ | 1 | 2 | 3 |
| $i / 3 = 1$ | 4 | 5 | 6|
| $i / 3 = 2$ |7 | 8 | 9 |

```c
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {

        int table1[9][9] = {0}, table2[9][9] = {0}, table3[9][9] = {0};
        int i = 0, j = 0;
        int index = 0;
        for (i = 0; i < 9; i++)
        {
            for (j = 0; j < 9; j++)
            {
                if (board[i][j] != 46) 
                {
                    index = board[i][j] - 49; // 将数字的 ASCII 转化为 0-8
                    table1[i][index]++;
                    
                    // 行散列表
                    if (table1[i][index] > 1)
                    {
                        return false;
                    }
                     // 列散列表
                    table2[j][index]++;
                    if (table2[j][index] > 1)
                    {
                        return false;
                    }
                     // 宫散列表
                    table3[i/3*3+j/3][index]++;
                    if (table3[i/3*3+j/3][index] > 1)
                    {
                        return false;
                    }
                } 
            }
        }
        
        return true;
    }
};
```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


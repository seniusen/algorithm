/*

题目：
给定一个 n*m 的矩阵 A ，矩阵中每一个元素为一个十六进制数。
寻找一条从左上角都右下角的路径，每次只能向右或者向下移动，
使得路径上所有数字之积在 16 进制下的后缀 0 最少。

输入描述：
    第一行：n, m(2 <= n,m <= 1000)
    接下来 n 行，每行 m 个 16 进制整数 0 <= a_ij <= 10^9

输出描述：
    第一行：最少后缀 0 的个数(十进制)
    第二行：路径方案，从左上角开始，">" 代表向右移动，"V" 代表向下移动。
    如果有多种方案，输出字典序最小的方案(">" 的字典序小于 "V")。

示例：
输入
    3 3
    3 2 8
    c 8 8
    2 a f
输出
    1
    >>VV
说明
    从左上角到右下角的所有路径中， 0x3 * 0x2 * 0x8 * 0x8 * 0xf =  0x1680
    后缀 0 最少为 1， 且路径 “>>VV” 的字典序最小。

*/

/*思路：

动态规划求得每一个位置处的乘积，使得每一个位置处的乘积十六进制末尾零最少，
并保留是怎样从前一步到当前位置的。若向下或者向右一致，则倒序求出字典序，
选择字典序小的移动方向。

*/


#include <iostream>
#include <vector>
using namespace std;

int find_zero_num(int number);
int min_dictionary(int *direction, int i, int j, int col);
void find_route(int *direction, vector<int> &route, int m, int n, int col);

enum {RIGHT = 0, DOWN = 1}; //向下走为 1 ，向右走为 0

int main()
{
    int n = 0, m = 0;
    cin >> n >> m;

    int data[n][m];           //保存矩阵中的数据
    long int product[n][m];  //保存从左上角到位置(i, j)处的乘积
    int direction[n][m] = {0};
    //保存位置(i, j)处的乘积是怎么得到的，1为从前一位置往下，0为从前一位置往右

    vector<int> route; //倒序保存路径

    int i = 0, j = 0;

    for(i = 0; i < n ; i++)
    {
        for(j = 0; j < m; j++)
        {
            cin >> hex >> data[i][j];
        }
    }

    // 初始化第一列的乘积作为边界值
    product[0][0] = data[0][0];
    for(i = 1; i < n; i++)
    {
        product[i][0] = product[i-1][0] * data[i][0];
        direction[i][0] = DOWN;
    }

    // 初始化第一行的乘积作为边界值
    for(j = 1; j < m; j++)
    {
        product[0][j] = product[0][j-1] * data[0][j];
        direction[0][j] = RIGHT;
    }

    long int down = 0;
    long int right = 0;
    int flag = 0;

    for(i = 1; i < n; i++)
    {
        for (j = 1; j < m; j++)
        {
            down = product[i-1][j] * data[i][j]; //往下走的乘积
            right = product[i][j-1] * data[i][j]; //往右走的乘积

            if (find_zero_num(down) < find_zero_num(right))
            {
                flag = 1;
            }
            else if (find_zero_num(down) > find_zero_num(right))
            {
                flag = RIGHT;
            }
            else            //若向下和向右一样，则优先取字典序小的
            {
                if(min_dictionary(*direction, i, j, m))
                {
                    flag = DOWN;
                }
                else
                {
                    flag = RIGHT;
                }
            }

            if(!flag)
            {
                product[i][j] = right;
                direction[i][j] = RIGHT;
            }
            else
            {
                product[i][j] = down;
                direction[i][j] = DOWN;
            }
        }
    }

    cout << find_zero_num(product[n-1][m-1]) << endl;

    find_route(*direction, route, n-1, m-1, m);

    for(i = int(route.size()-1); i >= 0; i--)
    {
        if (route[i])
        {
            cout << 'V';
        }
        else
        {
            cout << '>';
        }
    }

    cout << endl;
    for(i = 0; i < n ; i++)
    {
        for(j = 0; j < m; j++)
        {
            cout << hex << product[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    for(i = 0; i < n ; i++)
    {
        for(j = 0; j < m; j++)
        {
            cout << find_zero_num(product[i][j]) << " ";
        }
        cout << endl;
    }

    cout << endl;

    for(i = 0; i < n ; i++)
    {
        for(j = 0; j < m; j++)
        {
            cout << direction[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

// find the zero number of a hex data
int find_zero_num(int number)
{
    int sum = 0;
    if(number == 0)
    {
        sum = 1;
    }
    while (number % 16 == 0 && number >= 16)
    {
        sum++;
        number = number / 16;
    }
    return sum;
}

int min_dictionary(int *direction, int i, int j, int col)
{
    vector<int> route_down;
    vector<int> route_right;


    int m = i - 1;
    int n = j;
    find_route(direction, route_down, m, n, col); //向上回溯路线

    m = i;
    n = j - 1;
    find_route(direction, route_right, m, n, col); //向左回溯路线


    int length = int(route_right.size());

    for (i = length - 1; i >= 0; i--) //从第一个不相等的位置处开始判断字典序
    {
        if (route_right[i] < route_down[i])
        {
            return 0; //向右字典序小
        }
        if (route_right[i] > route_down[i])
        {
            return 1; //向下字典序小
        }
    }

    return -1;
}

// 从位置 (m, n) 处回溯路线，倒序保存在向量中
void find_route(int *direction, vector<int> &route, int m, int n, int col)
{
    while(1)
    {
        // 此位置乘积由上一位置向下移动得来，行数减一继续寻找
        if(direction[m * col + n] == 1)
        {
            m = m - 1;
            route.push_back(1);
        }
        // 此位置乘积由上一位置向右移动得来，列数减一继续寻找
        else
        {
            n = n - 1;
            route.push_back(0);
        }

        // 寻找至左上角，结束
        if (m == 0 && n == 0)
        {
            break;
        }
    }
}

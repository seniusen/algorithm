/*

题目：
给 n 个正整数 a_1,...,a_n， 将 n 个数顺序排成一列后分割成 m 段，每
一段的分数被记为这段内所有数的和，该次分割的分数被记为 m 段分数的最大值。
问所有分割方案中分割分数的最小值是多少？

输入描述：
    第一行依次给出正整数 n, m。
    第二行依次给出n 个正整数 a_1,...,a_n。

示例：
输入
    5 3
    1 4 2 3 5
输出
    5
说明
    分割成 1 4 | 2 3 | 5 的时候三段的分数都为 5，得到分割分数的最小值。

备注：
    对于所有的数据，有 m<=n<=100000,0<=a_1<=2^39。

*/

/*思路：

将 n 个数划分为 n 段，分割分数即为 n 个正整数的最大值；
将 n 个数划分为 m 段，分割分数即为 n 个正整数的和；
若分为 m 段，则分割分数一定介于最大值与和之间。
因此采用二分查找，每次取一个值对序列进行划分，若能划分出
m 段，使得每段的和都小于这个数值，则满足划分，反之不满足，
直至找到一个最小的满足划分的值为止。

*/
/*#include <iostream>
using namespace std;

int Judge(int data[], int sum, int m, int n);
int Binary_Search(int data[], int left, int right, int m, int n);


int main()
{
    int n = 0, m = 0;
    cin >> n >> m;

    int data[n];
    int max_num = 0;
    int sum = 0;

    int i = 0;

    for(i = 0; i < n ; i++)
    {
        cin >> data[i];
        if (data[i] > max_num)
        {
            max_num = data[i];
        }
        sum += data[i];
    }

    cout << Binary_Search(data, max_num, sum, m, n);

    return 0;
}

int Binary_Search(int data[], int left, int right, int m, int n)
{
    int mid = 0;

    while (left < right)
    {
        mid = left + (right - left) / 2;
        if (Judge(data, mid, m, n)) //满足划分，继续向左寻找
        {
            right = mid;//不减是因为无法确保减一之后的数是否满足划分
        }
        else    //不满足划分，继续向右寻找
        {
            left = mid + 1;
        }
    }

    return left;
}

int Judge(int data[], int mid, int m, int n)
{
    int cnt = 0;
    int sum = 0;

    for (int i = 0; i < n; i++)
    {
        if (sum + data[i] > mid) //累加和大于 mid，进行一次划分
        {
            sum = data[i];
            cnt++;
            if (cnt > m - 1)    //划分次数大于 m-1,不满足划分
            {
                return 0;
            }
        }
        else
        {
            sum += data[i];
        }
    }

    return 1;
}*/

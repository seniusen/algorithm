/*

题目：
给出一个长度为 n 的数组a_1、a_2、...、a_n，请找出在所有连续区间
中，区间和最大同时这个区间 0 的个数小于等于 3 个，输出这个区间和。

输入描述：
    第一行一个正整数 n, 表示数组长度，1 <= n <= 1000000。
    第二行 n 个正整数，a_1 a_2 ... a_n，其中 -1e9 <= a_1、a_2、...、a_n <= 1e9

输出描述：
    一个整数

示例1：
输入
    5
    1 2 3 4 5
输出
    15

示例2：
输入
    6
    15 0 0 0 0 20
输出
    20

*/

/*思路：

此问题为最大连续区间和的扩展，多增加了一个区间内 0 的个数不超过 3 的限制。
可以利用动态规划或者最简单的线性方法先解决最大区间和问题，再附加一个判断即可。

*/

#include <iostream>
using namespace std;

int MaxSubArray(int nums[], int n);

int main()
{
    int n = 0;
    cin >> n;

    int num[n];
    for(int i = 0; i < n ; i++)
    {
        cin >> num[i];
    }

    cout << MaxSubArray(num, n);

}

int MaxSubArray(int num[], int n)
{
    int i = 0, sum = 0, max_sum = 0;
    int temp_sum[4] = {0};
    int temp = 0;
    int zero_num = 0;
    for(i = 0; i < n; i++)
    {
        sum += num[i];
        /* 累加求和，只要和非负，就不会使得再相加的和变小，也就是对和的增加有贡献，就可以继续累加 */
        if(num[i] == 0)
        {
            zero_num++;
            temp_sum[zero_num-1] = sum;
            /*保存每次遇到 0 时的区间和*/
        }

        /* 增加一个对区间内 0 个数的判断 */
        if(sum > max_sum && zero_num <= 3)
        {
            max_sum = sum;
        }

        /*和为负，清零，重新开始*/
        if(sum < 0)
        {
            sum = 0;
            zero_num = 0;
            temp_sum[0] = 0;
            temp_sum[1] = 0;
            temp_sum[2] = 0;
            temp_sum[3] = 0;
        }

        /*遇到第四个 0 时对区间和进行更新，以第一个 0 后的数作为起点重新开始*/
        if(zero_num > 3)
        {
            zero_num -= 1;
            sum = sum - temp_sum[0];
            temp = temp_sum[0];
            temp_sum[0] = temp_sum[1] - temp;
            temp_sum[1] = temp_sum[2] - temp;
            temp_sum[2] = temp_sum[3] - temp;
            temp_sum[3] = sum;
        }
    }

    cout << temp_sum[0] << endl;
    cout << temp_sum[1] << endl;
    cout << temp_sum[2] << endl;
    cout << temp_sum[3] << endl;

    return max_sum;
}

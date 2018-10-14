/*

给 n 个实数 a_1,a_2 ... a_n, 要求计算这 n 个数两两
之间差的绝对值下取整后的和是多少。

输入描述

第一行为一个正整数 n 和一个整数 m。接下来 n 行，第 i 行
代表一个整数 b_i。a_i = b_i / m, i = 1...n。

n <= 1000:5分
n <= 100000且 a_i 均为整数:15分
n <= 100000 1 <= m <= 10^9 0 <= b_i <= 10^18:25分

输出描述

一个整数

示例1

输入

3 10
11
22
30

输出

2

备注：
请选手在解题时注意精度问题

a_i 取值为 1.1，2.2 和 3.0

|1.1-2.2| 下取整为 1
|1.1-3.0| 下取整为 1
|2.2-3.0| 下取整为 0

*/

// int 4 字节，long 8 字节
#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;

void Quick_Sort(long data[], double frac[], int left, int right);
void Merge_Array(double data[], int left, int mid, int right, double temp[]);
void Merge_Sort(double data[], int left, int right, double sorted_data[]);

int cnt = 0; // 逆序对数

int main()
{
    int n = 0, m = 0;
    cin >> n >> m;

    long b[n] = {0};
    long inte[n] = {0}; // a_i 的整数部分
    double frac[n] = {0}; // a_i 的小数部分
    int i = 0;

    double data[n] = {0};
    for (i = 0; i < n; i++)
    {
        cin >> b[i];
        data[i] = double(b[i]) / m;
    }

	// 暴力求解
    long sum1 = 0;
    int j = 0;
    for (i = 0; i < n-1; i++)
    {
        for (j = i+1; j < n; j++)
        {
            sum1 += floor(fabs(data[i] - data[j]));
        }
    }
    cout << sum1 << endl;


	//  分别求出整数部分和小数部分
    for (i = 0; i < n; i++)
    {
        inte[i] = b[i] / m;
        frac[i] = double(b[i]) / m - inte[i];
    }

	// 整数部分升序排列，小数部分随整数部分同步调整
    Quick_Sort(inte, frac, 0, n-1);

	// 相邻区间差乘以系数求总和
    int error[n-1] = {0};
    long sum = 0;
    for (i = 0; i < n-1; i++)
    {
        error[i] = abs(inte[i] - inte[i+1]);
        sum += (i+1) * (n-i-1) * error[i];
    }

	// 归并排序的同时求得小数部分逆序对数
    double sorted_data[n] = {0};
    Merge_Sort(frac, 0, n-1, sorted_data);

    sum -= cnt;
    cout << sum << endl;
    return 0;
}

void Quick_Sort(long data[], double frac[], int left, int right)
{
    if (left < right)
    {
        int i = left, j = right;
        long choice = data[i];
        double temp = frac[i];
        while(i < j)
        {
            while(i < j && data[j] >= choice)
            {
                j--;
            }
            if(i < j)
            {// 小数部分随整数部分同步调整
                data[i] = data[j];
                frac[i] = frac[j];
                i++;
            }
            while(i < j && data[i] <= choice)
            {
                i++;
            }
            if(i < j)
            {// 小数部分随整数部分同步调整
                data[j] = data[i];
                frac[j] = frac[i];
                j--;
            }
        }
        data[i] = choice;//i=j 小数部分随整数部分同步调整
        frac[i] = temp;//i=j
        Quick_Sort(data, frac, left, i-1);
        Quick_Sort(data, frac, i+1, right);
    }
}

// O(n(logn))
void Merge_Sort(double data[], int left, int right, double sorted_data[])
{
    if(left < right)
    {
        int mid = (left + right) / 2;
        Merge_Sort(data, left, mid, sorted_data);
        Merge_Sort(data, mid+1, right, sorted_data);
        Merge_Array(data, left, mid, right, sorted_data);
    }
}

void Merge_Array(double data[], int left, int mid, int right, double temp[])
{
    int i = left, j = mid + 1;
    int k = 0;

    while(i <= mid && j <= right)
    {
        if (data[i] < data[j] || fabs(data[i] - data[j]) <= 1e-9)
        {
            temp[k++] = data[i++];
        }
        else // 左边序列某个数大于右边某个数，则左边序列此数后面的数均大于右边的数
        {
            temp[k++] = data[j++];
            cnt += mid - i + 1;
        }
    }

    while(i <= mid)
    {
        temp[k++] = data[i++];
    }
    while(j <= right)
    {
        temp[k++] = data[j++];
    }

    for(i = 0; i < k; i++)
    {
        data[left+i] = temp[i];
    }
}

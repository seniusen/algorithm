/*

找出一个无序序列中在某个数后面第一个比它大的数

6 3 1 5 4 2 6
   5 5 6 6 6

10 2 4 5 8 9  7  10 6  64 1
    4 5 8 9 10 10 64 64 0

10 6 3 2 7 1 0 9  8  5  10
     7 7 7 9 9 9 10 10 10

*/

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n = 0;
    cin >> n;

    int data[n] = {0};
    int result[n-1] = {0};
    int i = 0;
    for(i = 0; i < n; i++)
    {
        cin >> data[i];
    }

    vector<int> num; //作为栈保存数据
    vector<int> index; //保存栈中数据在原始序列中的位置

    i = 0; // 初始化为 0，向栈压入第一个数据
    while (1)
    {
        if (int(num.size()) == 0)
        {
            // 栈为空，并且比较到最后一个数据，循环结束
            if (i == n-1)
            {
                cout << "exit2" << endl;
                break;
            }
            // 栈为空，压入新的数据
            num.push_back(data[i]);
            index.push_back(i);
            i++;
        }

        // 每次拿当前数据与栈顶元素比较，
        // 若当前数据小于等于栈顶数据，继续压栈
        int len = int(num.size() - 1);
        while (num[len] >= data[i])
        {
            // 比较到最后一个数据仍然比栈顶小，大循环结束
            if (i == n - 1)
            {
                cout << "exit1" << endl;
                goto END;
            }
            num.push_back(data[i]);
            index.push_back(i);
            i++;
            len = int(num.size() - 1);
        }

        // 若当前数据大于栈顶数据，当前数据即为栈顶数据后面
        // 第一个比它大的数，然后弹出栈顶数据，进行下一轮比较
        result[index[len]] = data[i];
        num.pop_back();
        index.pop_back();
    }

END:for(i = 0; i < n-1; i++)
    {
        cout << result[i] << " ";
    }

    return 0;
}

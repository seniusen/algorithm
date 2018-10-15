### 1. 栈的特点？

- 栈是一种先进后出的数据结构。类似于我们日常放盘子，每次放的时候只能放在最上面，而取的时候也只能依次从最上面取。

![栈](https://upload-images.jianshu.io/upload_images/11895466-ab3eaa6b7904a71c.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


- 栈可以用数组或者链表实现，用数组实现的栈叫作**顺序栈**，用链表实现的栈叫作**链式栈**。

- C++ 实现简易顺序栈。首先，定义一个固定长度的数组，然后用数组的索引值表征栈顶位置，压栈则索引值增 1，出栈则索引值减 1。

```c++
class ArrayStack
{
    private:
        int *data;      // 顺序栈
        int num;        // 栈中元素个数
        int len;        // 栈的大小

    public:
        // 初始化栈，申请一个大小为 n 的数组
        ArrayStack(int n)
        {
            data = new int[n];
            num = 0;
            len = n;
        }

        bool push(int item)
        {
            // 栈空间已满，返回 false，入栈失败
            if (num == len)
            {
                return false;
            }
            // 栈空间未满，压栈，栈中元素个数加 1
            else
            {
                data[num] = item;
                num++;
                return true;
            }
        }

        int pop()
        {
            // 栈为空，返回 -1，出栈失败
            if (num == 0)
            {
                return -1;
            }
            // 栈非空，弹出栈顶元素，栈中元素个数减 1
            else
            {
                int item = data[num-1];
                num--;
                return item;
            }
        }
};
```

- C++ 实现简易链式栈。首先，定义一个链表，压栈则在头结点后插入一个新结点，出栈则从链表中删除头结点后的第一个结点。 

```
// 单向链表
struct linked_list
{
    int data;
    linked_list *next;
};

class ListStack
{
    private:
        linked_list *head;  // 链表栈的头指针
        int num;            // 栈中元素个数

    public:
        // 初始化栈，增加一个哨兵结点，方便链表操作
        ListStack()
        {
            head = new linked_list;
            head->data = -1;
            head->next = NULL;
            num = 0;
        }

        // 压栈，在哨兵结点后插入新结点
        bool push(int item)
        {
            linked_list *node = new linked_list;
            if (node)
            {
                node->data = item;
                node->next = head->next;
                head->next = node;
                num++;
                return true;
            }
            else // 内存不足，无法插入新结点，返回 false
            {
                return false;
            }
        }

        int pop()
        {
            // 栈为空，返回 -1，出栈失败
            if (num == 0)
            {
                return -1;
            }
            // 出栈，弹出哨结点后第一个结点的值，并删除结点
            else
            {
                int item = head->next->data;
                num--;
                linked_list * node = head->next;
                head->next = node->next;
                delete node;
                return item;
            }
        }
};
```

### 2. 栈的应用？

- **函数调用**。在函数调用时，栈先会保存函数的返回地址、参数和一些局部变量，来保证调用结束后，程序还能回到上一次程序运行的位置继续正常运行。

- **表达式求值**。在进行算术表达式运算时，编译器是通过两个栈来实现的，其中一个保存操作数，另一个保存运算符。计算时，遇到操作数则直接压栈。遇到运算符则与栈顶运算符进行比较，若当前运算符优先级高于栈顶运算符优先级，则将运算符压栈；若当前运算符优先级低于或者等于栈顶运算符优先级，则从运算符栈取出运算符，从操作数栈取出栈顶的两个元素进行运算，将结果压入操作数栈，继续比较。

![表达式求值](https://upload-images.jianshu.io/upload_images/11895466-9a591140ed2dfa63.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


- **括号匹配**。从左到右对表达式中的括号进行扫描，遇到左括号则压入栈中，当扫描到右括号时，从栈顶取出一个元素。如果二者匹配，继续扫描剩下的字符串；如果不匹配或者栈中没有数据，则说明有非法格式存在。

### 3. 如何实现浏览器的前进和后退功能？

> 我们在浏览器中访问网页时，假设依次访问了 A > B > C 页面，此时我们可以从 C 后退到 B、A，也且可以再从 A、B 前进回到 C。

- 通过两个栈 X、Y 我们就可以实现这个功能，访问网页时，我们依次把网页 A、 B 、C 压入栈 X，要后退时再依次从栈顶取出元素放入栈  Y，然后前进时就可以从栈 Y 中再取出来即可。

[参考资料-极客时间专栏《数据结构与算法之美》](https://time.geekbang.org/column/126)


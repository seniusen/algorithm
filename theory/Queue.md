### 1. 队列的特点？

- 队列是一种**先进先出**的数据结构。类似于我们日常排队购物，先到的人排在前面，自然优先被服务。栈有出栈和入栈两个基本操作，队列也只有两个基本操作，从队尾入队 enqueue，从队头出队 dequene。
![队列和栈](https://upload-images.jianshu.io/upload_images/11895466-58fd09520f19e339.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


- 队列可以用数组或者链表实现，用数组实现的队列叫作**顺序队列**，用链表实现的队列叫作**链式队列**。

### 2. 顺序队列？

- C++ 实现简易顺序队列。首先，定义一个固定长度的数组，然后用两个数组的索引值分别表征队列的队头和队尾，入队则队尾索引值增 1，出队则队头索引值增 1。

![顺序队列](https://upload-images.jianshu.io/upload_images/11895466-a40c01fba424fde2.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 有一种特殊情况，队尾元素一直进队到达了数组上限，但前面有元素出队，这时候，队列其实还有存储空间没有利用，我们就将队列的数据都往前平移，腾出一些空间来。

![数据搬移](https://upload-images.jianshu.io/upload_images/11895466-6a50b876cb91ab95.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


```c++
class ArrayQueue
{
    private:
        int *data;      // 顺序队列
        int head;       // 队列头索引值
        int tail;       // 队列尾索引值
        int len;        // 队列的大小

    public:
        // 初始化队列，申请一个大小为 n 的数组
        ArrayQueue(int n)
        {
            data = new int[n];
            head = 0;
            tail = 0;
            len = n;
        }

        bool enqueue(int item)
        {
            // 队列头索引值为零且队列尾索引值等于数组长度，队列空间已满，返回 false，入队失败
            if (tail == len && head == 0)
            {
                cout << "queue is full" << endl;
                return false;
            }
            else
            {// 若只有队列尾索引值等于数组长度，向前平移数据
                if (tail == len && head != 0)
                {
                    int num = tail - head;

                    for (int i = 0; i < num; i++)
                    {
                        data[i] = data[len - num + i];
                    }

                    head = 0;
                    tail = num;
                }

                // 队列空间未满，入队，队列尾索引值加 1

                data[tail] = item;
                tail++;
                return true;
            }
        }

        int dequeue()
        {
            // 队列头等于队列尾，队列为空，返回 -1，出队失败
            if (head == tail)
            {
                cout << "queue is empty" << endl;
                return -1;
            }
            // 队列非空，队头元素出队，队列头索引值加 1
            else
            {
                int item = data[head];
                head++;
                return item;
            }
        }
};
```
### 2. 链式队列？


- C++ 实现简易链式队列。定义头指针指向哨兵结点，尾指针指向最后一个结点，入队则在链尾插入一个新结点，出队则删除哨兵结点后的第一个结点。 

![ 链式队列](https://upload-images.jianshu.io/upload_images/11895466-0e24e54af9bb365c.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


```
// 单向链表
struct linked_list
{
    int data;
    linked_list *next;
};

class ListQueue
{
    private:
        linked_list *head;  // 链表队列的头指针
        linked_list *tail;  // 链表队列的尾指针
        int num;            // 队列中元素个数

    public:
        // 初始化队列，增加一个哨兵结点，方便链表操作
        ListQueue()
        {
            head = new linked_list;
            head->data = -1;
            head->next = NULL;
            tail = head; // 头指针和尾指针都指向哨兵
            num = 0;
        }

        // 入队，在链尾插入新结点
        bool enqueue(int item)
        {
            linked_list *node = new linked_list;
            if (node)
            {
                node->data = item;
                node->next = NULL;
                tail->next = node;  // 添加新结点
                tail = node; // 更新尾指针
                num++;
                return true;
            }
            else // 内存不足，无法插入新结点，返回 false
            {
                return false;
            }
        }

        int dequeue()
        {
            // 队列为空，返回 -1，出队失败
            //if (num == 0)
            if (head == tail)
            {
                cout << "queue is empty" << endl;
                return -1;
            }
            // 出队，弹出哨兵结点后第一个结点的值，并删除结点
            else
            {
                if (head->next == tail) // 当队列只有一个结点时，需要更改尾节点指向哨兵
                {
                    tail = head;
                }

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

### 4. 循环队列？

- 用数组来实现队列，当队尾到达数组上限时，我们需要进行数据搬移来利用实际上处于空闲的内存空间，但这样入队操作的性能就会受到影响。
-  为了避免进行数据搬移，我们引入循环队列来解决这个问题。

![循环队列](https://upload-images.jianshu.io/upload_images/11895466-aef1943c615dc642.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 循环队列实质上就是将数组首尾相连组成一个环，当队尾到达数组上限但数组头还有空间时，我们就可以继续沿着数组头继续进队。

- 实现循环队列的关键就是确定队列空和队列满的条件。类似顺序队列，当 head = tail 时，队列为空；当 (head+1) % len = head 时，队列为满。而且，当队列满时， **tail 指向的位置是没有数据的**。

![队列满](https://upload-images.jianshu.io/upload_images/11895466-70eb3edccafe36eb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```
class CircularQueue
{
    private:
        int *data;      // 顺序队列
        int head;       // 队列头索引值
        int tail;       // 队列尾索引值
        int len;        // 队列的大小

    public:
        // 初始化队列，申请一个大小为 n 的数组
        CircularQueue(int n)
        {
            data = new int[n];
            head = 0;
            tail = 0;
            len = n;
        }

        bool enqueue(int item)
        {
            // 队列空间已满，返回 false，入队失败
            if ((tail + 1) % len == head)
            {
                cout << "queue is full" << endl;
                return false;
            }
            else
            {
                // 队列空间未满，入队，队列尾索引值加 1
                data[tail] = item;
                tail++;
                // 到达数组上限，索引值循环到 0
                if (tail == len)
                {
                    tail = 0;
                }
                return true;
            }
        }

        int dequeue()
        {
            // 队列头等于队列尾，队列为空，返回 -1，出队失败
            if (head == tail)
            {
                cout << "queue is empty" << endl;
                return -1;
            }
            // 队列非空，队头元素出队，队列头索引值加 1
            else
            {
                int item = data[head];
                head++;

                // 到达数组上限，索引值循环到 0
                if (head == len)
                {
                    head = 0;
                }
                return item;
            }
        }

        void print()
        {
            cout << head << " " << tail << endl;
        }
};
```

### 3. 阻塞队列和并发队列？

- 阻塞队列就是在队列基础上增加了阻塞操作。队列为空时，出队操作会被阻塞，直到队列中有了数据才能返回；队列满时，入队操作会被阻塞，直到队列中有空闲位置时才能插入新数据。

![阻塞队列](https://upload-images.jianshu.io/upload_images/11895466-93ab443c0c7bfa04.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 使用阻塞队列，我们可以轻松实现一个“生产者 - 消费者“模型。此外，我们还可以通过协调”生产者“和”消费者“的数量，来提高数据的处理效率。

![生产者消费者模型](https://upload-images.jianshu.io/upload_images/11895466-651e8c8d7e68ff22.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 在多线程情况下，会有多个线程同时操作队列，要想实现一个**线程安全的队列，我么就需要一个并发队列**。一种是在 enqueue、dequeue方法中加锁，同一时刻只允许一个存或取操作；另一种则是基于循环队列，利用 CAS 原子操作，可以实现非常高效的并发队列。

### 3. 队列在线程池等有限资源池中的应用？

> 线程池中没有空闲线程时，新的任务请求线程资源时，线程池该如何处理？各种处理策略又是如何实现的呢？

- 一般有两种策略。**非阻塞**的处理方式直接拒绝任务请求；**阻塞**的处理将请求进行排队，等到有空闲线程时，取出请求进行处理。

- 基于链表，可以实现**支持无限排队的无界队列(unbounded queue)**，但是可能会导致过多的请求排队，会导致请求的响应时间过长。而基于数组的**有界队列(bounded queue)**，队列大小有限，超出的请求就会被拒绝。


[参考资料-极客时间专栏《数据结构与算法之美》](https://time.geekbang.org/column/126)

#### 1. 题目
> 给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。

>示例：
给定一个链表: 1->2->3->4->5, 和 n = 2.
当删除了倒数第二个节点后，链表变为 1->2->3->5.

>说明：
给定的 n 保证是有效的。

>进阶：
你能尝试使用一趟扫描实现吗？

#### 2. 思路

- 定义两个指针 p1、p2，刚开始两个指针都指向头结点。如果要删除倒数第 N 个结点，我们就让 p2 **先前进 N-1 步**，这时候 p2 后面的节点个数为 K，**那我们要删除的结点也就是位于 p1 后面的第 K 个结点**。

- 如下图所示，假设我们要删除倒数第 3 个结点，p2 前进 2 步后指向第三个结点。

![1.png](https://upload-images.jianshu.io/upload_images/11895466-bbce27594664dce5.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- p2 后面还有 1 个结点，而我们要删除的结点也就是位于 p1 后面的第 1 个结点——结点 2。

![2.png](https://upload-images.jianshu.io/upload_images/11895466-b3530ef8e025c0e1.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 一种特殊情况是要删除倒数第 4 个结点，也就是第 1 个结点。这时候，我们只需要让 head 指向第 2 个结点即可。

![3.png](https://upload-images.jianshu.io/upload_images/11895466-ae0fcee73691a767.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 其他情况下，在 p2 指针到达指定位置后。我们**先让  p2 指针后移一个位置**，然后再同时让 p1 和 p2 向后移动。**当 p2 指向最后一个结点时，p1 就指向了待删除节点的前一个结点**，此时让 p1 指向 p1 后面的第 2 个结点即可删除指定的结点。

- 以下为删除倒数第 1 个结点的过程。

![4.png](https://upload-images.jianshu.io/upload_images/11895466-bb0b30fbc4056431.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![5.png](https://upload-images.jianshu.io/upload_images/11895466-b6db092cc158c8d3.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


- 当然，**不要忘了释放删除结点的内存**。
- 代码如下

```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        
        if (head == NULL)
        {
            return head;
        }

        else
        {
            int i = 1;
            ListNode *p1 = head, *p2 = head, *temp = NULL;
            
            while (i != n) // p2 指针前进 n-1 步
            {
                i++;
                p2 = p2->next;
            }
            
            if (p2->next == NULL) // 删除第一个结点的情况
            {
                temp = head;
                head = head->next; // head 指向第 2 个结点
            }
            else
            {
                p2 = p2->next; // p2 指针先前进 1 步
            
                while(p2->next)  // p1、p2 指针同步向后移动
                {
                    p2 = p2->next;
                    p1 = p1->next;
                }

                temp = p1->next;
                p1->next = p1->next->next; // p1 指向其后面的第 2 个结点
            }
            
            delete(temp); // 释放结点内存
            
        }   
            
        return head;
            
    }
        
};

```

获取更多精彩，请关注「seniusen」! 
![seniusen](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

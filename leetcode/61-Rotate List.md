### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-050734e4eb123db9.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


### 2. 解答
#### 2.1. 方法一

将链表每个节点向右移动 1 个位置，其实就是让链表最后一个结点指向第一个结点。

因此，向右移动 k 个位置就重复上述过程 k 次即可。

然后，我们注意到，若链表有 n 个结点，则移动 n 次后就还是原链表。
```
原始链表 1->2->3->NULL
向右旋转 1 步: 3->1->2->NULL
向右旋转 2 步: 2->3->1->NULL
向右旋转 3 步: 1->2->3->NULL
```
实际上，若链表有 n 个结点，我们只需要移动 n % k 次即可。

确定链表有多少个结点，我们则可以用快慢指针法。

![](https://upload-images.jianshu.io/upload_images/11895466-19c26f31067cb408.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 偶数个结点时，结点个数等于 i * 2。

![](https://upload-images.jianshu.io/upload_images/11895466-8ee3230422213edf.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 奇数个结点时，结点个数等于 i * 2 + 1。

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
    ListNode* rotateRight(ListNode* head, int k) {
        
        if (head == NULL || head->next == NULL) return head;
        
        int node_num = 0; // 链表的结点个数
        ListNode* slow = head;
        ListNode* fast = head;

        // 利用快慢指针确定链表的结点总个数
        while(fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            node_num++;
        }

        if (fast) // 奇数个结点
        {
            node_num = node_num * 2 + 1;
        }
        else // 偶数个结点
        {
            node_num = node_num * 2;
        }
        
        // 若链表有 K 个结点，向右移动 K 个位置就还是原链表
        // 因此我们只需要移动 K % node_num 次即可
        if (k % node_num == 0) return head;
        else k = k % node_num;
        
        ListNode *temp = head;
        ListNode *last_node = NULL;

        for (int i = 0; i < k; i++)
        {
            // 向右移动 1 个位置就是让最后一个结点指向第一个结点
            
            // 先找到倒数第二个结点
            while (temp->next->next)
            {
                temp = temp->next;
            }

            // 最后一个结点指向第一个结点，倒数第二个节点指向 NULL
            last_node = temp->next;
            temp->next = NULL;
            last_node->next = head;
            
            head = last_node;
            temp = head;
        }
        
        return head;
    }
};
```
#### 2.2. 方法二

上面的算法中每次将链表结点向右移动 1 个位置的时候，我们都要遍历一次链表，效率较低。

针对链表 1->2->3->4->5->NULL，如果要将链表每个结点向右移动 2 个位置，那倒数第 2 个结点就是旋转后新链表的起始位置；如果要将链表每个结点向右移动 3 个位置，那倒数第 3 个结点就是旋转后新链表的起始位置；而如果要将链表每个结点向右移动 33 个位置，那倒数第 3 个结点就是旋转后新链表的起始位置。

**更一般的情况下，若链表长度为 n，移动次数为 k，旋转后链表的起始位置就是原链表倒数第 k % n 个结点**。

在上面的例子中，假设新链表的起始位置是结点 4，那链表就被分成了两部分。1->2->3 和 4->5->NULL，我们要做的就是把 1->2->3 拼接在 4->5->NULL 后即可。

实现思路是这样的：
>我们先通过快慢指针确定链表长度 n，然后找到旋转后链表起始位置的上一个结点，记为 new_head_last，然后从起始位置 new_head 开始向后遍历，当到达 NULL 时，将 head 指向的头结点拼接在 new_head 后面，然后再将新链表的最后一个结点也即 new_head_last 后面置为 NULL 即可。

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
    ListNode* rotateRight(ListNode* head, int k) {
        
        if (head == NULL || head->next == NULL) return head;
        
        int node_num = 0; // 链表的结点个数
        int mid_num = 0;
        ListNode* slow = head;
        ListNode* fast = head;

        // 利用快慢指针确定链表的结点总个数
        while(fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            mid_num++;
        }

        if (fast) // 奇数个结点
        {
            node_num = mid_num * 2 + 1;
        }
        else // 偶数个结点
        {
            node_num = mid_num * 2;
        }
        
        // 若链表有 K 个结点，向右移动 K 个位置就还是原链表
        // 因此我们只需要移动 K % node_num 次即可
        if (k % node_num == 0) return head;
        else k = k % node_num;
        
        int which_node_is_new = 0; // 旋转后的头结点是第几个节点
        ListNode* new_head = NULL;
        ListNode* new_head_last = NULL;
 
        // 查找旋转后头结点的上一个结点
        // 此时 slow 指针指向中间结点，分为在 slow 前还是在 slow 后
        which_node_is_new = node_num - k; 
        if (which_node_is_new > node_num / 2)
        {
            new_head_last = slow;
            for (int i = 0; i < which_node_is_new - mid_num - 1; i++)
            {
                new_head_last = new_head_last->next;
            }
        }
        else
        {
            new_head_last = head;
            for (int i = 1; i < which_node_is_new; i++)
            {
                new_head_last = new_head_last->next;
            } 
        }

        new_head = new_head_last->next;
        ListNode* temp = new_head;
        
        while (temp->next)
        {
            temp = temp->next;
        }
        
        temp->next = head;
        new_head_last->next = NULL;
        
        return new_head;
    }
};
```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

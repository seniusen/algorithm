#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-90dc8c4e70750dbf.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 2. 解答

我们需要先找到第 m 个结点及其上一个结点，然后将从 m 到 n 的结点进行反转，最后依次将 m 到 n 反转后的结点和 n 之后的结点放入原链表中即可。

从前往后依次遍历 m-1 次即可找到第 m 个结点，然后我们开始将第 m 到第 n 个结点倒序放入一个新链表，也即每次都在新链表的头结点后面进行插入，来实现这部分子链表的反转。

最后，我们将这个反转后的子链表放入原链表，再把第 n 个结点后面的链表也放回到原链表即可。 

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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        
        if (head == NULL || head->next == NULL || m == n) return head;
        
        // 先找到第 m 个结点和其前一结点
        // 如果 m == 1，则没有 m 的前一结点，需要特殊处理
        ListNode *temp = head;
        int num = 1;
        ListNode *m_last_node = NULL;
        while (num < m) 
        {
            m_last_node = temp;
            temp = temp->next;
            num++;
        }
        ListNode *m_node = temp;
        
        // 把第 m 到 n 个结点倒序加入新链表中，反转链表
        // 即每次都在头结点之后插入结点，类似于队列，先进的在后面
        ListNode *queue = new ListNode(0);
        ListNode *reversed_node = NULL;
        while (num <= n)
        {
            reversed_node = temp;
            temp = temp->next;
            reversed_node->next = queue->next;
            queue->next = reversed_node;
            num++;
        }
        
        // 将 m 到 n 反转后的结点放入原链表中
        if (m != 1) m_last_node->next = queue->next;
        else head = queue->next;
        
        // 将 n 后面的结点放入原链表中
        m_node->next = temp;
        
        return head;
    }
};
```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-710df632139cc679.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 2. 解答

新建一个哨兵结点作为头结点，然后每次交换相邻两个结点。并依次将它们连接到新链表中去，再将原链表中后面的结点也串到新链表后面。直至到达链尾或者剩余一个节点，则此时返回新链表的头结点，也即是原始链表的第二个结点。

![](https://upload-images.jianshu.io/upload_images/11895466-db9adf326652757e.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](https://upload-images.jianshu.io/upload_images/11895466-4c2c0c4608be8f44.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

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
    ListNode* swapPairs(ListNode* head) {
        
        if (head == NULL || head->next == NULL)   return head; // 没有结点或只有一个结点
        
        ListNode *p1 = head;
        ListNode *p2 = head->next;
        ListNode *p3 = NULL;
        
        ListNode *temp = head->next; // 交换后的头结点为原链表的第二个结点
        head = new ListNode(0); // 新建哨兵结点方便操作

        while (1)
        {
            p3 = p2->next;
            
            p2->next = p1;  // 第一步，交换结点
            head->next = p2;    // 第二步，连接交换后的两个结点到新链表中
            head = p1;  // 第三步，指向新链表尾结点
            head->next = p3;    // 第四步，连接原链表后面的结点到新链表中
            
            if (p3 && p3->next)
            {
                p1 = p3;
                p2 = p1->next;
            }
            else
            {
                break;
            }    
        }
        
        return temp;
        
    }
};
```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-9b4f8d198dee5f77.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 2. 解答

从前向后遍历链表，将结点值小于 x 的结点放入到新链表 1 中，将结点值大于等于 x 的结点放入新链表 2 中。最后，将新链表 2 拼接在新链表 1 后面即可。

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
    ListNode* partition(ListNode* head, int x) {
        
        if (head == NULL || head->next == NULL) return head;
        
        ListNode *new_head1 = new ListNode(0); // 新建哨兵结点方便操作
        ListNode *temp1 = new_head1;
        
        ListNode *new_head2 = new ListNode(0); // 新建哨兵结点方便操作
        ListNode *temp2 = new_head2;
        
        while (head)
        {
            if (head->val < x) // 小于 x 的结点放入新链表 1
            {
                temp1->next = head;
                temp1 = head;
            }
            else // 大于等于 x 的结点放入新链表 2
            {
                temp2->next = head;
                temp2 = head;
            }
            
            head = head->next;
        }
        
        temp1->next = new_head2->next;
        temp2->next = NULL;
        
        return new_head1->next;   
    }
};
```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

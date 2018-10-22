#### 1. 题目

![21](https://upload-images.jianshu.io/upload_images/11895466-a3da5e3d7b46cdbb.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 2. 解答
- 新建一个带有哨兵结点的链表，依次比较两个有序链表的结点值，将较小值的结点插入到新链表后面。直到其中一个比较完毕，将另一个链表剩余的结点全部放到新链表最后面即可。最后，可以删除哨兵结点，或者直接返回哨兵结点后第一个结点指针。

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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        
        ListNode *head = new ListNode(0); // 新建哨兵结点，方便操作
        ListNode *temp = head;
        
        // 依次比较两个链表的结点值，将值较小的结点插入到新建的链表后面
        while(l1 && l2)
        {
            if (l2->val <= l1->val)
            {
                temp->next = l2;
                temp = temp->next;
                l2 = l2->next;
            }
            else
            {
                temp->next = l1;
                temp = temp->next;
                l1 = l1->next;
            }
        }
        
        // 其中一个链表比较完毕，将另外一个链表剩余结点直接插入到新建的链表后面
        if (l1)
        {
            temp->next = l1;
        }
        else
        {
            temp->next = l2;
        }
        
        temp = head;
        head = head->next;// 删除哨兵结点
        delete(temp);
        
        return head;  
    }
};
```

获取更多精彩，请关注「seniusen」! 
![seniusen](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

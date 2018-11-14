#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-4bb3be0be74405d5.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)



#### 2. 解答

新建一个链表，并添加一个哨兵结点，从前向后开始遍历链表。

- 如果下一个结点的值和当前结点的值相等，则循环向后遍历直到找到一个和当前结点值不相等的结点；

- 反之，如果下一个结点的值和当前结点的值不相等，此值即为原始链表中没有重复出现的数字，将其加入到新链表中。

然后继续向后遍历。最后，

- 如果 head 指向最后一个结点，则此最后一个结点的值也没有重复出现，将其加入到新链表中，此时新链表的尾结点无需处理；

- 如果 head 指向 NULL，我们则需要确认新链表的尾结点指向 NULL。

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
    ListNode* deleteDuplicates(ListNode* head) {
        
        if (head == NULL || head->next == NULL) return head;
        
        ListNode *new_head = new ListNode(0); // 新建哨兵结点方便操作
        ListNode *temp = new_head;
            
        while (head && head->next)
        {
            if (head->val == head->next->val)
            {
                while(head != NULL && head->next != NULL && head->val == head->next->val)
                {
                    head = head->next;
                }
                head = head->next;
            }
            else
            {
                temp->next = head;
                temp = head;
                head = head->next;
            }
        }
        
        if (head)   temp->next = head; // 原链表最后一个元素不是重复元素，添加到新链表尾
        else    temp->next = NULL; // 原链表最后一个元素是重复元素，新链表尾指向 NULL
        
        return new_head->next;
        
    }
};
```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

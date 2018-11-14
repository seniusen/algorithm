#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-e7b44311fe601435.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 2. 解答

从前向后遍历链表，如果下一个结点的值和当前结点的值相同，则删除下一个结点，否则继续向后遍历。

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
        
        ListNode *temp = head;
            
        while (temp && temp->next)
        {
            if (temp->val == temp->next->val)
            {
                temp->next = temp->next->next;
            }
            else
            {
                temp = temp->next;
            }
        }
        
        return head;
    }
};
```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

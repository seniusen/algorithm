
#### 1. 题目

![](https://user-gold-cdn.xitu.io/2018/11/8/166f1227d399268a?w=910&h=453&f=png&s=41776)

#### 2. 解答

```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def removeElements(self, head, val):
        """
        :type head: ListNode
        :type val: int
        :rtype: ListNode
        """
        
        # 如果头结点就要删除，往后移动头结点
        while head != None and head.val == val:
            head = head.next
        
        temp = head
        
        while temp != None and temp.next != None:
            
            # 如果下一个结点要被删除，看是否存在下下个结点
            if temp.next.val == val:
                if temp.next.next == None:
                    temp.next = None
                else:
                    temp.next = temp.next.next;
            
            # 如果下一个结点无需删除，继续往后遍历          
            else:
                temp = temp.next
                
        return head
```

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
    ListNode* removeElements(ListNode* head, int val) {
        
        
        while (head && head->val == val)
        {
            head = head->next;
        }
        
        ListNode* temp = head;
        
        while (temp && temp->next)
        {
            if (temp->next->val == val)
            {
                if (temp->next->next) temp->next = temp->next->next;
                else    temp->next = NULL;
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

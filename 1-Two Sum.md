#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-59eefabb29917698.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 2. 解答

循环遍历两个链表
- 若两个链表都非空，将两个链表结点的值和进位相加求出和以及新的进位

- 若其中一个链表为空，则将另一个链表结点的值和进位相加求出和以及新的进位

然后将每一位的和添加到新链表中。

如果**有一个链表为空，且此时进位为 0**，我们则只需要将非空链表后面的值复制到新链表即可，可以通过将非空链表的剩余结点直接接在新链表后面来实现。

如果最后两个链表同时为空，我们还要考虑此时是否有进位，**若有进位，进位即为最后一位的和**，然后，让链表尾结点指向 NULL 即可。

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        
        ListNode *head = new ListNode(0); // 建立哨兵结点
        ListNode *temp = head; 

        
        int carry = 0; // 保留进位
        int sum = 0;
            
        while(l1 || l2)
        {
            if (l1 && l2) // 两个链表都非空
            {
                sum = l1->val + l2->val + carry;
                l1 = l1->next;
                l2 = l2->next;
            }
            else if (l1) // l2 链表为空，只对进位和 l1 元素求和
            {
                sum = l1->val + carry;
                l1 = l1->next;
            }
            else // l1 链表为空，只对进位和 l2 元素求和
            {
                sum = l2->val + carry;
                l2 = l2->next;
            } 
            
            // 求出和以及进位，将和添加到新链表中
            carry = sum >= 10 ? 1 : 0;
            sum = sum % 10;
            head->next = new ListNode(sum);
            head = head->next;
            
            if ( (l1 == NULL || l2 == NULL) && carry == 0 )
            {
                head->next = l1 ? l1 : l2;  // 将非空链表剩余结点接在新链表后面
                return temp->next;
            }

        }
          
    
        if (carry) // 若最后一位还有进位，进位即为最后一位的和
        {
            head->next = new ListNode(carry);    
        }
        head->next->next = NULL;
        

        return temp->next;
        
    }
};
```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

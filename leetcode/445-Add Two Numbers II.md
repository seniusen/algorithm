#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-f868c3736972012a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 2. 解答

##### 2.1 方法一

在 [LeetCode 206——反转链表](https://blog.csdn.net/seniusen/article/details/83033827) 和 [LeetCode 2——两数相加](https://blog.csdn.net/seniusen/article/details/83478384) 的基础上，先对两个链表进行反转，然后求出和后再进行反转即可。

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
        
        // 先将两个链表反序
        l1 = reverseList(l1);
        l2 = reverseList(l2);
        
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
                head->next = l1 ? l1 : l2;
                return reverseList(temp->next);
            }

        }
          
    
        if (carry) // 若最后一位还有进位，进位即为最后一位的和
        {
            head->next = new ListNode(carry);    
        }
        head->next->next = NULL;
        

        return reverseList(temp->next);
        
    }
    
    ListNode* reverseList(ListNode* head) {
    
        if (head == NULL || head->next == NULL) return head; 
        else 
        { 
            ListNode * p1 = head; 
            ListNode * p2 = p1->next; 
            ListNode * p3 = p2->next; 
            
            while (p2) 
            { 
                p3 = p2->next; p2->next = p1; 
                p1 = p2; 
                p2 = p3; 
            } 
            head->next = NULL; 
            head = p1; 

            return head; 
        }

    }

};
```
##### 2.2 方法二

先求出两个链表的长度，然后对齐两个链表，按照对应位分别求出每一位的和以及进位，最后从最低位也就是最右边开始，将和与进位相加，新建节点在链表头部插入即可。

| 例 1 |  |  |  |  |
|  :------: |  :------:| :------: | :------: | :------: |
|l1 |7| 2 | 4 |3 |
|l2 |  | 5 | 6 | 4|
| 和 | 7 | 7 | 0 | 7|
| 进位| 0 | 1 |0 |0 |
| 结果| 7 | 8 |0 |7 |

| 例 2 |  |  |  |  |
|  :------: |  :------:| :------: | :------: | :------: |
|l1 || 9 | 9 |9 |
|l2 |  |  | 9 | 9|
| 和 | 0 | 9 | 8 | 8|
| 进位| 0 | 1 |1 |0 |
| 结果| 1 | 0 |9 |8 |

```c
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        
        int n1 = countListNodeNumber(l1);
        int n2 = countListNodeNumber(l2);
        
        ListNode* long_list = NULL;
        ListNode* short_list = NULL;
        int bigger_n = 0;
        int smaller_n = 0;
        
        if (n1 <= n2)
        {
            long_list = l2;
            short_list = l1;
            bigger_n = n2;
            smaller_n = n1;
        }
        else
        {
            long_list = l1;
            short_list = l2;
            bigger_n = n1;
            smaller_n = n2;   
        }
        int temp = bigger_n - smaller_n + 1;
        int sum_array[bigger_n + 1] = {0};
        int carry_array[bigger_n + 1] = {0};
        int sum = 0;
        int carry = 0;
        
        ListNode* long_temp = long_list;
        ListNode* short_temp = short_list;
        
        for (unsigned int i = 1; i <= bigger_n; i++)
        {
            carry = 0;
            if (i < temp)
            {
                sum = long_temp->val;
            }
            else
            {
                sum = long_temp->val + short_temp->val;
                if (sum >= 10)
                {
                    sum = sum % 10;
                    carry = 1;
                }
                short_temp = short_temp->next;
            }
            sum_array[i] = sum;
            carry_array[i-1] = carry;
            long_temp = long_temp->next;
        }
        
               
        ListNode* new_head = new ListNode(0);
        long_temp = new_head;
        
        for (unsigned int i = bigger_n; i > 0; i--)
        {
            // 在链表头部进行插入
            sum = sum_array[i] + carry_array[i];
            if (sum >= 10)
            {
                sum = sum % 10;
                carry_array[i-1] = 1;
            }
            short_temp = new ListNode(sum);
            short_temp->next = long_temp->next;
            long_temp->next = short_temp;
        }
        
        sum = sum_array[0] + carry_array[0];
        if (sum)
        {
            short_temp = new ListNode(sum);
            short_temp->next = long_temp->next;
            long_temp->next = short_temp;
        }
        
        return new_head->next;

    }
    
    int countListNodeNumber(ListNode *head)
    {
        int node_num = 0;
        ListNode* slow = head; 
        ListNode* fast = head; 
        
        while(fast && fast->next) 
        {
            slow = slow->next; 
            fast = fast->next->next; 
            node_num++; 
        } 
        
        if (fast) 
        { 
            node_num = node_num * 2 + 1;
        } 
        else 
        { 
            node_num = node_num * 2; 
        }
        
        return node_num;
    }
    
    
};
```
##### 2.3 方法三

将两个链表的节点分别放入两个栈中，若两个栈都非空，拿两个栈顶元素和进位，求出和以及新的进位；若其中一个栈为空，则拿一个栈顶元素和进位，求出和以及新的进位。然后新建节点，在链表头部进行插入，最后只用处理一下最高位的进位即可。

```c
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        
        stack<ListNode *> stack1;
        stack<ListNode *> stack2;
        
        while (l1)
        {
            stack1.push(l1);
            l1 = l1->next;
        }
        
        while (l2)
        {
            stack2.push(l2);
            l2 = l2->next;
        }
        
        int sum = 0;
        int carry = 0;
        
        ListNode *new_head = new ListNode(0);
        ListNode *temp = NULL;
        
        while (!stack1.empty() && !stack2.empty())
        {
            sum = stack1.top()->val + stack2.top()->val + carry;
            
            if (sum >= 10)
            {
                sum = sum % 10;
                carry = 1;
            }
            else
                carry = 0;
            
            temp = new ListNode(sum);
            temp->next = new_head->next;
            new_head->next = temp; 
            
            stack1.pop();
            stack2.pop();
        }
                

         while (!stack1.empty())
         {
            sum = stack1.top()->val + carry;

            if (sum >= 10)
            {
                sum = sum % 10;
                carry = 1;
            }
            else
                carry = 0;

            temp = new ListNode(sum);
            temp->next = new_head->next;
            new_head->next = temp; 

            stack1.pop();
         }
        

         while (!stack2.empty())
         {
            sum = stack2.top()->val + carry;

            if (sum >= 10)
            {
                sum = sum % 10;
                carry = 1;
            }
            else
                carry = 0;

            temp = new ListNode(sum);
            temp->next = new_head->next;
            new_head->next = temp; 

            stack2.pop();
         }
        
        if (carry)
        {
            temp = new ListNode(carry);
            temp->next = new_head->next;
            new_head->next = temp; 
        }
        
        return new_head->next;
    }   
};
```


获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

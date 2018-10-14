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
    bool isPalindrome(ListNode* head) {
        
        if (head == NULL || head->next == NULL)     // 空链或只有一个结点，返回 true
        {
            return true;            
        }
        
        else
        {
            /* 此为反转链表的三个指针，slow 即代表 p1 */
            ListNode* slow = head;           // 慢指针指向第一个结点
            ListNode * p2 = slow->next;      // 第二个结点
            ListNode * p3 = p2->next;        // 第三个结点
            
            ListNode* fast = head;           // 快指针指向头结点

            // 奇数结点快指针指向最后一个结点结束
            // 偶数结点快指针指向 NULL 结束
            while(fast && fast->next)   
            {
                p3 = p2->next;
                fast = fast->next->next;    // 快指针前进两步
                p2->next = slow;            // 反转链表
                slow = p2;                  // 慢指针前进一步
                p2 = p3;
            }

            head->next = NULL; // 处理前半部分子链的尾节点

            // 偶数结点
            if(!fast)
            {
                // 先比较 slow 后的两个结点是否相同
                if (slow->val == slow->next->val)
                {
                    // 以 slow 后的第三个结点和 p2 指向的结点开始循环向两边比较
                    slow = slow->next->next;
                    while(slow)
                    {
                        if (slow->val != p2->val)
                        {
                            return false;
                        }
                        else
                        {
                            slow = slow->next;
                            p2 = p2->next;
                        }
                    }
                    return true;
                }
                else
                {
                    return false;
                }
            }
            // 奇数结点
            else
            {
                // 以 slow 后的第一个结点和 p2 指向的结点开始循环向两边比较
                slow = slow->next;
                while(slow)
                {
                    if (slow->val != p2->val)
                    {
                        return false;
                    }
                    else
                    {
                        slow = slow->next;
                        p2 = p2->next;
                    }
                }
                return true;
            }
        }
                
    }
};

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
    ListNode* reverseList(ListNode* head) {
        
        // 迭代法       
        /*if (head == NULL || head->next == NULL)     // 空链或只有一个结点，直接返回头指针
        {
            return head;            
        }
        else                                        // 至少有两个结点
        {
            ListNode * p1 = head;                   // 第一个结点
            ListNode * p2 = p1->next;               // 第二个结点
            ListNode * p3 = p2->next;               // 第三个结点

            while (p2)                              // 第二个结点为空，到链尾，结束
            {
                p3 = p2->next;
                p2->next = p1;                      // 第二个结点指向第一个结点，进行反转
                p1 = p2;                            // 第一个结点往后移
                p2 = p3;                            // 第二个结点往后移
            }
            
            head->next = NULL;          // 第一个结点也就是反转后的最后一个节点指向 NULL
            head = p1;                  // 头结点指向反转后的第一个节点
            return head;
        }*/
        
        // 递归法
        if (head == NULL || head->next == NULL)     // 空链或只有一个结点，直接返回头指针
        {
            return head;            
        }

        else                                        // 有两个以上结点
        {
            ListNode *new_head = reverseList(head->next); // 反转以第二个结点为头的子链表
            
            // head->next 此时指向子链表的最后一个结点
            
            // 将之前的头结点放入子链尾
            head->next->next = head;
            head->next = NULL;
            
            return new_head;
        }
    }
};

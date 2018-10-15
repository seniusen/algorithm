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
    ListNode* middleNode(ListNode* head) {
        

        ListNode* slow = head;  // 慢指针指向头结点
        ListNode* fast = head;  // 快指针指向头结点

        // 奇数结点快指针指向最后一个结点结束
        // 偶数结点快指针指向 NULL 结束
        while(fast && fast->next)   
        {
            slow = slow->next;          // 慢指针前进一步
            fast = fast->next->next;    // 快指针前进两步
        }

        return slow;    // 返回中间结点

    }
};

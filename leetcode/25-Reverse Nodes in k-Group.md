#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-566c58c55be11c18.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 2. 解答

- 首先，利用快慢指针确定链表的总结点数。

![](https://upload-images.jianshu.io/upload_images/11895466-19c26f31067cb408.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 偶数个结点时，结点个数等于 i * 2。

![](https://upload-images.jianshu.io/upload_images/11895466-8ee3230422213edf.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 奇数个结点时，结点个数等于 i * 2 + 1。

- 然后将链表的每 K 个结点划分为一组。循环对每组的子链表进行[翻转](https://blog.csdn.net/seniusen/article/details/83033827)，并依次拼接起来。

![](https://upload-images.jianshu.io/upload_images/11895466-5d444a089894949d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

![](https://upload-images.jianshu.io/upload_images/11895466-56fa80c4ca569179.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
- 最后，将多余的结点拼接在新链表最后面即可。
![](https://upload-images.jianshu.io/upload_images/11895466-705c3a63bf069054.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

- 代码如下
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        
        if (head == NULL || head->next == NULL || k == 1) //空链表或只有一个结点或者 k=1 不用翻转，直接返回
        {
            return head;
        }
        else
        {
            int node_num = 0; // 链表的结点个数
            ListNode* slow = head;
            ListNode* fast = head;
            
            // 利用快慢指针确定链表的结点总个数
            while(fast && fast->next)
            {
                slow = slow->next;
                fast = fast->next->next;
                node_num++;
            }
            
            if (fast) // 奇数个结点
            {
                node_num = node_num * 2 + 1;
            }
            else // 偶数个结点
            {
                node_num = node_num * 2;
            }
            
            int reverse_time = node_num / k; // 需要翻转链表的次数
            
            // 链表结点数小于 k，不需要翻转链表
            if (reverse_time == 0)
            {
                return head;
            }
            else
            {
                ListNode* temp = head; // 保存链表的头结点
                ListNode* tail = head; // 翻转后子链表的尾结点

                ListNode* p1 = head;
                ListNode* p2 = head;
                ListNode* p3 = NULL;

                for (int i = 0; i < reverse_time; i++)
                {
                    p2 = p2->next;

                    // 进行 k-1 次翻转
                    for (int j = 0; j < k-1; j++)
                    {
                        p3 = p2->next;
                        p2->next = p1;
                        p1 = p2;
                        p2 = p3;
                    }

                    if (i == 0)
                    {
                        temp = p1; // 第一轮翻转，temp 指向翻转后的新链表的头结点
                    }
                    else
                    {
                        tail->next = p1; // 连接翻转后的子链表
                    }

                    tail = head; // 指向翻转后的新链表的尾结点
                    head = p2; // 指向后面待翻转链表的第一个结点
                    p1 = p2;
                }

                tail->next = head; // 连接多余的结点

                return temp;
            }
            
        }     
    }
};
```


获取更多精彩，请关注「seniusen」! 
![seniusen](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

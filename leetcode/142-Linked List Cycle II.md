#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-a2afa09d32cef2e7.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 2. 解答

##### 2.1 方法 1

定义快慢两个指针，慢指针每次前进一步，快指针每次前进两步，若链表有环，则快慢指针一定会相遇。

当快慢指针相遇时，我们让慢指针指向头节点，快指针不变，然后每次快慢指针都前进一步，当两个指针再次相遇时，两个指针所指向的节点就是入环节点。

![](https://upload-images.jianshu.io/upload_images/11895466-5b1467e1836d0731.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

将链表的环向后展开，如上图所示，假设第一次相遇时慢指针走过了 a 个节点，即图中 s 节点，可知此时快指针指向同一个节点，即图中的 f 节点。

然后，假设慢指针从链表头到入环节点共有 b 个节点，快指针从快慢指针相遇节点到入环节点共有 c 个节点。那么可知第一次相遇时，快指针走过了 a+c+a-b 个节点，这应该是慢指针走过节点数的两倍，也即 a+c+a-b = 2a，所以有 b=c。



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
    ListNode *detectCycle(ListNode *head) {
        
        ListNode *slow = head;
        ListNode *fast = head;
        
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) break;
        }
        
        if (fast && fast->next)
        {
            slow = head;
            while (slow != fast)
            {
                slow = slow->next;
                fast = fast->next;
            }
            
            return slow;
        }
        
        return NULL;
    }
};
```
##### 2.2 方法 2

用 unordered_map 充当散列表的功能，每次将链表的节点指针作为键值存入 map，如果检测到当前节点指针已经存在于 map 中则说明当前节点指针即为链表入环的第一个节点。

```c
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
           
        unordered_map<ListNode *, char> nodemap;
        ListNode *temp = head;
        
        while (temp)
        {
            // 当前节点已存在于 map 中，即为链表入环的第一个节点
            if (nodemap.count(temp) == 1) return temp;
            nodemap[temp] = '0';
            temp = temp->next;
        }
        return NULL;
    }
};
```


获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

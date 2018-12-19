#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-f9045e50e1ffa348.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 2. 解答

##### 2.1 方法 1

定义快慢两个指针，慢指针每次前进一步，快指针每次前进两步，若链表有环，则快慢指针一定会相遇。

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
    bool hasCycle(ListNode *head) {
        
        ListNode *slow = head;
        ListNode *fast = head;
        
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
         return false;
    }
};
```

##### 2.2 方法 2

用 unordered_map 充当散列表的功能，每次将链表的节点指针作为键值存入 map，如果检测到当前节点指针已经存在于 map 中则说明链表有环。

```c
class Solution {
public:
    bool hasCycle(ListNode *head) {
        
        unordered_map<ListNode *, char> nodemap; // 散列表功能
        ListNode *temp = head;
        
        while (temp)
        {
            if (nodemap.count(temp) == 1) return true; // 当前节点已存在于 map 中，则说明有环
            nodemap[temp] = '0';
            temp = temp->next;
        }
        return false;
    }
};
```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

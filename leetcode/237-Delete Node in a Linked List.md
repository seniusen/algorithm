#### 1. 题目

![237](https://upload-images.jianshu.io/upload_images/11895466-81f46b3caa396003.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 2. 解答
- 因为给定的只有一个待删除的结点指针，我们并不知道其前面结点，所以需要将待删除结点后面的结点值复制到前面结点去，然后指向其后的第二个结点即可。

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
    void deleteNode(ListNode* node) {
        
        // 将待删除结点后面的结点值复制到前面结点去，然后指向其后的第二个结点
       
        node->val = node->next->val;
        node->next = node->next->next;
    }
};
```

获取更多精彩，请关注「seniusen」! 
![seniusen](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

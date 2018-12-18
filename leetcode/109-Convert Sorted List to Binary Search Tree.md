
#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-a7edb84b7f089610.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 2. 解答

##### 2.1. 方法一 

在 [LeetCode 108——将有序数组转化为二叉搜索树](https://blog.csdn.net/seniusen/article/details/84260240) 中，我们已经实现了将有序数组转化为二叉搜索树。因此，这里，我们可以先遍历一遍链表，将节点的数据存入有序数组中，然后再将有序数组转化为二叉搜索树即可。

```c
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        
        vector<int> nums;
        
        while (head != NULL)
        {
            nums.push_back(head->val);
            head = head->next;
        }
        
        return sortedArrayToBST(nums, 0, nums.size()-1);
    }
    
    TreeNode* sortedArrayToBST(vector<int>& nums, int begin, int end) {
        
        if (end < begin) return NULL; // 数组为空
        int mid = begin + (end - begin) / 2;
                
        TreeNode * tree = new TreeNode(nums[mid]); // 中值作为根节点
        tree->left = sortedArrayToBST(nums, begin, mid-1); // 左子树
        tree->right = sortedArrayToBST(nums, mid+1, end); // 右子树
        
        return tree;
    }
};
```
##### 2.2. 方法二 

将有序数组转化为二叉搜索树的核心思想就是**找到数组的中间数据，以此为根节点，然后再递归建立左右子树**。因此，借助于 [LeetCode 876——链表的中间结点](https://blog.csdn.net/seniusen/article/details/83042504) 中的思想，我们可以快速地找到链表的中间节点，然后再以中间节点前后的两个子链分别建立左右子树即可。

如下图所示，当 slow 指针指向中间节点时，last 指针指向中间节点的上一个节点，slow->next 是右子链的头结点，而将 last->next 指向 NULL 后，左子链的头节点即为 head。

![](https://upload-images.jianshu.io/upload_images/11895466-f0773e923ead1f5d.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

此外，要注意一种特殊情况，当只有一个节点时，此时 last、slow、fast 都指向这个节点，那么**左子链此时应为空**。

![](https://upload-images.jianshu.io/upload_images/11895466-05a687206cbdc6d8.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

```c
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        
        ListNode* last = head;
        ListNode* slow = head;  
        ListNode* fast = head;  

        // 循环结束时慢指针指向中间结点
        while(fast && fast->next)   
        {
            last = slow;
            slow = slow->next; 
            fast = fast->next->next;
        }
        
        if (slow == NULL) return NULL;
                
        TreeNode * tree = new TreeNode(slow->val); // 中值作为根节点
        
        if (last == slow) tree->left = NULL;
        else
        {         
            last->next = NULL;
            tree->left = sortedListToBST(head); // 左子树
        }
        tree->right = sortedListToBST(slow->next); // 右子树
        
        return tree;
        
    }
    
};
```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)



#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-e480d84fa9bc4254.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 2. 解答

如果根节点为空，直接返回 NULL。如果根节点非空，从根节点开始循环查找，直到节点为空。
- 如果待查找的值大于当前节点值，节点指向右孩子；
- 如果待查找的值小于当前节点值，节点指向左孩子；
- 如果待查找的值等于当前节点值，返回当前节点。

若循环结束还没有找到，返回 NULL。

```c
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* searchBST(TreeNode* root, int val) {
        
        
        if (root == NULL) return NULL;
        
        TreeNode* temp = root;
        
        while(temp)
        {
            if (val < temp->val) temp = temp->left;
            else if (val > temp->val) temp = temp->right;
            else return temp;
        }
        
        return NULL;
        
    }
};
```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

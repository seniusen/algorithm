
#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-98360433f7033131.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 2. 解答

如果根节点为空，直接返回 0。如果根节点非空，递归得到其左右子树的深度，树的深度就为左右子树深度的最大值加 1。

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
    int maxDepth(TreeNode* root) {
        
        if (root == NULL) return 0;
        else
        {
            int a = maxDepth(root->left);
            int b = maxDepth(root->right);
            return a > b ? a+1 : b+1;
        }
    }
};
```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

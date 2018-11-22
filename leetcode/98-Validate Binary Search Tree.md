
#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-010b2c1b786b7abe.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 2. 解答

针对一个节点，有下列四种情况：

- 节点为空或者节点的左右节点都为空；
- 只有右结点为空；
- 只有左结点为空；
- 左右结点都不为空；

如果当前节点的左右子节点值满足二叉搜索树的条件，我们可以**递归判断左右子树是否为二叉搜索树**。如果左右子树也满足二叉搜索树条件，同时**左子树最大节点（也即前驱结点）值小于当前节点值，右子树最小节点（也即后继结点）值大于当前节点值**，那么整棵树即为二叉搜索树。

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
    bool isValidBST(TreeNode* root) {
        
        if (root == NULL || (root->left == NULL && root->right == NULL)) return true;
        else if (root->left != NULL && root->right == NULL)
        {
            if (root->left->val >= root->val) return false;
            else return isValidBST(root->left) && isValidprev_node(root->left, root->val);
        }
        else if (root->left == NULL && root->right != NULL)
        {
            if (root->right->val <= root->val) return false;
            else return isValidBST(root->right) && isValidnext_node(root->right, root->val);
        }
        else 
        {
            if (root->right->val <= root->val || root->left->val >= root->val) return false;
            else return isValidBST(root->left) && isValidprev_node(root->left, root->val) 
                && isValidBST(root->right) && isValidnext_node(root->right, root->val);
        }        
    }
    
    // 前驱节点是否有效
    bool isValidprev_node(TreeNode* root, int data)
    {
        while (root->right != NULL)
        {
            root = root->right;
        }
        if (root->val < data) return true;
        else return false;
    }
    // 后继节点是否有效
    bool isValidnext_node(TreeNode* root, int data)
    {
        while (root->left != NULL)
        {
            root = root->left;
        }
        if (root->val > data) return true;
        else return false;
    }
      
};
```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

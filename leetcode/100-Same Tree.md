
#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-a7131e477c4af977.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 2. 解答

针对两棵树的根节点，有下列四种情况：

- p 和 q 都为空，两棵树相同；
- p 不为空 q 为空，两棵树不相同；
- p 为空 q 不为空，两棵树不相同；
- p 和 q 都不为空，如果两个节点的值相同，而且递归判断左右子树也相同的话，两棵树相同，反之两棵树不同。


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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        
        if (p == NULL && q == NULL) return true;
        else if (p != NULL && q == NULL) return false;
        else if (p == NULL && q != NULL) return false;
        else
        {
            if (p->val == q->val) return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
            else return false;
        }
        
    }
};
```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

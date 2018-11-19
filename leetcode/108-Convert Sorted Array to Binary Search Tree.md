#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-5f50f26480608ab2.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 2. 解答

一棵高度平衡的二叉搜索树意味着根节点的左右子树包含相同数量的节点，也就是**根节点为有序数组的中值**。

因此，我们将数组的中值作为根节点，然后再递归分别得到左半部分数据转化的左子树和右半部分数据转化的右子树即可。

递归终止的条件是数组为空，这时候返回 NULL。

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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        
        int num = nums.size(); 
        if (num == 0) return NULL; // 数组为空
        int mid = num / 2;
                
        TreeNode * tree = new TreeNode(nums[mid]); // 中值作为根节点
        vector<int> left_nums = vector<int>(nums.begin(), nums.begin() + mid);
        tree->left = sortedArrayToBST(left_nums); // 左子树
        
        vector<int> right_nums = vector<int>(nums.begin() + mid + 1, nums.end());
        tree->right = sortedArrayToBST(right_nums); // 右子树
        
        return tree;
    }
};
```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

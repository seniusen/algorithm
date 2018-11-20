
#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-6cf87410a576f126.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 2. 解答

以 $1, 2, \cdots, n$ 构建二叉搜索树，其中，任意数字都可以作为根节点来构建二叉搜索树。当我们将某一个数字作为根节点后，其左边数据将构建为左子树，右边数据将构建为右子树。因此，这是一个递归问题。

假设序列为 $[begin, end]$，若以第 $i$ 个数据为根节点，其左边数据 $[begin, i-1]$ 可以构建出左子树 left_tree，右边数据 $[i+1, end]$ 可以构建出右子树 right_tree。它们都存储在一个向量中，因此，我们需要遍历左右子树所有可能的情况，分别构建二叉搜索树。

其中要特别注意，**如果某一个子树向量为空，我们需要在向量中添加一个空指针，保证循环进行一次**，这时候只需要遍历另一个子树即可。

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
    vector<TreeNode*> generateTrees(int n) {
        
        return generateTrees(1, n);
    }
    
    vector<TeeNode*> generateTrees(int begin, int end) {
        
        vector<TreeNode*> all_tree;     
        vector<TreeNode*> left_tree;
        vector<TreeNode*> right_tree;
        TreeNode *tree = NULL;

        if (begin > end) return all_tree;

        for (int i = begin; i <= end; i++)
        {
            left_tree = generateTrees(begin, i - 1);
            right_tree = generateTrees(i + 1, end);
            
            // 左右子树如果为空的话需要循环一次
            if (left_tree.size() == 0) left_tree.push_back(NULL);
            if (right_tree.size() == 0) right_tree.push_back(NULL);
            for (int j = 0; j < left_tree.size(); j++)
            {         
                for (int k = 0; k < right_tree.size(); k++)
                {
                    tree = new TreeNode(i); // 每次都需要建一个新树
                    tree->left = left_tree[j];
                    tree->right = right_tree[k];
                    all_tree.push_back(tree);
                }
            }
        }
        
        return all_tree;
    }
};
```

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

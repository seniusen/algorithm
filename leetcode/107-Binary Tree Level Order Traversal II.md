#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-a0325eaa166ec976.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 2. 解答
与 [LeetCode 102 ——二叉树的层次遍历](https://blog.csdn.net/seniusen/article/details/84183651) 类似，**我们只需要将每一层的数据倒序输出即可**。

定义一个存放树中数据的向量 data，一个存放树的每一层数据的向量 level_data 和一个存放每一层节点的队列 node_queue。

如果根节点非空，根节点进队，然后循环以下过程直至队列为空：

- 1. 得到队列的大小，即为树中当前层的节点个数。队列元素循环出队，并将节点的值加入 level_data，如果节点有左右子节点，左右子节点入队
- 2.  **将 level_data 插入到 data 头部**并清空  level_data

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        
        vector<vector<int>> data;
        vector<int> level_data;
        queue<TreeNode *> node_queue;
        int node_num = 1;
        TreeNode* temp = NULL;
        
        if (root) node_queue.push(root);
        
        while (!node_queue.empty())
        {
            node_num = node_queue.size();
            for (int i = 0; i < node_num; i++)
            {
                temp = node_queue.front();
                node_queue.pop();
                level_data.push_back(temp->val);
                
                if (temp->left)     node_queue.push(temp->left);
                if (temp->right)    node_queue.push(temp->right);
            }
            
            data.push_back(level_data);
            level_data.clear();
        }
        
        return data;
    }
};
```

获取更多精彩，请关注「seniusen」! 

![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


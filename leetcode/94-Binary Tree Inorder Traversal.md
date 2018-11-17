#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-9c3f21868f53c9d8.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 2. 解答

##### 2.1. 递归法

定义一个存放树中数据的向量 data，从根节点开始，如果节点不为空，那么
- 1. 递归得到其左子树的数据向量 temp，将 temp 合并到 data 中去
- 2. 将当前节点的数值加入到 data 中
- 3. 递归得到其右子树的数据向量 temp，将 temp 合并到 data 中去

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
    vector<int> inorderTraversal(TreeNode* root) {
        
        vector<int> data = {};
        vector<int> temp = {};

        if (root != NULL)
        {
            temp = inorderTraversal(root->left);
            data.insert(data.end(),temp.begin(),temp.end());
            data.push_back(root->val);
            temp = inorderTraversal(root->right);
            data.insert(data.end(),temp.begin(),temp.end());
        }
        
        return data;
    }
};
```

##### 2.2. 迭代法

定义一个存放树中节点的栈 node_stack 和存放数据的向量 data，从根节点开始，如果节点不为空或者栈非空，循环以下过程：
- 1. 如果节点非空，将节点压入栈，节点指向其左孩子，循环直到节点为空
- 2. 如果节点为空，弹出栈顶节点，将节点的值加入 data，然后将节点指向其右孩子

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
    vector<int> inorderTraversal(TreeNode* root) {
            
        vector<int> data = {};
        stack<TreeNode*> node_stack;
        TreeNode* temp = root;
        
        while (temp || !node_stack.empty())
        {
            while(temp != NULL)
            {
                node_stack.push(temp);
                temp = temp->left;
            }
            
            temp = node_stack.top();
            node_stack.pop();
            data.push_back(temp->val);
            temp = temp->right;
        }
        
        return data;
    }
};
```

##### 2.3. Morris 遍历法

前面两种方法要么需要函数栈要么需要人工栈，其空间复杂度为 $O(n)$，而 Morris 遍历法可以做到在不影响时间复杂度的情况下做到空间复杂度为 $O(1)$。

定义一个存放数据的向量 data，从根节点开始，如果当前节点非空，循环以下过程：
- 1. 如果当前节点没有左孩子，将当前节点的值加入到 data 中，当前节点指向其右孩子
- 2. 如果当前节点有左孩子，则寻找当前节点的前驱节点，即节点值小于该节点值并且值最大的节点，也即当前节点左子树中值最大的节点 
  - a) 如果前驱节点没有右孩子，前驱节点右孩子指向当前节点，当前节点指向其左孩子
  - b) 如果前驱节点右孩子为当前节点，将当前节点的值加入到 data 中，当前节点指向其右孩子，前驱节点右孩子设为空（恢复原有树结构）

![](https://upload-images.jianshu.io/upload_images/11895466-66be937c5dfa4531.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

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
    vector<int> inorderTraversal(TreeNode* root) {
            
        vector<int> data = {};
        TreeNode* cur = root;
        TreeNode* pre = NULL;

        while (cur)
        {
            if (cur->left == NULL)
            {
                data.push_back(cur->val);
                cur = cur->right;
            }
            
            else
            {
                // 寻找前驱结点
                pre = cur->left;
                while (pre->right != cur && pre->right)
                {
                    pre = pre->right;
                }
                
                if (pre->right == NULL)
                {
                    pre->right = cur;
                    cur = cur->left;
                }
                else
                {
                    data.push_back(cur->val);
                    cur = cur->right;
                    pre->right = NULL;
                }
            }
        }
        
        return data;
    }
};
```

[参考资料](https://www.cnblogs.com/AnnieKim/archive/2013/06/15/MorrisTraversal.html)

获取更多精彩，请关注「seniusen」! 

![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

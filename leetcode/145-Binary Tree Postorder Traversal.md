#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-433df85be45119d3.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 2. 解答

##### 2.1. 递归法

定义一个存放树中数据的向量 data，从根节点开始，如果节点不为空，那么

- 1. 递归得到其左子树的数据向量 temp，将 temp 合并到 data 中去
- 2. 递归得到其右子树的数据向量 temp，将 temp 合并到 data 中去
- 3. 将当前节点的数值加入到 data 中

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
    vector<int> preorderTraversal(TreeNode* root) {
        
        vector<int> data = {};
        vector<int> temp = {};

        if (root != NULL)
        {
            temp = postorderTraversal(root->left);
            data.insert(data.end(),temp.begin(),temp.end());
            temp = postorderTraversal(root->right);
            data.insert(data.end(),temp.begin(),temp.end());
            data.push_back(root->val);
        }
        
        return data;        
    }
};
```

##### 2.2. 迭代法一

> 仿照前序遍历的思想，只不过这次我们的顺序为中-右-左，然后倒序将其加入到向量中，即为后序左-右-中的结果。

定义一个存放树中节点的栈 node_stack 和存放数据的向量 data，从根节点开始，如果节点不为空或者栈非空，循环以下过程：
- 1. 如果节点非空，**将节点的值加入 data 的头部**，如果节点有左孩子，将节点左孩子压入栈，节点指向其右孩子，循环直到节点为空
- 2. 如果节点为空，栈非空，则弹出栈顶节点

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
    vector<int> preorderTraversal(TreeNode* root) {

        // 按照中右左前序遍历，倒序存储即为左右中
        vector<int> data = {};
        stack<TreeNode*> node_stack;
        TreeNode* temp = root;
        
        while (temp || !node_stack.empty())
        {
            while(temp != NULL)
            {
                data.insert(data.begin(), temp->val); // 在头部插入
                if (temp->left)    node_stack.push(temp->left);
                temp = temp->right;
            }
            
            // 若最后一个节点没有左子节点，栈为空
            if (!node_stack.empty()) // 栈非空
            {
                temp = node_stack.top();
                node_stack.pop();
            }
        }
        
        return data;
    }
};
```

##### 2.3. 迭代法二

> 后序遍历的话只有某一节点的左右子节点都被访问过之后才能访问该节点。

定义一个存放树中节点的栈 node_stack 和存放数据的向量 data，如果树非空，先将根节点压入栈。

cur 指向当前节点，pre 指向上一次访问的节点，初始化为空，然后栈非空则循环以下过程：

当前节点为栈顶节点
- 1. 如果**节点左右子节点都为空或者上一次访问的节点为其左右子节点中的一个**，（某些节点可能只有一个子节点，所以 pre 不能为空，然后若只有左子节点，则上一次访问的为其左子节点；若有左右子节点，按照压栈顺序，则上一次访问的为其右子节点；）则弹出栈顶节点，将节点数据加入 data，将上一次访问的节点指向当前节点
- 2. 否则，如果存在左右子节点，先压入其右子节点，再压入其左子节点

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
    vector<int> preorderTraversal(TreeNode* root) {

       vector<int> data = {};
        stack<TreeNode*> node_stack;
        if (root)   node_stack.push(root); // 树非空，先将根节点压入栈
        
        TreeNode* cur = root;   // 当前节点
        TreeNode* last = NULL;  // 上一次访问的节点
        
        while (!node_stack.empty())
        {
            cur = node_stack.top();
            
            if ((cur->left == NULL && cur->right == NULL) || 
                (last != NULL && (cur->left == last || cur->right == last)))
            {
                data.push_back(cur->val);
                node_stack.pop();
                last = cur;
            }
            else
            {
                if (cur->right) node_stack.push(cur->right);
                if (cur->left) node_stack.push(cur->left);
            }
        }
        
        return data;
    }
};
```

[参考资料](https://www.cnblogs.com/AnnieKim/archive/2013/06/15/MorrisTraversal.html)

获取更多精彩，请关注「seniusen」! 

![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 1. 题目

![23](https://upload-images.jianshu.io/upload_images/11895466-e66379111fcfb1b1.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)


#### 2. 解答

##### 2.1. 方法一
- 在 [合并两个有序链表](https://www.jianshu.com/p/8a57f46e4fc3) 的基础上，我们很容易想到第一种解法，首先我们将第一个链表和第二个链表合并成一个新的链表，然后再往后依次合并接下来的每个链表即可。

- 假设每个链表结点数一样都为 n，第一次合并时，要遍历 2n 个结点，往后则要分别遍历 3n, 4n, ... , kn 个结点。可以看到，每次进行合并时都要将之前所有的链表遍历一次，因此这个方法的时间复杂度较高，为 $O((\frac{k(k+1)}{2} - 1) * n)$。

- 代码如下
```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        
        int k = lists.size(); // 链表个数
        
        if (k >= 2)
        {   
            // 先将前两个链表合并为一个新链表，再把新链表依次和后面的链表合并
            ListNode *head = mergeTwoLists(lists[0], lists[1]);
            for (int i = 2; i < k; i++)
            {
                head = mergeTwoLists(head, lists[i]);
            }
            
            return head;  
        }
        else if (k == 1)
        {
            return lists[0];
        } 
        else
        { 
            return NULL;
        }
        
    }
    
        ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        
        ListNode *head = new ListNode(0); // 新建哨兵结点，方便操作
        ListNode *temp = head;
        
        // 依次比较两个链表的结点值，将值较小的结点插入到新建的链表后面
        while(l1 && l2)
        {
            if (l2->val <= l1->val)
            {
                temp->next = l2;
                temp = temp->next;
                l2 = l2->next;
            }
            else
            {
                temp->next = l1;
                temp = temp->next;
                l1 = l1->next;
            }
        }
        
        // 其中一个链表比较完毕，将另外一个链表剩余结点直接插入到新建的链表后面
        if (l1)
        {
            temp->next = l1;
        }
        else
        {
            temp->next = l2;
        }
        
        temp = head;
        head = head->next;// 删除哨兵结点
        delete(temp);
        
        return head;  
    }
};
```

##### 2.2. 方法二

- 我们还可以每次**只合并相邻的两个链表**，这样经过第一次合并后，链表个数减半，我们一直重复这个过程，直到最后剩余一个链表即可。

- 假设每个链表结点数一样都为 n，第一次合并时，要进行 $\frac{k}{2}$ 次合并，每次合并要遍历 2n 个结点；第二次合并时，要进行 $\frac{k}{4}$ 次合并，每次合并要遍历 4n 个结点；可见，每次合并过程都只需要遍历 kn 次结点。而总共要进行 $log_2k$ 个循环，因此这个方法的时间复杂度为 $O(n * klog_2k)$，比第一个改善了许多。

- 代码如下
```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        
        int k = lists.size(); // 链表个数
        
        if (k >= 2)
        {   
            while(k != 1) // 循环合并过程直到剩余一个链表
            {
                if (k % 2 == 0)  // 总共偶数个链表，依次合并相邻两个链表然后从前往后放到 vector 中去
                {
                    for (int i = 0; i < k; i=i+2)
                    {
                        lists[i / 2] = mergeTwoLists(lists[i], lists[i+1]);
                    }
                    k = k / 2; // 每次合并后的新链表个数
                }
                
                else // 总共奇数个链表，依次合并相邻两个链表然后从前往后放到 vector 中去，最后余一个链表直接放入 vector 最后面
                {
                    for (int i = 0; i < k - 1; i=i+2)
                    {
                        lists[i / 2] = mergeTwoLists(lists[i], lists[i+1]);
                    }
                    lists[k / 2] = lists[k-1];
                    k = k / 2 + 1; // 每次合并后的新链表个数
                }
            }
            
            return lists[0]; 
                  
        }
        else if (k == 1)
        {
            return lists[0];
        } 
        else
        { 
            return NULL;
        }
        
    }
    
        ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        
        ListNode *head = new ListNode(0); // 新建哨兵结点，方便操作
        ListNode *temp = head;
        
        // 依次比较两个链表的结点值，将值较小的结点插入到新建的链表后面
        while(l1 && l2)
        {
            if (l2->val <= l1->val)
            {
                temp->next = l2;
                temp = temp->next;
                l2 = l2->next;
            }
            else
            {
                temp->next = l1;
                temp = temp->next;
                l1 = l1->next;
            }
        }
        
        // 其中一个链表比较完毕，将另外一个链表剩余结点直接插入到新建的链表后面
        if (l1)
        {
            temp->next = l1;
        }
        else
        {
            temp->next = l2;
        }
        
        temp = head;
        head = head->next;// 删除哨兵结点
        delete(temp);
        
        return head;  
    }
};
```

##### 2.3. 方法三

- 利用 C++ 模板库中的优先队列构建小顶堆，每次首结点元素值最小的链表出队，然后将首结点插入到新链表后面，再把删除首结点后的子链表放入队列中继续比较，直到队列为空结束。

- 代码如下
```c
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        
        int k = lists.size();
        
        struct cmp
        {
            bool operator()(ListNode* a, ListNode* b)
            {
                return a->val > b->val;
            }
        };

        priority_queue<ListNode *, vector<ListNode*>, cmp> q; // 构建小顶堆

        for (int i = 0; i < k; i++)
        {
            if (lists[i])
                q.push(lists[i]);  // 链表非空，加入队列
        }

        ListNode *head = new ListNode(0); // 新建哨兵结点，方便操作
        ListNode *temp = head;

        while(!q.empty())
        {
            temp->next = q.top(); // 将元素值最小的首结点插入到新链表后面
            temp = temp->next; // 指针后移
            q.pop();        // 首结点元素值最小的链表出队
            if (temp->next)  // 把删除首结点后的链表放入队列中
                q.push(temp->next);
        }

        temp = head;
        head = head->next;
        delete(temp);  // 删除哨兵结点

        return head;
    }
};
```

获取更多精彩，请关注「seniusen」! 
![seniusen](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 1. 题目

![](https://upload-images.jianshu.io/upload_images/11895466-a8bf0fdce3c0a620.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

#### 2. 解答

第一次遍历链表的时候，复制旧链表的节点值建立一个新的链表，同时定义一个 unordered_map 作为哈希表，哈希表的键为旧链表的节点指针，值为新链表的节点指针。

然后，第二次遍历链表，访问旧链表节点的随机指针，然后以此为键从 map 中取出对应的新链表节点指针，这也就是当前新链表节点的随机指针。


```c
/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        
        unordered_map<RandomListNode *, RandomListNode *> nodemap;
        RandomListNode *temp = head;
        RandomListNode *new_head = new RandomListNode(0); //哨兵节点，方便操作
        RandomListNode *copy_temp = new_head;
 
        // 建立新链表
        while (temp)
        {
            copy_temp->next = new RandomListNode(temp->label);
            nodemap[temp] = copy_temp->next;
            
            temp = temp->next;
            copy_temp = copy_temp->next;
        }
        
        RandomListNode *random_temp = NULL;
        temp = head;
        copy_temp = new_head->next;
        // 填充新链表的随机指针
        while (temp)
        {
            random_temp = temp->random;
            if (random_temp != NULL)   copy_temp->random = nodemap[random_temp];
            else    
                copy_temp->random = NULL;
            
            temp = temp->next;
            copy_temp = copy_temp->next;
        }
        
        return new_head->next;
    }
};
```


获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

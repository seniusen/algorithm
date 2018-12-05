在社交网络中，有一个[六度分割理论](https://zh.wikipedia.org/wiki/%E5%85%AD%E5%BA%A6%E5%88%86%E9%9A%94%E7%90%86%E8%AE%BA)，具体是说，世界上任何互不相识的两人，平均只需要六步就能够建立起联系。一个用户的一度连接用户就是他的好友，二度连接用户就是他好友的好友，三度连接用户就是他好友好友的好友。

给定一个用户，如何找出这个用户的所有三度（包括一度、二度和三度）好友关系呢？

### 1. 什么是 “搜索” 算法

我们知道，算法都是作用于某种具体的数据结构上的，而深度优先搜索算法和广度优先搜索算法就是作用于图这种数据结构的。

图上的搜索算法，就是**从图中的一个顶点出发，到另一个顶点的路径**。图有两种存储方法，邻接矩阵和邻接表，在这里我们用邻接表来存储图，并以无向图作为例子，但这两种算法也同样都可以应用在有向图中。

```c
// 无向图
class Graph
{
private:
    int v;  // 顶点个数
    vector<vector <int> > adjacent_list; // 嵌套向量来表示邻接表
    bool found; // 深度优先搜索算法中标志变量

public:
    Graph(int n)
    {
        v = n;
        found = false;
        for (int i = 0; i < v; i++)
        {
            vector<int> temp;
            adjacent_list.push_back(temp);
        }
    }

    // 无向图中一条边的两个顶点都要存储
    void AddEdge(int s, int t)
    {
        adjacent_list[s].push_back(t);
        adjacent_list[t].push_back(s);
    }

    void BFS(int s, int t);
    void Print(int prev[], int s, int t);
    void RecursiveDFS(int prev[], int visited[], int cur, int t);
    void DFS(int s, int t);
};
```

### 2. 广度优先搜索（BFS）

广度优先搜索（Breadth-First-Search），一般简称为 BFS。直观地讲，它其实就是一种地毯式层层推进的搜索策略，即先查找离起始顶点最近的，然后是次近的，依次往外搜索。

![](https://upload-images.jianshu.io/upload_images/11895466-b816cf52f1d7fb3e.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

下面这段代码的功能是搜索一条从顶点 s 到顶点 t 的一条最短的路径。

```c
void Graph::Print(int prev[], int s, int t)
{
    if (prev[t] != -1 && t != s)
    {
        Print(prev, s, prev[t]);
    }
    cout << t << ' ';
}

// 从 s 到 t 的广度优先搜索
void Graph::BFS(int s, int t)
{
    if (s == t) return;

    int visited[v] = {0};
    int prev[v] = {0};
    queue<int> vertex;

    visited[s] = 1;
    vertex.push(s);
    for (int i = 0; i < v; i++) prev[i] = -1;

    while(!vertex.empty())
    {
        int cur = vertex.front();
        vertex.pop();
        for (unsigned int i = 0; i < adjacent_list[cur].size(); i++)
        {
            int temp = adjacent_list[cur][i];
            if (!visited[temp])
            {
                prev[temp] = cur;
                if (temp == t)
                {
                    Print(prev, s, t);
                    return;
                }
                vertex.push(temp);
                visited[temp] = 1;
            }
        }
    }
}
```
其中，有三个非常重要的辅助变量需要特别注意。

- **visited**，布尔数组，记录顶点是否已经被访问过，访问过则为真，没有访问过则为假，这里用 0 和 1 表示。
- **vertex**，记录上一层的顶点，也即已经被访问但其相连的顶点还没有被访问的顶点。当一层的顶点搜索完成后，我们还需要通过这一层的顶点来遍历与其相连的下一层顶点，这里我们用队列来记录上一层的顶点。
- **prev**，记录搜索路径，保存的是当前顶点是从哪个顶点遍历过来的，比如 prev[4] = 1，说明顶点 4 是通过顶点 1 而被访问到的。

![](https://upload-images.jianshu.io/upload_images/11895466-9b707a03987bd122.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![](https://upload-images.jianshu.io/upload_images/11895466-983228b5d99c9a56.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
![](https://upload-images.jianshu.io/upload_images/11895466-22ae0c66b9d1e31d.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

下面我们来看一下广度优先搜索的时间复杂度和空间复杂度。

最坏情况下，终止顶点 t 距离起始顶点 s 很远，需要遍历完整个图才能找到。这时候，每个顶点都要进出一遍队列，每条边也都会被访问一次。所以，广度优先搜索的时间复杂度为 O(V+E)，V 为顶点个数，E 为边的条数。针对一个所有顶点都是联通的图，E 肯定要大于 V-1，所以时间复杂度可以简写为 O(V)。

空间复杂度主要是三个变量所占用的额外空间，和顶点个数成正相关，为 O(V)。

### 3. 深度优先搜索（DFS）

深度优先搜索（Depth-First-Search），简称 DFS，最直观的例子就是走迷宫。

假设你站在迷宫的某个分岔路口，你想找到出口。你随意选择一个岔路口来走，走着走着发现走不通的时候就原路返回到上一个分岔路口，再选择另一条路继续走，直到找到出口，这种走法就是深度优先搜索的策略。

![](https://upload-images.jianshu.io/upload_images/11895466-8974c07087798b7c.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

上图中，我们希望找到一条从 s 到 t 的路径，其中实线表示向前遍历，虚线表示回退。可以看到，深度优先搜索到的并不是从 s 到 t  的最短路径。

实际上，深度优先搜索用的是一种比较著名的思想——**回溯思想**，这种思想非常适合用递归来实现。深度优先搜索的代码里面有几个和广度优先搜索一样的部分 visited、prev 和 Print() 函数，它们的作用也都是一样的。此外，还有一个特殊的 found 变量，标记是否找到终止顶点，找到之后我们就可以停止递归不用再继续查找了。

```c
void Graph::RecursiveDFS(int prev[], int visited[], int cur, int t)
{
    if (found) return;

    if (cur == t)
    {
        found = true;
        return;
    }

    for (unsigned int i = 0; i < adjacent_list[cur].size(); i++)
    {
        int temp = adjacent_list[cur][i];
        if (!visited[temp])
        {
            prev[temp] = cur;
            visited[temp] = 1;
            RecursiveDFS(prev, visited, temp, t);
        }
    }
    return;
}

// 从 s 到 t 的深度优先搜索
void Graph::DFS(int s, int t)
{
    if (s == t) return;

    int visited[v] = {0};
    int prev[v] = {0};

    visited[s] = 1;
    for (int i = 0; i < v; i++) prev[i] = -1;
    RecursiveDFS(prev, visited, s, t);

    Print(prev, s, t);
}
```

在深度优先搜索算法中，每条边最多会被访问两次，一次是遍历，一次是回退。所以，深度优先搜索的时间复杂度为 O(E)。

visited、prev 数组的大小为顶点个数，而递归函数调用栈的最大深度不会超过顶点的个数，所以深度优先搜索的空间复杂度为 O(V)。

测试代码如下，对应图为上面广度优先搜索算法中的例图。

```c
int main ()
{
    Graph g1(8);
    g1.AddEdge(0, 1);
    g1.AddEdge(0, 3);
    g1.AddEdge(1, 4);
    g1.AddEdge(1, 2);
    g1.AddEdge(3, 4);
    g1.AddEdge(4, 5);
    g1.AddEdge(4, 6);
    g1.AddEdge(2, 5);
    g1.AddEdge(5, 7);
    g1.AddEdge(6, 7);
    //g1.BFS(3, 7);
    g1.DFS(3, 2);

    return 0;
}
```
### 4. 查找三度好友？

查找用户的三度好友，也就是距离用户 3 条边以内的用户。也就是说，在广度优先算法中，我们只需要向外查找 3 层即可，可以通过一个数组记录当前顶点与起始顶点的距离来实现。在深度优先算法中，我们只需要控制最多只从起始顶点递归 3 次即可，可以通过一个变量记录递归深度来实现。



[参考资料-极客时间专栏《数据结构与算法之美》](https://time.geekbang.org/column/126)

获取更多精彩，请关注「seniusen」! 
![](https://upload-images.jianshu.io/upload_images/11895466-ee82f7655f20bfeb.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

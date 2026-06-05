# Dijkstra 最短路算法

## 核心思想

Dijkstra 算法用于求解带权有向图（或无向图）中单源最短路径问题，适用于边权非负的情况。

算法从起点 `s` 开始，逐步“扩展”已知最短路径的节点集合。每次选择当前距离起点最近的未确认节点作为中间节点，然后通过它去松弛其所有邻边。这样可以保证每个被确认的节点的距离是最终最短距离。

## 主要步骤

1. 初始化：
   - 所有节点的距离 `dis[i]` 设为无穷大
   - 起点 `s` 的距离设为 0
   - 所有节点标记为未访问

2. 使用优先队列（最小堆）保存候选节点，队列中的元素是 `(节点编号, 当前最短距离)`。

3. 反复执行：
   - 从优先队列中取出距离最小的节点 `x`
   - 如果这个节点已经被访问过，则跳过
   - 将 `x` 标记为已访问
   - 遍历 `x` 的所有出边 `x -> to`，尝试松弛：
     - 如果 `dis[to] > dis[x] + edge_weight`
     - 则更新 `dis[to]` 并把新的 `(to, dis[to])` 推入队列

4. 直到队列为空，或者所有可达节点的最短距离都被确认。

## 这段代码的实现说明

```cpp
#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

const int N=1e5+10;
const int M=2e5+10;

int n,m,s;
int cnt;
int head[N];
int vis[N];
int dis[N];

struct ty{
    int t,l,next;
}edge[M];

void addedge(int x,int y,int l){
    edge[++cnt].t=y;
    edge[cnt].l=l;
    edge[cnt].next=head[x];
    head[x]=cnt;
}
struct ty2{
    int x,dis;
    bool operator < (const ty2 &a) const{
        return dis>a.dis;
    }
};
priority_queue<ty2> q;
void dij(int s){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    ty2 tmp;
    tmp.x=s;
    tmp.dis=0;
    dis[s]=0;
    
    q.push(tmp);
    while(!q.empty()){
        int x=q.top().x;
        q.pop();
        if(vis[x]) continue;
        vis[x]=1;
        for(int i=head[x];i!=-1;i=edge[i].next){
            int to=edge[i].t;
            if(vis[to]) continue;
            if(dis[to]>dis[x]+edge[i].l){
                dis[to]=dis[x]+edge[i].l;
                ty2 tt;
                tt.x=to;
                tt.dis=dis[to];
                q.push(tt);
            }
        }

    }
    for(int i=1;i<=n;i++){
        cout<<dis[i]<<' ';
    }
}
int main(){
    memset(head,-1,sizeof(head));
    cin>>n>>m>>s;
    for(int i=0;i<m;i++){
        int x,y,l;
        cin>>x>>y>>l;
        addedge(x,y,l);
    }
    dij(s);
    return 0;
}
```

### 关键实现点

- `head[]` 和 `edge[]` 组成邻接表，`addedge` 用头插法保存每条有向边。
- `dis[]` 保存从起点到每个节点的当前最短距离。
- `vis[]` 防止节点被重复处理。
- 自定义 `ty2` 结构并重载 `operator<`，使 `priority_queue` 变成最小堆。
- 松弛操作：如果通过当前节点 `x` 到邻居 `to` 的距离更短，则更新 `dis[to]` 并将新候选值加入队列。

## 复杂度

- 时间复杂度：`O((n+m) log n)`。
- 空间复杂度：`O(n+m)`。

## 注意事项

- 该实现假设节点编号从 `1` 开始。
- 如果图中有不可达节点，最终输出的距离会是初始化时的一个大值。
- Dijkstra 算法要求边权不能为负。

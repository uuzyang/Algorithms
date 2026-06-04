#include<bits/stdc++.h>

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
//https://ac.nowcoder.com/acm/problem/208246
#include<bits/stdc++.h>

using namespace std;

const int N=40010;
const int M=160000;
struct ty{
    int t,l,next;
}edge[M];

int head[N];
int cnt=0;
void addedge(int x,int y,int l){
    // cout<<x<<' '<<y<<' '<<l<<endl;
    edge[++cnt].t=y;
    edge[cnt].l=l;
    edge[cnt].next=head[x];
    head[x]=cnt;
}
int n;
char a[110][110];
int vis[N];
int dis[N];

struct ty2{
    int x,dis;

    bool operator < (const ty2 &a) const{
        return dis>a.dis;
    }
};

priority_queue<ty2> q;

void dij(int s,int t){
    memset(vis,0,sizeof(vis));
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    ty2 tmp;
    tmp.x=s;
    tmp.dis=0;
    q.push(tmp);
    while(!q.empty()){
        int x=q.top().x;
        q.pop();
        if(vis[x]) continue;
        vis[x]=1;
        for(int i=head[x];i!=-1;i=edge[i].next){
            int y=edge[i].t;
            if(vis[y]) continue;
            if(dis[y]>dis[x]+edge[i].l){
                dis[y]=dis[x]+edge[i].l;
                ty2 tt;
                tt.x=y;
                tt.dis=dis[y];
                q.push(tt);
            }
        }
    }
    if(dis[t]>=0x3f3f3f3f) cout<<"-1"<<endl;
    else cout<<dis[t]<<endl;

}

int main(){
    memset(head,-1,sizeof(head));
    cnt=0;
    cin>>n;
    int startx,starty,endx,endy;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
            if(a[i][j]=='A'){
                startx=i;
                starty=j;
            }
            if(a[i][j]=='B'){
                endx=i;
                endy=j;
            }
        }
    }
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(a[i][j]=='x') continue;
            int idx=(i-1)*n+j;
            int s,x,z,y;
            s=(idx-1)*4+1; //上
            y=(idx-1)*4+2; //右
            x=(idx-1)*4+3;  //下
            z=(idx-1)*4+4;  //左
            addedge(s,x,0);
            addedge(x,s,0);
            addedge(z,y,0);
            addedge(y,z,0);
            addedge(s,y,1);
            addedge(y,s,1);
            addedge(y,x,1);
            addedge(x,y,1);
            addedge(x,z,1);
            addedge(z,x,1);
            addedge(z,s,1);
            addedge(s,z,1);
            if(i!=1){//连上一行的x
                if(a[i-1][j]!='x') {
                    int lx=(((i-2)*n+j)-1)*4+3;
                    addedge(lx,s,0);
                    addedge(s,lx,0);
                }
               
            }
            if(j!=1){//连上一列的y
                if(a[i][j-1]!='x'){
                    int ly=(idx-2)*4+2;
                    addedge(z,ly,0);
                    addedge(ly,z,0);
                }
            }

        }
    }
    //加一个超级源点和汇点 0 ,4*n*n+1.
    int si=(startx-1)*n+starty;
    int ei=(endx-1)*n+endy;
    addedge(0,(si-1)*4+1,0);
    addedge(0,(si-1)*4+2,0);
    addedge(0,(si-1)*4+3,0);
    addedge(0,(si-1)*4+4,0);
    addedge((ei-1)*4+1,n*n*4+1,0);
    addedge((ei-1)*4+2,n*n*4+1,0);
    addedge((ei-1)*4+3,n*n*4+1,0);
    addedge((ei-1)*4+4,n*n*4+1,0);
    dij(0,n*n*4+1);
    return 0;
}
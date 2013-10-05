#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long LL;
const LL oo=1e18;
const int mm=100+9;
const int nn=2000+9;
class Edge
{
  public:int v,next;LL dis;
}e[nn];
class heap
{
  public:int u;LL dis;
  bool operator <(const heap& x)const
  {
    return dis>x.dis;
  }
};
int head[mm],edge,n,m,L;
bool del[nn],vis[mm],belong[nn][mm];LL dis[mm][mm],dd[mm],sum_all,sum_del,sum_mid;
void data()
{
  memset(head,-1,sizeof(head));edge=0;
}
void add(int u,int v,LL _dis)
{
  e[edge].v=v;e[edge].dis=_dis;e[edge].next=head[u];head[u]=edge++;
}
void dijstra(LL*d,int S,bool action)
{
  memset(vis,0,sizeof(vis));
  priority_queue<heap>Q;
  for(int i=0;i<=n;++i)
    d[i]=oo;
    d[S]=0;
    Q.push((heap){S,0});
    heap z;int u,v;
    while(!Q.empty())
    {
      z=Q.top();Q.pop();
      u=z.u;
      if(vis[u])continue;vis[u]=1;
      for(int i=head[u];~i;i=e[i].next)
      { v=e[i].v;
        if(action&&del[i])continue;///i边已经删除
        if(d[v]>d[u]+e[i].dis)
        { if(!action)
          {belong[i^1][S]=belong[i][S]=1;}
          d[v]=d[u]+e[i].dis;Q.push((heap){v,d[v]});
        }
      }
    }
    if(!action)
    {
      for(int i=1;i<=n;++i)
        if(d[i]<oo)sum_all+=d[i];
        else sum_all+=L;
    }
    else
    {
      for(int i=1;i<=n;++i)
      {
        if(dis[S][i]<oo)sum_mid-=dis[S][i];
        else sum_mid-=L;///去除原边的影响
        if(d[i]<oo)sum_mid+=d[i];
        else sum_mid+=L;///加上新边
      }
    }
}
int main()
{ int a,b,c;
  while(~scanf("%d%d%d",&n,&m,&L))
  { data();
    for(int i=0;i<m;++i)
    {
      scanf("%d%d%d",&a,&b,&c);
      add(a,b,c);add(b,a,c);
    }
    sum_all=0;
    memset(del,0,sizeof(del));
    memset(belong,0,sizeof(belong));
    for(int i=1;i<=n;++i)
    dijstra(dis[i],i,0);
    sum_del=sum_all;
    for(int i=0;i<m;++i)
    { sum_mid=sum_all;
      del[i+i]=del[i+i+1]=1;
      for(int j=1;j<=n;++j)
        if(belong[i+i][j])///这个优化很关键，有点难，源点固定的最短路会改变，当且仅当最短路上的边
        dijstra(dd,j,1);///发生变动，而一条n点最短路最多n-1条边，因此最坏需要n*(n-1)次改变
      if(sum_del<sum_mid)sum_del=sum_mid;
      del[i+i]=del[i+i+1]=0;
    }
    printf("%lld %lld\n",sum_all,sum_del);
  }
  return 0;
}

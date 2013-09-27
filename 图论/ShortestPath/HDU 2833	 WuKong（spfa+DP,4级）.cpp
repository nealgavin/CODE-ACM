E - WuKong
Time Limit:1000MS     Memory Limit:32768KB     64bit IO Format:%I64d & %I64u
Submit
 
Status
Appoint description: 
Description
Liyuan wanted to rewrite the famous book “Journey to the West” (“Xi You Ji” in Chinese pinyin). In the original book, the Monkey King Sun Wukong was trapped by the Buddha for 500 years, then he was rescued by Tang Monk, and began his journey to the west. Liyuan thought it is too brutal for the monkey, so he changed the story:

One day, Wukong left his home - Mountain of Flower and Fruit, to the Dragon   King’s party, at the same time, Tang Monk left Baima Temple to the Lingyin Temple to deliver a lecture. They are both busy, so they will choose the shortest path. However, there may be several different shortest paths between two places. Now the Buddha wants them to encounter on the road. To increase the possibility of their meeting, the Buddha wants to arrange the two routes to make their common places as many as possible. Of course, the two routines should still be the shortest paths.

Unfortunately, the Buddha is not good at algorithm, so he ask you for help.
 
Input
There are several test cases in the input. The first line of each case contains the number of places N (1 <= N <= 300) and the number of roads M (1 <= M <= N*N), separated by a space. Then M lines follow, each of which contains three integers a b c, indicating there is a road between place a and b, whose length is c. Please note the roads are undirected. The last line contains four integers A B C D, separated by spaces, indicating the start and end points of Wukong, and the start and end points of Tang Monk respectively. 

The input are ended with N=M=0, which should not be processed.
 
Output
Output one line for each case, indicating the maximum common points of the two shortest paths.
 
Sample Input
6 6
1 2 1
2 3 1
3 4 1
4 5 1
1 5 2
4 6 3
1 6 2 4
0 0
 
Sample Output
3

Hint: One possible arrangement is (1-2-3-4-6) for Wukong and (2-3-4) for Tang Monk. The number of common points are 3.
 

先跑出最短路：如果 dis[a]+edge[a][b]==dis[b] 说明 ab可以可以是最短路上的边。所已用DP 
                            dp[a][b] 从两起点到ab的最优值。
  注意 起点一样，以及重边。
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define clr(f,z) memset(f,z,sizeof(f))
using namespace std;
const int mm=330;
const int oo=0x3f3f3f3f;
class Edge
{
 public:int v,next,w;
};
int g[mm][mm],n,m;
class ShortPath
{
 public:
 int head[mm],edge;Edge e[mm*mm*2];
 void clear()
 {
   clr(head,-1);edge=0;
 }
 void add(int u,int v,int w)
 {
  e[edge].v=v;e[edge].w=w;e[edge].next=head[u];head[u]=edge++;
 }
 bool vis[mm];int id[mm];
 void spfa(int s,int n,int*dis)
 {
   int u,v;
   FOR(i,0,n)dis[i]=oo,vis[i]=0;
   queue<int>Q;
   dis[s]=0;vis[s]=1;Q.push(s);
   while(!Q.empty())
   {
    u=Q.front();Q.pop();vis[u]=0;
    for(int i=head[u];~i;i=e[i].next)
    { v=e[i].v;
      if(dis[v]>dis[u]+e[i].w)
      {
        dis[v]=dis[u]+e[i].w;
        if(!vis[v])
        { Q.push(v);
         vis[v]=1;//++id[v];if(id[v]>=n)return -1;
        }
      }
    }
   }
   //return dis[n];
 }
}sf;
int d1[mm],d2[mm];
int dp[mm][mm];
int DP(int x,int y)
{
  if(dp[x][y]!=-1)return dp[x][y];
  int ret=0;
  if(x==y)///equal point inc
  { ++ret;
    FOR(i,1,n)
    if(d1[i]+g[i][x]==d1[x])
    FOR(j,1,n)
    if(d2[j]+g[j][y]==d2[y])
    ret=max(ret,DP(i,j)+1);
  }
  FOR(i,1,n)
  if(d1[i]+g[i][x]==d1[x])
  ret=max(ret,DP(i,y));
  FOR(i,1,n)
  if(d2[i]+g[i][y]==d2[y])
  ret=max(ret,DP(x,i));
  dp[x][y]=ret;
  return ret;
}
int main()
{
 int a,b,c,d;
 //freopen("data.in","r",stdin);
 while(~scanf("%d%d",&n,&m))
 { if(n==0&&m==0)break;
  sf.clear();
  FOR(i,0,n)FOR(j,0,n)g[i][j]=oo;
  FOR(i,1,m)
  {scanf("%d%d%d",&a,&b,&c);sf.add(a,b,c);sf.add(b,a,c);
   if(c<g[a][b])
   g[a][b]=c,g[b][a]=c;
  }
  scanf("%d%d%d%d",&a,&b,&c,&d);
  sf.spfa(a,n,d1);
  sf.spfa(c,n,d2);
  FOR(i,0,n)FOR(j,0,n)dp[i][j]=-1;
  dp[a][c]=0;
  if(a==c)dp[a][c]=1;
  printf("%d\n",DP(b,d));
 }
}




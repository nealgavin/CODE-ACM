#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define clr(f,z) memset(f,z,sizeof(f))
#define ll(x) (1<<x)
using namespace std;
const int mm = 1e5+9;
const int oo = 1e9;
class Edge
{
	public:
	int v,c,next;
};
int n,m,t;
class ShortPath
{
	public:
	Edge e[mm*4];
	int head[mm*2],edge;
	int pp[12];
	void init()
	{
		edge = 0;
		clr(head,-1);
	}
	void add(int u,int v,int c)
	{
		e[edge].v = v; e[edge].c = c; 
		e[edge].next = head[u]; head[u] = edge++;
	}
	bool vis[mm];
	int dis[12][mm];
	void spfa(int s)
	{
		clr(vis,0);
		clr(dis[s],0x3f);
		queue<int>Q;
		Q.push(pp[s]);
		vis[ pp[s] ] = 1;
		dis[s][ pp[s] ] = 0;
		int u,v;
		while(!Q.empty())
		{
			u = Q.front(); Q.pop();
			vis[u] = 0;
			for(int i=head[u];~i;i=e[i].next)
			{
				v = e[i].v;
				if(dis[s][u] + e[i].c < dis[s][v])
				{
					dis[s][v] = dis[s][u] + e[i].c;
					if(!vis[v])
					{
						Q.push(v);
						vis[v] = 1;
					}
				}
			}
		}

	}

}sp;
int dp[12][1<<12];
int DP()
{
	clr(dp,0x3f);
	int nn=ll(t);
	for(int i=0;i<t;++i)
	dp[i][0] = sp.dis[i][0];

	for(int i=1;i<nn;++i)
	{
		for(int j=0;j<t;++j)
		{
			if(i&ll(j))
			{
				int zz = i^ll(j);
				for(int k=0;k<t;++k)
				{
					dp[j][i] = min(dp[j][i],dp[k][zz]+sp.dis[ k ][ sp.pp[j] ]);

				}
			}
		}
	}
	int ans = oo;
	for(int i=0;i<t;++i)
	ans = min(ans,dp[i][nn-1]+sp.dis[i][0]);//dis to src
	return ans;
}
int main()
{
	int cas,a,b,c;
	while(cin>>cas)
	{
		while(cas--)
		{
			cin>>n>>m;
			sp.init();
			for(int i=0;i<m;++i)
			{
				cin>>a>>b>>c;
				sp.add(a,b,c);
				sp.add(b,a,c);
			}
			cin>>t;
			for(int i=0;i<t;++i)
			cin>>sp.pp[i];
			for(int i=0;i<t;++i)
			sp.spfa(i);
			cout<<DP()<<endl;
		}
	}
	return 0;
}


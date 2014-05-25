/*************************************************************************
	> File Name: hdu-4824-Disk_Schedule.cpp
	> Author: nealgavin
	> Mail: nealgavin@126.com 
	> Created Time: Sun 25 May 2014 07:38:59 PM CST
 ************************************************************************/

#include<iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int mm = 1000+9;
const int oo = 1e9;

int dp[mm][mm],d[mm];
int n;

int dis(int x,int y)
{
    if(d[x] < d[y])
        x^=y^=x^=y;
    int distance = d[x]-d[y];
    return min(distance,360-distance);
}

void init()
{
    dp[1][0] = dis(0,1);
}

int DP()
{
    for(int i=2;i<=n;++i)
    {
        dp[i][i-1] = oo;
        for(int j=0;j<i-1;++j)
        {
            dp[i][i-1] = min(dp[i][i-1],dp[i-1][j]+dis(i,j));
            dp[i][j] = dp[i-1][j] + dis(i,i-1);
        }
    }
    int ans = oo;
    for(int i=0;i<n;++i)
        ans = min(ans,dp[n][i]+dis(i,n));
    return ans;
}
int main()
{
    int cas;
    while(~scanf("%d",&cas))
    {
        while(cas--)
        {
            scanf("%d",&n);
            int x;
            d[0] = 0;
            for(int i=1;i<=n;++i)
                scanf("%d %d",&x,&d[i]);
            init();
            printf("%d\n",DP()+x*800+n*10);
        }
    }
    return 0;
}

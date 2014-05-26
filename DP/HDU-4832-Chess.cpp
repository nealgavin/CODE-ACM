/*************************************************************************
	> File Name: HDU-4832-Chess.cpp
	> Author: nealgavin
	> Mail: nealgavin@126.com 
	> Created Time: Mon 26 May 2014 06:23:18 PM CST
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int mm = 1003;
const int mod = 9999991;

int dp[2][mm][mm]; //  step | point 
int C[mm][mm]; // the method from m take n
int sum[2][mm];
int n,m,x,y,K;

void init()
{
    C[1][1] = 1; C[1][0] = 1;
    for(int i=2;i<mm;++i)
    {
        C[i][0] = 1; C[i][i] = 1;
        for(int j=1;j<i;++j)
        C[i][j] = (C[i-1][j] + C[i-1][j-1])%mod;
    }
}

void DP()
{
    memset(dp,0,sizeof(dp));
    dp[0][0][x] = 1;
    for(int i=1;i<=K;++i)
        for(int j=1;j<=n;++j)
    {
        if(j-1>=1)
        dp[0][i][j] = (dp[0][i][j] + dp[0][i-1][j-1])%mod;
        if(j-2>=1)
        dp[0][i][j] = (dp[0][i][j] + dp[0][i-1][j-2])%mod;
        if(j+1<=n)
        dp[0][i][j] = (dp[0][i][j] + dp[0][i-1][j+1])%mod;
        if(j+2<=n)
        dp[0][i][j] = (dp[0][i][j] + dp[0][i-1][j+2])%mod;
    }
    dp[1][0][y] = 1;
    for(int i=1;i<=K;++i)
        for(int j=1;j<=m;++j)
    {
        
        if(j-1>=1)
        dp[1][i][j] = (dp[1][i][j] + dp[1][i-1][j-1])%mod;
        if(j-2>=1)
        dp[1][i][j] = (dp[1][i][j] + dp[1][i-1][j-2])%mod;
        if(j+1<=m)
        dp[1][i][j] = (dp[1][i][j] + dp[1][i-1][j+1])%mod;
        if(j+2<=m)
        dp[1][i][j] = (dp[1][i][j] + dp[1][i-1][j+2])%mod;
    }

    memset(sum,0,sizeof(sum));
    for(int i=0;i<2;++i)
    for(int j=0;j<=K;++j)
    for(int k=0;k<=(i==0?n:m);++k)
    {
        sum[i][j] = (sum[i][j] + dp[i][j][k])%mod;
    }
}

int getans()
{
    init();
    DP();
    int ans = 0;
    for(int i=0;i<=K;++i)
    ans = (ans + ((long long)C[K][i]*sum[0][i]%mod)*sum[1][K-i]%mod)%mod;
    return ans;
}

int main()
{
    int T;
    while(~scanf("%d",&T))
    {
        for(int ca=1;ca<=T;++ca)
        {
            scanf("%d%d%d%d%d",&n,&m,&K,&x,&y);
            printf("Case #%d:\n%d\n",ca,getans());
        }
    }
    return 0;
}

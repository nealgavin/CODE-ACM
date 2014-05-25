/*************************************************************************
	> File Name: HDU-4834-JZP_Set.cpp
	> Author: nealgavin
	> Mail: nealgavin@126.com 
	> Created Time: Sun 25 May 2014 08:41:19 PM CST
 ************************************************************************/

#include<iostream>
#include <cstdio>
#include <cstring>
#define LL long long

using namespace std;
const int mm = 1e7+4;

LL sum[mm],ans[mm];
LL dp[mm];

void DP()
{
    for(int i=0;i<mm;++i)
        dp[i] = 0;
    for(int i=1;i<mm;i+=2)//all odd numeric
        for(int j=1;j*i<mm;++j)
            ++dp[i*j];//count the number of odd divisor 
}

void init()
{
    DP();
    sum[0] = 0;
    for(int i=1;i<mm;++i)
    {
        sum[i] = sum[i-1] + dp[i];
    }

    ans[0] = 0;
    for(int i=1;i<mm;++i)
        ans[i] += ans[i-1]+sum[i];

}

int main()
{
    int T;
    init();
    while(~scanf("%d",&T))
    {
        for(int ca=1;ca<=T;++ca)
        {
            int x;
            scanf("%d",&x);
            --x;
            printf("Case #%d:\n",ca);
            printf("%I64d\n",ans[x]+x+2);
        }
    }
    return 0;
}


/*************************************************************************
	> File Name: hdu-4833-Best-Financing.cpp
	> Author: nealgavin
	> Mail: nealgavin@126.com 
	> Created Time: Mon 26 May 2014 07:28:57 PM CST
 ************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
const int mm = 5009;
const int nn = 100003;
class Income{
    public:
    int date;
    int earning;
}salry[mm];

class Contral{
    public:
    int start;
    int finish;
    int interest_rates;
}earn[mm];

int T,n,m;
int f[nn],day_in[nn],all_in[nn];
int dp[mm];
map<int,int>mp;
vector<int>vc[2][mm];

int main()
{
    while(~scanf("%d",&T))
    {
        for(int ca=1;ca<=T;++ca)
        {
            scanf("%d %d",&n,&m);
            memset(day_in,0,sizeof(day_in));
            memset(all_in,0,sizeof(all_in));
            for(int i=0;i<n;++i)
            {
                scanf("%d %d",&salry[i].date,&salry[i].earning);
                all_in[ salry[i].date ] += salry[i].earning;
            }
            for(int i=1;i<nn;++i)
                all_in[i] += all_in[i-1];
            for(int i=0;i<m;++i)
                scanf("%d %d %d",&earn[i].start,&earn[i].finish,&earn[i].interest_rates);
            for(int i=0;i<m;++i)
            for(int i=0;i<m;++i)
            {
                f[i] = earn[i].start;
                f[i+m] = earn[i].finish;
            }
            sort(f,f+m+m);
            int pos = unique(f,f+m+m)-f;
            mp.clear();
            for(int i=0;i<pos;++i)
                mp[ f[i] ] = i;
            day_in[ 0 ] = all_in[ f[0] ];
            for(int i=1;i<pos;++i)
                day_in[ i ] = all_in[ f[i] ] - all_in[ f[i-1] ];

            for(int i=0;i<2;++i)
            for(int j=0;j<pos;++j)
                 vc[i][j].clear();
            
            for(int i=0;i<m;++i)
            {
                earn[i].start = mp[ earn[i].start ];
                earn[i].finish = mp[ earn[i].finish ];
                vc[0][ earn[i].start ].push_back(earn[i].finish);
                vc[1][ earn[i].start ].push_back(earn[i].interest_rates);
            }
            memset(dp,0,sizeof(dp));
            for(int i=pos-1;i>=0;--i)
            { 
                dp[i] = dp[i+1];
                int sz = vc[0][i].size();
                for(int j=0;j<sz;++j)
                {
                    dp[i] = max(dp[i],dp[ vc[0][i][j] ]+vc[1][i][j]);
//                    cerr<<"in"<<i<<" "<<dp[i]<<" "<<vc[0][i][j]<<" "<<vc[1][i][j]<<endl;
                }
            }
            long long ans = 0;
            for(int i=0;i<pos;++i)
                ans += (long long)dp[i]*day_in[i];
            printf("Case #%d:\n",ca);
            printf("%.2f\n",(double)ans/100);
        }
    }
    return 0;
}

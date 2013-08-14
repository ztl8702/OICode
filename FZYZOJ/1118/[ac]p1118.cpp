#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>

/*
 * OJ P1118
 * Cost
 */
const int MAXN=32005;
const int MAXM=65;

int n,m;
int w[MAXM];
int cost[MAXM];
int son[MAXM][3]; //count son1 son2
bool acc[MAXM];
int f[MAXN];

namespace Worker
{
int ans=0;
inline void readData()
{
    int r1,r2,r3;
    scanf("%d%d",&n,&m);
    n/=10;
    for (int i=1; i<=m; ++i)
    {
        scanf("%d%d%d",&r1,&r2,&r3);
        r1/=10;
        w[i]=r1*r2;
        cost[i]=r1;
        if (r3)
        {
            son[r3][0]++;
            son[r3][ son[r3][0] ]=i;
            acc[i]=true;
        }
        else
        {
            acc[i]=false;
        }
    }
}

inline int max(int a,int b)
{
    return a>b?a:b;
}

inline bool legal(int x)
{
    return (x>=0)?true:false;
}

inline void process()
{
    int tmp;
    memset(f,-128,sizeof(f));
    f[0]=0;
    for (int i=1; i<=m; ++i)
        if (!acc[i])
        {
            for (int money=n; money>=cost[i]; --money)
            {
                f[money]=max(f[money],f[money-cost[i]]+w[i]);
                if (son[i][0]>=1)
                {
                    tmp=money - cost[son[i][1]] - cost[i];
                    if (legal(tmp))
                        f[money]=max(f[money],f[ tmp ] + w[i] + w[son[i][1]]);
                }
                if (son[i][0]>=2)
                {
                    tmp= money - cost[son[i][2]] - cost[i];
                    if (legal(tmp))
                        f[money]=max(f[money],f[ tmp ] + w[i] + w[son[i][2]]);

                    tmp= money - cost[son[i][1]]- cost[son[i][2]] - cost[i];
                    if (legal(tmp))
                        f[money]=max(f[money],f[ tmp ] + w[i] + w[son[i][1]] + w[son[i][2]]);
                }
                ans=max(f[money],ans);
            }

        }
}

inline void print()
{
    printf("%d\n",ans*10);
}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("p1118.in","r",stdin);
    freopen("p1118.out","w",stdout);
#endif
    Worker::readData();
    Worker::process();
    Worker::print();
    return 0;
}

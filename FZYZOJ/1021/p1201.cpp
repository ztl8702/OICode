#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <iostream>
using std::min;
using std::max;
using std::cout;
using std::endl;
int n,m;
int f[20][300005];
int power2[30], maxtime;

void work()
{
    int i,j;
    for (i=1; i<=maxtime; ++i)
    {
        for (j=1; j<=n-power2[i]+1; ++j)
            f[i][j]=max(f[i-1][j],f[i-1][j+power2[i-1]]);
    }
}

int query(const int l ,const int r)
{
    int i,pi;
    for (i=0; i<=maxtime&&l+power2[i]-1<=r; ++i)
            pi=i;
    return max(f[pi][l],f[pi][r-power2[pi]+1]);
}

void input()
{
    int i;
    scanf("%d",&n);
    for (i=1; i<=n; ++i)
        scanf("%d", &f[0][i]);
    power2[0]=1;
    for (i=1; i<=25; ++i)
    {
        power2[i]=power2[i-1]<<1;
        if (power2[i]>=n)
        {
            maxtime=i;
            break;
        } 
    }
}

void solve()
{
    int i,x,y;
    scanf("%d", &m);
    for (i=1; i<=m; ++i)
    {
        scanf("%d%d", &x, &y);
        cout<<query(x,y)<<endl;
    }
}

int main()
{
    input();
    work();
    solve();
    return 0;
} 

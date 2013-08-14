#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
long long n,m,ans;
long long deg[1000005];
int main()
{
    int i,x,y;
    scanf("%lld%lld", &n, &m);
    for (i=1; i<=m; ++i)
    {
        scanf("%d%d", &x, &y);
        ++deg[x];
        ++deg[y];
    }
    for (i=1; i<=n; ++i)
        ans+=deg[i]*(n-1-deg[i]);
    ans/=2;
    ans=n*(n-1)*(n-2)/2/3-ans;
    printf("%lld\n", ans); while(1);
    return 0;
}

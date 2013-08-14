#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
long long v[205][205],n,m;
long long f[205][205];
int main()
{
    int i,j,k;
    scanf("%lld%lld",&n, &m);
    for (i=1; i<=n; ++i)
        for (j=1; j<=m; ++j)
            scanf("%lld", &v[i][j]);
    for (i=1; i<=n; ++i)
    {
        for (j=0; j<=m; ++j)
        {
            for (k=1; k<=j; ++k)
            {
                f[i][j]=std::max(f[i][j], f[i-1][j-k]+v[i][k]);
            }
        }
    }
    printf("%lld\n", f[n][m]);
    return 0;
}

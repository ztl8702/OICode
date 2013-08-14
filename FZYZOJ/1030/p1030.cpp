#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
int v[105][105];
int f[105][105];
int ans=-(1<<30);
int n,k;
int main()
{
    int i,j;
    memset(f,-64, sizeof(f));
    scanf("%d%d",&k,&n);
    for (i=1; i<=k; ++i)
        for (j=1; j<=n; ++j)
            scanf("%d", &v[i][j]);
    memset(f[0],0, sizeof(f[0]));
    for (i=1; i<=k; ++i)
    {
        f[i][i]=v[i][i]+f[i-1][i-1];
        for (j=i+1; j<=n-k+i; ++j)
            f[i][j]=std::max(f[i][j-1], v[i][j]+f[i-1][j-1]);
    }
    printf("%d",f[k][n]);
    return 0;
}

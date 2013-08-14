#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
int score[55],n,f[110];
int main()
{
    int i,j,k,totDegree;
#ifndef ONLINE_JUDGE
    freopen("p1672.in","r",stdin);
    freopen("p1672.out","w",stdout);
#endif
    scanf("%d",&n);
    memset(f,192,sizeof(f));
    totDegree=2*n-2;
    for (i=1; i<n; ++i)
    {
        scanf("%d",&score[i]);
        f[i]=score[i];
    }
    for (i=2; i<=n; ++i)
        for (j=totDegree; j>=0; --j)
        {  
            f[j]=-1061109568;
            for (k=1; k<=n-1 && k<=j; ++k)
                f[j]=std::max(f[j],f[j-k]+score[k]);
        }
    printf("%d\n",f[totDegree]);
    return 0;
}

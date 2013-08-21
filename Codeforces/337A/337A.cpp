#include <cstdio>
#include <cstdlib>
int main()
{
    int n,m, num[100];
    scanf("%d%d", &n, &m);
    for (int i=1; i<=m; ++i)
        scanf("%d", &num[i]);
    for (int i=1; i<=m-1; ++i)
        for (int j=1; j<=m-i; ++j)
            if (num[j]>num[j+1])
            {
                int tmp=num[j];
                num[j]=num[j+1];
                num[j+1]=tmp; 
            }
    int ans=2147483600;
    for (int i=1; i<=m-n+1; ++i)
    {
        if (num[i+n-1]-num[i]<ans)
            ans=num[i+n-1]-num[i];
    }
    printf("%d\n",ans);
    return 0;
}

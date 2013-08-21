#include <cstdio>
#include <cstring>
#include <cstdlib>
const int MAXN=5005;
int n, num[MAXN];
int f[MAXN];
int main()
{
    scanf("%d",&n);
    for (int i=1; i<=n; ++i)
    {
        scanf("%d",&num[i]);
    }
    f[1]=1;
    int ans=1;
    for (int i=2; i<=n; ++i)
    {
        int maxlen=0;
        for (int j=1; j<i; ++j)
            if (num[j]<num[i] && f[j]>maxlen)
                maxlen=f[j];
        f[i]=maxlen+1;
        if (f[i]>ans)
            ans=f[i];
    }
    printf("%d\n",ans);
    return 0;
}

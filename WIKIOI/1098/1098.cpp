#include <cstdio>
#include <cstring>
#include <cstdlib>
int main()
{
    int n;
    int num[1000],tot=0, average=0;
    scanf("%d", &n);
    for (int i=1; i<=n; ++i)
    {
        scanf("%d", &num[i]);
        tot+=num[i];
    }
    average=tot/n;
    
    int exDelta=0,delta=0, ans=0, step=0;
    for (int i=1; i<=n; ++i)
    {
        exDelta=delta;
        delta+=(num[i]-average);
        if ((exDelta<0 && delta>=0) || (exDelta>0 && delta<=0))
        {
            ans+=step;
            step=0;
        }
        if (delta)
            ++step;
    }
    printf("%d\n", ans);
    return 0;
}

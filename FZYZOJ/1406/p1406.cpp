#include <cstdio>
#include <cstdlib>

#define MAXN 8
#define MAXP 7
#define MAXL 2147480000

int num[MAXN+5];
int n;
inline int readi(int ii)
{
    if (ii<=n)
    {
        int x;
        scanf("%d",&x);
        return x;
    }
    else return (-MAXL);
}

int main()
{
    int p,ll,ans,now;
    scanf("%d",&n);
    num[0] = - MAXL;
    if (n==1)
        ans=1;
    else
    {
        ans=0;
        scanf("%d",&num[1]);
        for (int i=1; i<=n; ++i)
        {
            num[(i+1) & MAXP]=readi(i+1);
            if (num[(i-1)&MAXP]<num[i &MAXP] && num[(i+1)&MAXP]<num[i&MAXP]) ++ans;
        }
        ans=ans*2-1;
        if (num[n&MAXP]<num[(n-1)&MAXP]) ++ans;
    }
    printf("%d",ans);
    return 0;
}

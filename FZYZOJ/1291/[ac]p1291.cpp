#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>

const int MAXN=100005;
struct TNum
{
    long long sum;
    int id;
} sigma[MAXN];
int n;
inline bool sigmaCompare(const TNum &a, const TNum &b)
{
    return (a.sum<b.sum || (a.sum==b.sum && a.id<b.id));
}

inline void input()
{
    int i;
    scanf("%d",&n);
    for (i=1; i<=n; ++i)
    {
        scanf("%lld",&sigma[i].sum);
        sigma[i].sum+=sigma[i-1].sum;
        sigma[i].id=i;
    }
    std::sort(sigma,sigma+n+1,sigmaCompare);
   // for (i=0; i<=n; ++i)
     //   printf("sigma[%d] sum=%lld id=%d\n",i,sigma[i].sum,sigma[i].id);
}

inline void work()
{
    long long delta, minSum=(1LL<<62);
    int i, maxLen=0, len;
    bool zero=false;
    int zLow=MAXN+1, zHigh=0, zMax=0;
    for (i=1; i<=n; ++i)
    {
        if (!zero)
        {
            len=abs(sigma[i].id-sigma[i-1].id);
            delta=abs(sigma[i].sum-sigma[i-1].sum);
            if (delta<minSum || (delta==minSum && len>maxLen))
            {
                minSum=delta;
                maxLen=len;
            }
            //printf("i=%d,l=%d,delta=%lld, minSum=%lld\n",i,len,delta,minSum);
            if (minSum==0)
                zero=true;
        }
        if (zero)
        {
            if (sigma[i].sum==sigma[i-1].sum)
            {
                zLow=sigma[i-1].id<zLow?sigma[i-1].id:zLow;
                zHigh=sigma[i-1].id>zHigh?sigma[i-1].id:zHigh;
                zMax=(zHigh-zLow)>zMax?zHigh-zLow:zMax;
                if (sigma[i].sum!=sigma[i+1].sum||i==n)
                {
                    zLow=sigma[i].id<zLow?sigma[i].id:zLow;
                    zHigh=sigma[i].id>zHigh?sigma[i].id:zHigh;
                    zMax=(zHigh-zLow)>zMax?zHigh-zLow:zMax;          
                    zLow=MAXN+1; zHigh=0;
                }
            }
        }
    }
    if (zero)
        printf("0\n%d\n",zMax);
    else
        printf("%lld\n%d\n",minSum,maxLen);
}

int main()
{
    input();
    work();
    return 0;
}

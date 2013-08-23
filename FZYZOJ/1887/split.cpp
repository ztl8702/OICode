#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
const int MAXN=100005;
const int MOD=1000000009;
int sigma[MAXN];
long long sum[MAXN];
int n;

namespace TLA
{
    inline int lowbit(const int x)
    {
        return x&(-x);
    }

    inline void add(int pos, const int value)
    {
        while (pos<=n)
        {
            sigma[pos]+=value;
            sigma[pos]%=MOD;
            pos+=lowbit(pos);
        }
    }

    inline int getSum(int pos)
    {
        int ans=0;
        while (pos>0)
        {
            ans=(ans+sigma[pos])%MOD;
            pos-=lowbit(pos);
        }
        return ans;
    }
}

namespace DIS //discretization
{
    typedef struct item
    {
        long long value;
        long long *origin;
    } Item;

    Item tmp[MAXN];
    bool cmpItem(const Item a, const Item b)
    {
        return (a.value<b.value);
    }
    long long zero=0;
    void workDIS()
    {
        for (int i=1; i<=n; ++i)
        {
            tmp[i].value=sum[i];
            tmp[i].origin=&sum[i];
        }

        tmp[n+1].value=0LL;
        tmp[n+1].origin=&zero;

        std::sort(tmp+1,tmp+n+2,cmpItem);
        int count=0;
        for (int i=1; i<=n+1; ++i)
        {
            if (i==1 || (tmp[i].value!=tmp[i-1].value))
                ++count;
            *(tmp[i].origin)=(long long)count;
        }
    }
}

int f[MAXN];

void solve()
{
    int start;
  /*  for (start=1; start<=n && sum[start]<DIS::zero; ++start)
    {
        f[start]=0;
    }
    f[start]=1;
    printf("start=%d\n",start);
    TLA::add((int)sum[start],f[start]);*/
    for (int i=1; i<=n; ++i)
    {
        f[i]=TLA::getSum((int)sum[i])%MOD;
        if (sum[i]>=DIS::zero)
            ++f[i];
        TLA::add((int)sum[i],f[i]);
        //printf("f[%d]=%d\n",i,f[i]);
    }
    printf("%d\n", f[n]%MOD);
}

int main()
{
    scanf("%d",&n);
    int a;
    for (int i=1; i<=n; ++i)
    {
        scanf("%d",&a);
        sum[i]=sum[i-1]+a;
    }
    DIS::workDIS();
    solve();
    return 0;
}

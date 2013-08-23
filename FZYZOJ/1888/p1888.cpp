#include <cstdio>
#include <cstring>
#include <cstdlib>
const int MAXN=1000000+5;
long long f[MAXN];
long long Pi[MAXN], Rpi[MAXN];
bool vst[MAXN];
int n;
long long p;

long long power(const long long lower, const long long upper)
{
    if (upper==0)
        return 1;
    long long tmp=power(lower,upper>>1);
    if (upper%2)
    {
        return (((tmp*tmp)%p)*lower)%p;
    }
    else
    {
        return (tmp*tmp)%p;
    }
}

int powerUp(const int x)
{
    int tmp=1;
    while ((tmp)<x)
        tmp<<=1;
    return tmp;
}


long long C(const long long lower, long long upper)
{
    if (lower-upper<upper)
        upper=lower-upper;
    long long ans=Pi[lower];
    ans=(ans*Rpi[lower-upper])%p;
    ans=(ans*Rpi[upper])%p;
    return ans;
}

long long dp(const int size)
{
    if (vst[size])
        return f[size];
    int ptwo=powerUp(size);
    int delta=ptwo-size-1;
    int left,right;
    if (delta<=(ptwo>>2))
    {
        left=(size+delta-1)>>1;
        right=size-left-1;
    }
    else
    {
        left=((size+delta-1)>>1)-(delta-(ptwo>>2));
        right=size-left-1;
    }
    f[size]=(C(size-1,left)*dp(left))%p;
    f[size]= (f[size]*dp(right))%p;
    vst[size]=true;
    return f[size];
}

void input()
{
    scanf("%d%lld", &n, &p);
    vst[1]=true;
    vst[2]=true;
    f[1]=f[2]=1LL;
    Rpi[0]=1;
    Pi[0]=1;
    long long Ri;
    for (int i=1; i<=n; ++i)
    {
        Ri=power(i,p-2);
        Pi[i]=(Pi[i-1]*i)%p;
        Rpi[i]=(Rpi[i-1]*Ri)%p;
    }
    
}

int main()
{
    input();
    printf("%lld\n",dp(n));
    return 0;
}

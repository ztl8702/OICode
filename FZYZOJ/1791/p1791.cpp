#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
const int MAXN=1000005;
int n;
int q[MAXN], tail=0;
long long ans;
int main()
{
    int i, rd;
    scanf("%d", &n);
    for (i=1; i<=n; ++i)
    {
        scanf("%d", &rd);
        while (tail>=1 && q[tail]<rd)
        {
            ans+=std::min(rd,tail>1?q[tail-1]:2147483600);
            --tail;
        }
        ++tail;
        q[tail]=rd;
    }
    for (i=1; i<=tail-1; ++i)
        ans+=q[i];
    printf("%lld\n", ans); 
    return 0;
}

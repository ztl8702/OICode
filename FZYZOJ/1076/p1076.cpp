#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
int n,m;
long long sum[200000], pos[200000];
long long ans=-(1LL<<60);
int main()
{ 
    int i;
    long long now;
    scanf("%d%d", &n, &m);
    int QHead=0, QTail=1;
    for (i=1; i<=n; ++i)
    {
        scanf("%lld" ,&now);
        sum[i]=sum[i-1]+now;
        while (QHead<QTail && pos[QHead+1]<i-m)
            ++QHead;
        while (QHead<QTail && sum[i]<=sum[pos[QTail]])
            --QTail;
        ++QTail;
        pos[QTail]=i;
        if (sum[i]-sum[pos[QHead+1]]>ans)
            ans=sum[i]-sum[pos[QHead+1]];
    }
    cout<<ans<<endl;
    return 0;
}

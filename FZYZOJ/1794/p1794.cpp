#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
const int RANGE=1000000;
bool isp[RANGE+5];
int p[100000], pcount;
void getPrime()
{
    int i, j, tmp;
    for (i=2; i<=RANGE; ++i)
    {
        if (!isp[i])
            p[++pcount]=i;
        for (j=1, tmp=i*p[j]; j<=pcount && tmp<=RANGE; ++j, tmp=i*p[j])
            isp[tmp]=true;
    }
}
bool search(const long long target)
{
    int l=1, r=pcount, mid;
    long long tmp;
    while (l<=r)
    {
        mid=(l+r)>>1;
        tmp=(long long)p[mid]*p[mid];
        if (tmp==target)
            return true;
        else if (target>tmp)
            l=mid+1;
        else
            r=mid-1;
    }
    return false;
}
int n;
long long query;

int main()
{
    getPrime();
    scanf("%d", &n);
    for (int i=1; i<=n; ++i)
    {
        scanf("%lld", &query);
        puts(search(query)?"YES":"NO");
    }
    return 0;
}

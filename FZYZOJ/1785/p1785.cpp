#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
const int P=1000000009;
int n,T,f[500005];
int main()
{
    long long tmp;
    f[1]=2;
    f[2]=3;
    for (int i=3; i<=500000; ++i)
    {
        tmp=(long long)f[i-1]+(long long)f[i-2];
        f[i]=tmp % P;
    }
    scanf("%d", &T);
    for (int i=1; i<=T; ++i)
    {
        scanf("%d", &n);
        printf("%d\n", f[n]);
    }
    return 0;
}

#include <cstdio>
#include <cstdlib>

int main()
{
    long long q,p;
    scanf("%lld%lld",&p,&q);
    printf("%lld\n",(p-1)*(q-1)/4LL + (p==q)*(p-1)/2LL);
    return 0;
}

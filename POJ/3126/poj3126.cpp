#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
bool prime[10005];

void makePrimes()
{
    memset(prime,true, sizeof(prime));
    prime[0]=prime[1]=false;
    int i,j;
    for (i=2; i<=10000; ++i)
    {
        for (j=i+i; j<=10000; j+=i)
            prime[j]=false;
    }
}
int Q[10005];
bool vst[10005];
int dst[10005],parent[10005];
void workOnce()
{
    int QHead=0,QTail=0, start, target;
    scanf("%d%d", &start, &target);
    memset(vst,false, sizeof(vst));
    memset(dst, 63, sizeof(dst));
    ++QTail;
    Q[QTail]=start;
    vst[start]=true;
    dst[start]=0;
    int i,x,now, next;
    while (QHead<QTail)
    {
        now=Q[++QHead];
        for (i=1; i<=1000; i*=10)
            for (x=0; x<10; ++x)
            {
                next=now+(x-(now%(i*10))/i)*i;
                if (next>999 && !vst[next] && prime[next])
                {
                    Q[++QTail]=next;
                    vst[next]=true;
                    dst[next]=dst[now]+1;
                    parent[next]=now; 
                }
            }
    }
    dst[target]>10000?printf("Impossible\n"):printf("%d\n", dst[target]);
}
int main()
{
    makePrimes();
    int testcase;
    scanf("%d", &testcase);
    for (;testcase; --testcase)
        workOnce();
    return 0;
}

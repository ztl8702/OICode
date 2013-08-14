#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;
const double INFPRC=1e+20;
double D1,C,V,P0;
int n;
struct TStation
{
    double d,p;
} sta[1005];

inline bool cmpStation(const TStation &a, const TStation &b)
{
    return a.d<b.d;
}

inline void input()
{
    scanf("%lf%lf%lf%lf%d",&D1,&C,&V,&P0,&n);
    for (int i=1; i<=n; ++i)
    {
        scanf("%lf%lf",&sta[i].d,&sta[i].p);
        sta[i].d/=V;
    }
    ++n;
    sta[n].d=0;
    sta[n].p=P0;
    std::sort(sta+1,sta+1+n,cmpStation);
    ++n;
    sta[n].d=D1/V;
    sta[n].p=-10000.0;
    /*for (int i=1; i<=n; ++i)
        printf("#%d:pos=%.2lf pri=%.2lf\n",i,sta[i].d,sta[i].p);
    */
}

inline double work()
{
    int i,j,next;
    bool cheaper;
    double left=0,need,fee=0;
    i=1;
    while (i<n)
    {
        if (sta[i+1].d-sta[i].d>C) 
            return -1;
        cheaper=false;
        for (j=i+1; j<=n && sta[j].d-sta[i].d<=C; ++j)
        {
            next=j;
            if (sta[j].p<=sta[i].p)
            {
                cheaper=true;
                break;
            }
        }
        if (cheaper)
        {
            need=max(0.0,(sta[next].d-sta[i].d)-left);
            fee+=sta[i].p*need;
            left+=need;
        }
        else
        {
            need=C-left;
            fee+=sta[i].p*need;
            left+=need;
        }
        left-=sta[next].d-sta[i].d;
        i=next;
    }
    return fee;
}

int main()
{
    input();
    double ans=work();
    if (ans<0)
        printf("No Solution\n");
    else
        printf("%.2lf\n",work());
  //  system("pause");
    return 0;
}

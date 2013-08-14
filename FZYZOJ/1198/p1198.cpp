#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <vector>
const double INFPRC=1e+20;
double D1,C,D2,P0;
int n;
struct TStation
{
    double d,p;
} sta[1005];
struct TOil
{
    int sta;
    double price,used,pos;
} oil[1005];
int ocount;

inline bool cmpOil(const TOil &a, const TOil &b)
{
    return a.price<b.price;
}

inline bool cmpStation(const TStation &a, const TStation &b)
{
    return a.d<b.d;
}

inline void input()
{
    scanf("%lf%lf%lf%lf%d",&D1,&C,&D2,&P0,&n);
    for (int i=1; i<=n; ++i)
        scanf("%lf%lf",&sta[i].p,&sta[i].d);
    ++n;
    sta[n].d=0;
    sta[n].p=P0;
    std::sort(sta+1,sta+1+n,cmpStation);
    ++n;
    sta[n].d=D1;
    sta[n].p=0;
    for (int i=1; i<=n; ++i)
        printf("#%d:pos=%.2lf pri=%.2lf\n",i,sta[i].d,sta[i].p);
}

inline void addOilType(const int staid)
{
    ++ocount;
    oil[ocount].price=sta[staid].p;
    oil[ocount].used=0;
    oil[ocount].pos=sta[staid].d;
    oil[ocount].sta=staid;
    std::sort(oil+1,oil+ocount+1,cmpOil);
}

inline double useOil(const double need,const double pos)
{
    int i,disabled=0;
    double require=need,fee=0; 
    std::sort(oil+1,oil+ocount+1,cmpOil);
    i=1;
    while (require>0 && i<=ocount)
    {
        if (oil[i].used<C  && pos-oil[i].pos<=C*D2)
        {
            if (C-oil[i].used>=require)
            {
                oil[i].used+=require;
                fee+=oil[i].price*require;
                printf(" use #%d*%.2lfL;",oil[i].sta,require);
                require=0;
            }
            else
            {
                fee+=oil[i].price*(C-oil[i].used); 
                printf(" use #%d*%.2lfL;",oil[i].sta,(C-oil[i].used));
                require-=C-oil[i].used; 
                oil[i].used=C;
            }
            if (oil[i].used>=C)
            {
                ++disabled;
                oil[i].price=INFPRC;
            }
        }
        else
        {
            ++disabled;
            oil[i].price=INFPRC;
        }
        ++i;
    }
    std::sort(oil+1,oil+ocount+1,cmpOil);
    ocount-=disabled;
    return (require>0)?-1:fee;
}

inline void work()
{
    int i,j;
    double ans=0,tmp;
    addOilType(1);
    for (i=2; i<=n; ++i)
    {
        printf("Station %d->%d: ",i-1,i);
        tmp=useOil((sta[i].d-sta[i-1].d)/D2,sta[i].d);
        if (tmp<0)
        {
            printf("No Solution\n");
            return;
        }
        else
            ans+=tmp;
        addOilType(i);
        printf("\n");
    }
    printf("%lf\n",ans);
}
int main()
{
    input();
    work();
    system("pause");
    return 0;
}

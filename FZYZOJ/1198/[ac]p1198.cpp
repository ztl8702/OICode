#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cmath>
const int MAXN=1005;
const char ERR_MSG[]="No Solution\0";
double C, D1, D2;
struct TStation
{
    double price, dis;
} sta[MAXN];
inline bool StationCompare(const TStation &a, const TStation &b)
{
    return a.dis<b.dis;
}
int N;
struct TOilTank
{
    double Q[2005],V[2005];
    int head,tail;
    double volume;
    inline void refill(const double price)
    {
        while (head<tail && Q[tail]>price)
        {
            volume-=V[tail];
            --tail;
        }
        if (volume<C)
        {
            ++tail;
            Q[tail]=price;
            V[tail]=C-volume;
            volume=C;
        }
        /*printf("[");
        for (int i=head+1; i<=tail; ++i)
            printf("%lf(%lf L),",Q[i], V[i]);
        printf("]");*/
    }
    
    inline double use(double v)
    {  
        double cost=0.0;
        while (head<tail && v)
        {
            if (V[head+1]>v)
            {
                V[head+1]-=v;
                volume-=v;
                cost+=v*Q[head+1];
                v=0;
            }
            else
            {
                cost+=V[head+1]*Q[head+1];
                volume-=V[head+1];
                v-=V[head+1];
                ++head;
            }
        }
        return cost;
    }
} tank;

inline void input()
{
    int i;
    scanf("%lf%lf%lf%lf%d\n",&D1,&C,&D2,&sta[0].price,&N);
    for (i=1; i<=N; ++i)
    {
        scanf("%lf%lf",&sta[i].dis, &sta[i].price);
        sta[i].dis/=D2;
    }
    sta[N+1].dis=D1/D2;
    sta[N+1].price=0;
    std::sort(sta+1, sta+N+1, StationCompare);
}

inline void work()
{
    int i;
    double ans=0.0;
    tank.head=tank.tail=0;
    tank.refill(sta[0].price);
    //for (i=0; i<=N+1; ++i)
      //  printf("%lf %lf\n",sta[i].dis, sta[i].price);
    for (i=1; i<=N+1; ++i)
    {
        if (sta[i].dis-sta[i-1].dis>C)
        {
            puts(ERR_MSG);
            exit(0);
        }
        ans+=tank.use(sta[i].dis-sta[i-1].dis);
        tank.refill(sta[i].price);
    }
    printf("%.2lf\n",ans);
}

int main()
{
    input();
    work();
    
    return 0;
}

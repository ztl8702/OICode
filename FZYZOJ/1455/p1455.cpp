#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cmath>
double pi=atan2(0,-1);
using namespace std;
struct TPoint
{
    bool empty;
    double x, y;
} a,b,c,d;
int T;


inline TPoint getCross()
{
    TPoint p;
    p.empty=true;
    double k1,k2,b1,b2, crossx, crossy;
    if (a.x==b.x && c.x==d.x)
        return p;
    else if (a.x==b.x)
    {
        k2=(c.y-d.y)/(c.x-d.x);
        b2=c.y-k2*c.x;
        crossy=k2*a.x+b2;
        if (min(a.y,b.y)<=crossy &&  crossy<=max(a.y,b.y) && min(c.x, d.x)<=a.x && a.x<=max(c.x,d.x))
        {
            p.empty=false;
            p.x=a.x;
            p.y=crossy;
            return p;
        }
    }
    else if (c.x==d.x)
    {
        k1=(a.y-b.y)/(a.x-b.x);
        b1=a.y-k1*a.x;
        crossy=k1*c.x+b1;
        if (min(c.y,d.y)<=crossy && crossy<=max(c.y,d.y) && min(a.x, b.x)<=c.x && c.x<=max(a.x,b.x))
        {
            p.empty=false;
            p.x=c.x;
            p.y=crossy;
            return p;
        }
    }
    else
    {
        k1=(a.y-b.y)/(a.x-b.x);
        b1=a.y-k1*a.x;
        k2=(c.y-d.y)/(c.x-d.x);
        b2=c.y-k2*c.x;
        crossx=(b2-b1)/(k1-k2);
        crossy=k1*crossx+b1;
        if (min(a.y,b.y)<=crossy &&  crossy<=max(a.y,b.y) && min(a.x, b.x)<=crossx && crossx<=max(a.x,b.x))
            if (min(c.y,d.y)<=crossy &&  crossy<=max(c.y,d.y) && min(c.x, d.x)<=crossx && crossx<=max(c.x,d.x))
            {
                p.empty=false;
                p.x=crossx;
                p.y=crossy;
                return p;
            }
    }
    return p;
}

inline double solve()
{
    scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y, &d.x, &d.y);
    TPoint pp=getCross(), circle[4]={a,b,c,d};
    double angle[4];
    if (pp.empty)
        return 0.0;
    for (int i=0; i<4; ++i)
    {
        circle[i].x-=pp.x;
        circle[i].y-=pp.y;
        angle[i]=atan2(circle[i].y, circle[i].x);
    }
    //puts("FUCK0");
    //printf("pp(%lf, %lf) \n", pp.x, pp.y);
    for (int i=0; i<=2; ++i)
        for (int j=i+1; j<=3; ++j)
        {
            if (0<angle[i] && angle[i]<pi && 0<angle[j] && angle[j]<pi)
            {
                int upper,lower;
                upper=(circle[i].y>circle[j].y)?i:j;
                lower=(circle[i].y>circle[j].y)?j:i;
                if (angle[upper]>pi/2 && angle[lower]>pi/2)
                {
                    if (angle[upper]<angle[lower] && circle[upper].x>circle[lower].x)
                        continue;
                    if (angle[upper]>angle[lower] && circle[upper].x<circle[lower].x)
                        continue;
                }
                if (angle[upper]<pi/2 && angle[lower]<pi/2)
                {
                    if (angle[upper]<angle[lower] && circle[upper].x<circle[lower].x)
                        continue;
                    if (angle[upper]>angle[lower] && circle[upper].x>circle[lower].x)
                        continue;
                }

                if (circle[upper].x==0)
                    return fabs(circle[lower].y)*fabs(circle[lower].x)*0.5;
                else
                {
                    double cx=(circle[upper].x)/(circle[upper].y)*(circle[lower].y);
                    return fabs(circle[lower].y)*fabs(cx-circle[lower].x)*0.5;
                }
            }
        }
    return 0;
}

int main()
{
    freopen("p14551.in","r", stdin);
    freopen("p1455.out","w",stdout);
    cin>>T;
    for (int i=1; i<=T; ++i)
        printf("%.2lf\n",solve());
    return 0;
}

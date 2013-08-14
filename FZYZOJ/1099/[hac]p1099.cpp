/*
 *
 * P1099 -- cake
 * @param
 * @return
 *
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
const int MAXLL=~(1<<31);
int m,n;
int ans;

void dfs(const int floor,const int mh,const int mr,const int vleft,const int s)
{
    if (floor==0)
    {
        if ((s<ans)&&(vleft==0)) ans=s;
        return;
    }
    if (s>=ans) return;
    if (s+vleft*2/(mr-1)>=ans) return;
    if ((mh-1)*(mr-1)*(mr-1)*floor<vleft) return;
    if (vleft==0) return;
    if (floor==1)
    {
        for (int r=1; r<mr; ++r)
        {
            int nowS=r*r;
            if (vleft % nowS != 0) continue;
            int h=(int)vleft / nowS;
            if (h>=mh) continue;
            dfs(floor-1,h,r,0,s+2*r*h);
        }
    }
    else
        for (int r=floor; r<mr; ++r)
        {
            int nowS=r*r;
            if (nowS>=vleft) break;
            for (int h=floor; h<mh&&(h*nowS<vleft); ++h)
            {
                dfs(floor-1,h,r,vleft-nowS*h,s+2*r*h);
            }
        }
}

void calcbase()
{
    for (int r=m; r<=100; ++r)
    {
        int nowS=r*r;
        if (nowS>n) break;
        for (int h=m; (h*nowS<=n); ++h)
        {
            if (nowS*h>n) break;
            dfs(m-1,h,r,n-h*nowS,2*r*h+nowS);
        }
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    ans=MAXLL;
    calcbase();
    printf("%d\n",ans==MAXLL?0:ans);
    return 0;

}

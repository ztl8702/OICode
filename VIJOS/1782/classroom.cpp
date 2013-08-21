#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
const int MAXN=1000005;
int n,m;
int r[MAXN], d[MAXN], startDate[MAXN], endDate[MAXN];
int used[MAXN];

inline bool fill(const int prev, const int curr)
{
    bool err=false;
    if (prev<curr)
    {
        for (int i=prev+1; i<=curr; ++i)
        {
            used[startDate[i]]+=d[i];
            used[endDate[i]+1]-=d[i];
        }
    }
    else if (curr<prev) //Undo
    {
        for (int i=curr+1; i<=prev; ++i)
        {
            used[startDate[i]]-=d[i];
            used[endDate[i]+1]+=d[i];
        }
    }
    int tmp=0;
    for (int i=1; i<=n; ++i)
    {
        tmp+=used[i];
        if (tmp>r[i])
        {
            err=true;
            break;
        }
    }
    return err;
}

int solve() //find out the maximum number that can be satisfied.
{
    int Left=0, Right=m, Mid=(Left+Right)>>1;
    int Last=0;
    while (Left < Right)
    {
        Mid=(Left+Right+1)>>1;
        bool res=fill(Last, Mid);
        Last=Mid;
  //     printf("l=%d r=%d m=%d e=%d\n", Left,Right,Mid,res);
        if (res)
            Right=Mid-1;
        else 
            Left=Mid;
        
    }
    return Left;
}

int main()
{
    freopen("classroom.in","r",stdin);
    freopen("classroom.out","w",stdout);
    scanf("%d%d",&n, &m);
    for (int i=1; i<=n; ++i)
        scanf("%d",&r[i]);
    for (int i=1; i<=m; ++i)
        scanf("%d%d%d", &d[i],&startDate[i], &endDate[i]);
    int ll=solve();
    if (ll==m)
        printf("0\n");
    else
    {
        printf("-1\n");
        printf("%d\n",ll+1);
    }
 //   system("pause");
    return 0;   
}

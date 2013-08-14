#include <cstdio>
#include <cstring>
#include <cstdlib>
const int MAXN=1000;
const int INFINITY=2147483600;
int n;
int p[MAXN+5][MAXN+5];
bool intree[MAXN];
int dist[MAXN]; //当前已经加入MST的所有点 到（MST外的）点j的最小边权 
inline int getmin(int a,int b) {return a<b?a:b;}
int main()
{
    int i,j,k,Ans=0,min,mini,now;
    #ifndef ONLINE_JUDGE
    freopen("p1420.in","r",stdin);
    freopen("p1420.out","w",stdout);
    #endif
    scanf("%d",&n);
    for (i=1;i<=n;++i)
    {
        scanf("%d",&p[i][n+1]);
        p[n+1][i]=p[i][n+1];
    }
    for (i=1;i<=n;++i)
       for (j=1;j<=n;++j)
            scanf("%d",&p[i][j]);    
    intree[n+1]=true;
    for (i=1;i<=n;++i)
        dist[i]=p[n+1][i];
    
    for (i=1;i<n+1;++i)
    {
        min=INFINITY; mini=0;
        for (j=1;j<=n+1;j++)
            if (!intree[j] && dist[j]<min)
            {
                min=dist[j];
                mini=j;
            }
        if (mini!=0)
        {
            Ans+=min;
            intree[mini]=true;
            for (j=1;j<=n;++j) 
                dist[j]=getmin(dist[j],p[j][mini]);
        }
    }
    printf("%d",Ans);
    return 0;
}

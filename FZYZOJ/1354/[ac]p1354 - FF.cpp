/*
 * FZYZ OJ P1354
 * Maximum Flow - FF
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define FILLCHAR(ARR,VAL) memset(ARR,VAL,sizeof(ARR))
#define DEBUG(MSG) printf("[DEBUG]%s\n",MSG)
const int INFINITY = 2100000000;
const char ERRMSG[] = "No Solution!\0";
int g[1000][1000],oppo[1000],fsum;
int m,n;
inline int min(int a,int b) {return a<b?a:b;}

namespace NetworkFlow
{
    int Source,Sink,Count;
    int prev[1000000];
    bool findAugmentingPath(int now)
    {
        if (now==Sink) 
            return true;
        for (int i=1;i<=Count;++i)
            if (prev[i]<0 && g[now][i]>0)
            {
                prev[i]=now;
                if (findAugmentingPath(i)) return true;
            } 
        return false;
    }
    
    inline void increaseFlow()
    {
        int d=INFINITY,i;
        for (i=Sink;prev[i]>0;i=prev[i])
            d=min(d,g[prev[i]][i]);
        for (i=Sink;prev[i]>0;i=prev[i])
        {
            g[prev[i]][i]-=d;
            g[i][prev[i]]+=d;
        }
        fsum+=d;
    }
    
    inline void FF()
    {
        FILLCHAR(prev,-1);
        prev[Source]=0;
        while (findAugmentingPath(Source))
        {
            increaseFlow();
            FILLCHAR(prev,-1);
            prev[Source]=0;
        }
        
    }
}

int main()
{
    int i,j,a,b;
    #ifndef ONLINE_JUDGE
    freopen("p1354.in","r",stdin);
    freopen("p1354.out","w",stdout);
    #endif
    scanf("%d%d",&m,&n);
    {
        using namespace NetworkFlow;
        Source=m+n+1;
        Sink=m+n+2;
        Count=m+n+2;
    }
    fsum=0;    
    FILLCHAR(g,0);
    for (i=1;i<=m;++i)
        g[NetworkFlow::Source][i]=1;
    for (i=m+1;i<=m+n;++i)
        g[i][NetworkFlow::Sink]=1;
    for (;;)
    {
        scanf("%d%d",&a,&b);
        if (a==-1&&b==-1)
            break;
        g[a][b+m]=1;
    }
    FILLCHAR(oppo,0);
    NetworkFlow::FF();
    printf("%d\n",fsum);
    for (i=1;i<=m;++i)
    {
        for (j=m+1;j<=m+n;++j)
            if (g[i][j]==0&&g[j][i]==1)
            {
                printf("%d %d\n",i,j-m);
                break;
            }
    }
    return 0;
}

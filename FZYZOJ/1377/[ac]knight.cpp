#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
const int MAXN=205;
const int MAXP=MAXN*MAXN;
const int MAXM=4000000;
const int drt[8][2]= {{+1,+2},{+2,-1},{+2,+1},{+1,-2},
    {-1,-2},{-2,-1},{-2,+1},{-1,+2}
};
const int INF = 2147483600;
int n,m;
int indexp[MAXN][MAXN];
bool blocked[MAXN][MAXN];
int Tot=0;
struct TEdge
{
    int startv, endv, cap, next;
} edges[MAXM];
int head[MAXP], ecount, fsum=0;
namespace Network
{
    int source, sink, d[MAXP], stack[MAXP], gap[MAXP], nowhead[MAXP], preEdge[MAXM];
    inline void addedge(int u, int v, int c)
    {
        ++ecount;
        edges[ecount].startv=u;
        edges[ecount].endv=v;
        edges[ecount].next=head[u];
        edges[ecount].cap=c;
        head[u]=ecount;
    }

    inline void sap()
    {
        int i, x=source, MinFlow=INF, mindis, mini, changedindex;
        bool flag;
        gap[0]=Tot;
        memcpy(nowhead,head,sizeof(head));
        while (d[source]<Tot)
        {
loop:
            flag=false;
            stack[x]=MinFlow;
            for (i=nowhead[x]; i; i=edges[i].next)
            {
                if (edges[i].cap && d[x]==d[edges[i].endv]+1)
                {
                    flag=true;
                    nowhead[x]=i;
                    MinFlow=std::min(MinFlow,edges[i].cap);
                    x=edges[i].endv;
                    preEdge[x]=i;
                    if (x==sink)
                    {
                        fsum += MinFlow;
                        for (; x!=source; x=edges[preEdge[x]].startv)
                        {
                            edges[preEdge[x]].cap   -= MinFlow;
                            edges[preEdge[x]^1].cap += MinFlow;
                        }      
                        MinFlow=INF;
                    }
                    goto loop;
                }// if
            }// for
            if (!flag)
            {
                mindis=Tot+1;
                mini=0;
                for (i=head[x]; i; i=edges[i].next)
                    if (edges[i].cap && d[edges[i].endv]<mindis)
                    {
                        mindis=d[edges[i].endv];
                        mini=i;
                    }
                nowhead[x]=mini;
                --gap[d[x]];
                changedindex=d[x];
                d[x]=mindis+1;
                ++gap[d[x]];
                if (gap[changedindex]==0)
                    break;
                if (x!=source)
                {
                    x=edges[preEdge[x]].startv;
                    MinFlow=stack[x];
                }
            }
        }// while
    }

}
inline void Input()
{
    using namespace Network;
    int i, x, y, nx, ny;
    bool flag;
    scanf("%d%d",&n,&m);
    for (x=1; x<=n; ++x)
        for (y=1; y<=n; ++y)
            indexp[x][y]=++Tot;
    for (i=1; i<=m; ++i)
    {
        scanf("%d%d",&x,&y);
        blocked[x][y]=true;
    }
    source=n*n+1;
    sink=n*n+2;
    ecount=1;
    for (x=1; x<=n; ++x)
        for (y=1; y<=n; ++y)
            if (!blocked[x][y])
            {
                if ((x+y)%2==0)
                {
                    addedge(source,indexp[x][y],1);
                    addedge(indexp[x][y],source,0);
                    for (i=0; i<8; ++i)
                    {
                        nx=x+drt[i][0];
                        ny=y+drt[i][1];
                        if (nx>0&&nx<=n&&ny>0&&ny<=n&&!blocked[nx][ny])
                        {
                            addedge(indexp[x][y],indexp[nx][ny],1);
                            addedge(indexp[nx][ny],indexp[x][y],0);
                        }
                    }
                }
                else
                {
                    addedge(indexp[x][y],sink,1);
                    addedge(sink,indexp[x][y],0);
                }
            }
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
#endif
    Input();
    Network::sap();
    printf("%d\n",n*n-fsum-m);
    return 0;
}

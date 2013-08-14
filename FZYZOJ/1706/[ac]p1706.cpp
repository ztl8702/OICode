#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define FILLCHAR(A,X) memset(A,X,sizeof(A))
int n,m;
struct {int endv,next;} edges[5000],edgesR[5000];
int ecount=0,ecountR=0,head[105],headR[105];
bool vst[105];
int visited=0;
void findWinner(const int now)
{
    if (!vst[now])
    {
        ++visited;
        vst[now]=true; 
        for (int p=head[now]; p; p=edges[p].next)
            findWinner(edges[p].endv);
    }
}
void findLoser(const int now)
{
    if (!vst[now])
    {
        ++visited;
        vst[now]=true;
        for (int p=headR[now]; p; p=edgesR[p].next)
            findLoser(edgesR[p].endv);
    }
}
inline void addEdge(const int u, const int v)
{
    ++ecount;
    edges[ecount].endv=v;
    edges[ecount].next=head[u];
    head[u]=ecount;
}
inline void addEdgeR(const int u, const int v)
{
    ++ecountR;
    edgesR[ecountR].endv=v;
    edgesR[ecountR].next=headR[u];
    headR[u]=ecountR;
}
int main()
{
    int i,a,b,ans=0,tmp;
#ifndef ONLINE_JUDGE
    freopen("P1706.in","r",stdin);
    freopen("P1706.out","w",stdout);
#endif
    scanf("%d%d",&n,&m);
    for (i=1; i<=m; ++i)
    {
        scanf("%d%d",&a,&b);
        addEdge(b,a);
        addEdgeR(a,b);
    }
    for (i=1; i<=n; ++i)
    {
        tmp=visited=0;
        FILLCHAR(vst,false);
        findWinner(i);
        tmp+=visited;
        visited=0;
        FILLCHAR(vst,false);
        findLoser(i);
        tmp+=visited;
        if (tmp-1==n)
            ++ans;
    }
    printf("%d\n",ans);
    return 0;
}

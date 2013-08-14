#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define FILLCHAR(A,X) memset(A,X,sizeof(A))
const int INF=2139062143;
const int MAXN=3000;
const int MAXM=50000000;
const int SIZE=200005;
int dist[MAXN],path[MAXN];
struct __TEdge{int startv,endv,cap,w,next;} E[MAXM];
int head[MAXN],ecount=1;
bool vst[MAXN];
int Q[SIZE];
int n,price,wFast,wSlow,tFast,tSlow;
int Source,Sink,Vtot,minCost=0;
inline void addEdge(const int a, const int b, const int c, const int w)
{
    ++ecount; E[ecount].startv=a; E[ecount].endv=b; E[ecount].cap=c; E[ecount].w=w;  E[ecount].next=head[a]; head[a]=ecount;
    ++ecount; E[ecount].startv=b; E[ecount].endv=a; E[ecount].cap=0; E[ecount].w=-w; E[ecount].next=head[b]; head[b]=ecount;
}
inline bool findAugPath()
{
    int QHead=0,QTail=1,now,p;
    FILLCHAR(vst,false);
    FILLCHAR(path,0);
    FILLCHAR(dist,127);
    dist[Source]=0;
    vst[Source]=true;
    Q[QTail]=Source;
    while (QHead<QTail)
    {
        ++QHead;
        now=Q[QHead%SIZE];
        vst[now]=false;
        for (p=head[now]; p; p=E[p].next)
            if (E[p].cap && dist[E[p].endv]>dist[now]+E[p].w){
                dist[E[p].endv]=dist[now]+E[p].w;
                path[E[p].endv]=p;
                if (!vst[E[p].endv])
                {
                    ++QTail;
                    Q[QTail%SIZE]=E[p].endv;
                    vst[E[p].endv]=true;
                }
            }
    }
    return (path[Sink]!=0);
}
inline int minCostFlow()
{
    int aug,p;
    while (findAugPath()) {
        aug=INF;
        for (p=Sink; p!=Source; p=E[path[p]].startv) {
            if (E[path[p]].cap<aug) 
                aug=E[path[p]].cap;
        }
        for (p=Sink; p!=Source; p=E[path[p]].startv) {
            E[path[p]].cap-=aug;
            E[path[p]^1].cap+=aug;
            minCost+=aug*E[path[p]].w;
        }
    };
    return minCost;
}
inline void Input()
{
    int i,outFlow;
    scanf("%d%d%d%d%d%d",&n,&price,&tFast,&wFast,&tSlow,&wSlow);
    Source=n*2+1;
    Sink=n*2+2;
    for (i=1; i<=n; ++i)
    {
        scanf("%d",&outFlow);
        addEdge(Source,i,outFlow,0);
        addEdge(i+n,Sink,outFlow,0);
        addEdge(Source,i+n,INF,price);
        if (i+tFast<=n)
            addEdge(i,n+i+tFast,INF,wFast);
        if (i+tSlow<=n)
            addEdge(i,n+i+tSlow,INF,wSlow);
        if (i<n)
            addEdge(i,i+1,INF,0);       
    }
}
int main()
{
    Input();
    printf("%d\n",minCostFlow());
}

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define FILLCHAR(A,X) memset(A,X,sizeof(A))
const int INF= 2147483600;
int n,m,fsum;

struct TEdge
{
    int  cur,startv,endv,next;
} edges[20000];
int ecount, head[200], nowHead[200];
namespace SAP
{
    int d[200]={}, count[200], preEdge[200], stack[200];   
    int Source, Sink, Tot;
    inline void addEdge(int u, int v, int w=0)
    {
        ++ecount;
        edges[ecount].startv=u;
        edges[ecount].endv=v;
        edges[ecount].next=head[u];
        edges[ecount].cur=w;
        head[u]=ecount;
    }

    inline void sap()
    {
        int i, x=Source, MinFlow=INF, mindis, mini, changedIndex;
        bool flag;
        count[0]=Tot;
        while (d[Source]<Tot)
        {
loop:
            flag=false;
            stack[x]=MinFlow;
            for (i=nowHead[x]; i; i=edges[i].next)
            {
                if (edges[i].cur && d[x]==d[edges[i].endv]+1)
                {
                    flag=true;
                    nowHead[x]=i;
                    MinFlow=std::min(MinFlow,edges[i].cur);
                    x=edges[i].endv;
                    preEdge[x]=i;
                    if (x==Sink)
                    {
                        fsum += MinFlow;
                        for (; x!=Source; x=edges[preEdge[x]].startv)
                        {
                            edges[preEdge[x]].cur   -= MinFlow;
                            edges[preEdge[x]^1].cur += MinFlow;
                        }
                        MinFlow=INF;
                    }
                    goto loop;
                }// if
            }// for
            if (!flag)
            {
                mindis=Tot;
                mini=0;
                for (i=head[x]; i; i=edges[i].next)
                    if (edges[i].cur && d[edges[i].endv]<mindis)
                    {
                        mindis=d[edges[i].endv];
                        mini=i;
                    }
                nowHead[x]=mini;
                --count[d[x]];
                changedIndex=d[x];
                d[x]=mindis+1;
                ++count[d[x]];
                if (count[changedIndex]==0)
                    break;
                if (x!=Source)
                {
                    x=edges[preEdge[x]].startv;
                    MinFlow=stack[x];
                }
            }
        }// while
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
        using namespace SAP;
        Source=m+n+1;
        Sink=m+n+2;
        Tot=m+n+2;
    }
    fsum=0;
    ecount=1;
    for (i=1;i<=m;++i)
    {
        SAP::addEdge(SAP::Source,i,1);
        SAP::addEdge(i,SAP::Source,0);
    }
    for (i=m+1;i<=m+n;++i)
    {
        SAP::addEdge(i,SAP::Sink,1);
        SAP::addEdge(SAP::Sink,i,0);
    }
    for (;;)
    {
        scanf("%d%d",&a,&b);
        if (a==-1&&b==-1)
            break;
        SAP::addEdge(a,b+m,1);
        SAP::addEdge(b+m,a,0);    
    }
    SAP::sap();
    printf("%d\n",fsum);
    for (i=2+2*m+2*n; i<=ecount; i+=2)
    {
        if (edges[i].cur==0)
            printf("%d %d\n",edges[i].startv,edges[i].endv);
    }
    
    return 0;
}

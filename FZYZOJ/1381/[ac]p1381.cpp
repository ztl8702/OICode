#include <cstdio>
#include <cstring>
#include <cstdlib>
const int MAXE=1000005;
const int MAXN=100005;
int n,m,q;
namespace Graph
{
    struct TEdge
    {
        int next,endv;
    } E[MAXE],Ei[MAXE],Es[MAXE];
    int head[MAXN],hi[MAXN],hs[MAXN];
    int last[MAXN],stack[MAXN],size[MAXN],color[MAXN],order[MAXN],InDegree[MAXN],ocount=0,count=0,sTail=0;
    
    inline void addEdge(const int a, const int b, TEdge e[], int h[])
    {
        ++h[0];
        e[h[0]].endv=b;
        e[h[0]].next=h[a];
        h[a]=h[0];
    }
    
    void dfs(const int now)
    {
        if (!color[now])
        {
            color[now]=1;
            for (int p=head[now]; p; p=E[p].next)
                dfs(E[p].endv);
            stack[++sTail]=now;
        }
    }
    
    void dfsi(const int now, const int cc)
    {
        color[now]=cc;
        ++size[cc];
        order[++ocount]=now;
        for (int p=hi[now]; p; p=Ei[p].next)
            if (!color[Ei[p].endv])
                dfsi(Ei[p].endv, cc);
    }
    
    inline void build()
    {
        int i,j,now;
        memset(color,0,sizeof(color));
        for (i=1; i<=n; ++i)
        {
            dfs(i);
        }
        memset(color,0,sizeof(color));
        for (i=sTail; i>0; --i)
            if (!color[stack[i]])
                dfsi(stack[i],++count);
        for (i=1; i<=n; ++i)
        {
            now=order[i];
            for (j=head[now]; j; j=E[j].next)
            {
                if (last[color[E[j].endv]]!=color[now] && color[now]!=color[E[j].endv])
                {
                    ++InDegree[color[E[j].endv]]; 
                    addEdge(color[now],color[E[j].endv], Es, hs);
                    last[color[E[j].endv]]=color[now];
                }
            }
        }
    }
    
    int Q[MAXN*2], len[MAXN],f[MAXN], maxlen, maxcount;
    void bfs()
    {
        int i; 
        int now, tot, p, QHead=0, QTail=0;
        maxlen=maxcount=0;
        for (i=1; i<=count; ++i)
            if (InDegree[i]==0)
            {
                Q[++QTail]=i;
                f[Q[QTail]]=1;
            }
        while (QHead<QTail)
        {
           
            now=Q[++QHead];
            len[now]+=size[now];
            tot=len[now]; 
            if (tot>maxlen)
            {
                maxlen=tot;
                maxcount=f[now]%q;
            } else
            if (tot==maxlen)
            {
                maxcount+=f[now];
                maxcount%=q;
            }
            for (p=hs[now]; p; p=Es[p].next)
            {
                if (len[now]>len[Es[p].endv])
                {
                    len[Es[p].endv]=len[now];
                    f[Es[p].endv]=f[now]%q;
                } else
                if (len[now]==len[Es[p].endv])
                {
                    f[Es[p].endv]+=f[now]%q;
                    f[Es[p].endv]%=q;
                }
                --InDegree[Es[p].endv];
                if (InDegree[Es[p].endv]==0)
                {
                    ++QTail;
                    Q[QTail]=Es[p].endv;
                }
            }
        }
    }
}

inline void input()
{
    int i,x,y;
    scanf("%d%d%d",&n,&m,&q);
    for (i=1; i<=m; ++i)
    {
        scanf("%d%d",&x,&y);
        Graph::addEdge(x,y,Graph::E,Graph::head);
        Graph::addEdge(y,x,Graph::Ei,Graph::hi);
    }
}

inline void work()
{
    Graph::build();
    Graph::bfs();
    printf("%d\n%d\n",Graph::maxlen, Graph::maxcount%q);
}

int main()
{
    input();
    work();
    return 0;
}

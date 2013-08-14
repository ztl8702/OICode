#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#define FILLCHAR(A,X) memset(A,X,sizeof(A))
const int MAXN=20005;
const int MAXM=100005;
int n,m;
int c[MAXN], v[MAXN];
namespace Graph
{
    struct TEdge
    {
        int endv, next;
    }e[MAXM*2], ei[MAXM*2], es[MAXN*2];
    int h[MAXN], hi[MAXN], hs[MAXN];
    int color[MAXN], tot[MAXN], stack[MAXN], tail, ccount, order[MAXN], last[MAXN];
    void addE(const int a, const int b, TEdge ee[], int hh[])
    {
        ++hh[0];
        ee[hh[0]].endv=b;
        ee[hh[0]].next=hh[a];
        hh[a]=hh[0];
    }

    void dfs(const int now)
    {
        color[now]=1;
        for (int p=h[now]; p; p=e[p].next)
            if (!color[e[p].endv])
                dfs(e[p].endv);
        stack[++tail]=now;
    }
    
    void dfsi(const int now, const int cc)
    {
        color[now]=cc;
        tot[cc]+=v[now];
        order[++order[0]]=now;
        for (int p=hi[now]; p; p=ei[p].next)
            if (!color[ei[p].endv])
                dfsi(ei[p].endv, cc);
    }
    
    void build()
    {
        int i, now;
        FILLCHAR(color, 0);
        for (i=1; i<=n; ++i)
            if (!color[i])
                dfs(i);
        FILLCHAR(color, 0);
        for (i=tail; i>0; --i)
            if (!color[stack[i]])
                dfsi(stack[i], ++ccount);
        for (i=1; i<=n; ++i)
        {
            now=order[i];
            for (int p=h[now]; p; p=e[p].next)
                if (last[color[e[p].endv]]!=color[now] && color[now]!=color[e[p].endv])
                {
                    addE(color[now], color[e[p].endv], es, hs);
                    last[color[e[p].endv]]=color[now];
                }
        }
    }
    int f[MAXN];
    int getMax(const int now)
    {
        if (f[now])
            return f[now];
        int tmp=0;
        for (int p=hs[now]; p; p=es[p].next)
            tmp=std::max(tmp, getMax(es[p].endv));
        return (f[now]=tmp+tot[now]);
    }
}
void input()
{
    int x,y;
    scanf("%d%d", &n, &m);
    for (int i=1; i<=n; ++i)
        scanf("%d%d", &c[i], &v[i]);
    for (int i=1; i<=m; ++i)
    {
        scanf("%d%d", &x, &y);
        Graph::addE(x,y, Graph::e, Graph::h);
        Graph::addE(y, x, Graph::ei, Graph::hi);
    }
    Graph::build();
}

void solve()
{
    double ans=0.0;
    for (int i=1; i<=n; ++i)
        ans=std::max(ans, (double)Graph::getMax(Graph::color[i])/c[i]);
    printf("%.2lf\n", ans);
}

int main()
{
    input();
    solve();
    return 0;
}

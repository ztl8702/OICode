#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
const int MAXN=305;
const int MAXM=100000;
int n,m,p;
int map[MAXN][MAXN];
int spot[MAXN];
struct TEdge
{
    int s,v, w, next;
    bool used;
} e[MAXM];
int  ecount;
int father[MAXN];
bool cmp(const TEdge &a, const TEdge &b)
{
    return a.w<b.w;
}

int getF(const int x)
{
    return (father[x]==x)?x:father[x]=getF(father[x]);
}

void mount(const int a, const int b)
{
    father[getF(a)]=getF(b);
}

void input()
{
    int i,j,k;
    memset(map, 60, sizeof(map)); 
    scanf("%d%d%d", &n, &m, &p);
    for (i=1; i<=n; ++i) map[i][i]=0;
    for (i=1; i<=p; ++i)
        scanf("%d", &spot[i]);
    for (i=1; i<=m; ++i)
    {
        scanf("%d%d%d", &e[i].s, &e[i].v, &e[i].w);
        if (e[i].w<map[e[i].s][e[i].v])
            map[e[i].s][e[i].v]=map[e[i].v][e[i].s]=e[i].w;
    }
    for (k=1; k<=n; ++k)
        for (i=1; i<=n; ++i)
            if (k!=i)
                for (j=1; j<=n; ++j)
                    if (k!=j && i!=j)
                        if (map[i][k]+map[k][j]<map[i][j])
                            map[i][j]=map[i][k]+map[k][j];
    for (i=1; i<p; ++i)
        for (j=i+1; j<=p; ++j)
        {
            ++ecount;
            e[ecount].s=spot[i];
            e[ecount].v=spot[j];
            e[ecount].w=map[spot[i]][spot[j]];
        }
}

void solve()
{
    int i, ans=0, tot=0;
    std::sort(e+1, e+ecount+1, cmp);
    m=1<<30;
    for (i=1; i<=n; ++i)    
        father[i]=i;
    for (i=1; i<=ecount && tot<=p-1; ++i)
        if (getF(e[i].s)!=getF(e[i].v))
        {
            ++tot;
            ans+=e[i].w;
            mount(e[i].s, e[i].v);
        }
    bool find1=false;
    for (i=1; i<=p; ++i)
        if (spot[i]==1)
        {
            find1=true; break;
        }
    if (!find1)
    {
        int m=1<<30;
        for (i=1; i<=p; ++i)
            m=std::min(m, map[1][spot[i]]);
        ans+=m;
    }
    printf("%d\n", ans);
}

int main()
{
    input();
    solve();
    return 0;
}

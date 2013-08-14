#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cmath>
#define FILLCHAR(A,X) memset(A,X,sizeof(A))
const int MAXN=10005;
const int MAXM=100005;
int n,m;
int lo;
struct TEdge
{
    int startv, endv, next;
    long long w;
} es[MAXM];
inline bool cmp(const TEdge &a, const TEdge &b)
{
    return a.w<b.w;
}
namespace Graph
{
    TEdge e[MAXM*3];
    int ecount, head[MAXN];
    int father[MAXN], pa[MAXN][20];
    long long f[MAXN][20];
    
    int getFather(const int x)
    {
        return (father[x]==x)?x:(father[x]=getFather(father[x]));
    }
    
    inline void mount(const int a, const int b)
    {
        int fa=getFather(a), fb=getFather(b);
        father[fa]=fb;
    }
    
    inline void addE(const int a, const int b, const long long w)
    {
        ++ecount;
        e[ecount].startv=a;
        e[ecount].endv=b;
        e[ecount].w=w;
        e[ecount].next=head[a];
        head[a]=ecount;
    }
    
    inline void Kruskal()
    {
        int i,count=0;
        for (i=1; i<=n; ++i)
            father[i]=i;
        for (i=1; i<=m; ++i)
        {
            if (getFather(es[i].startv) != getFather(es[i].endv))
            {
                ++count;
                mount(es[i].startv, es[i].endv);
                addE(es[i].startv, es[i].endv, es[i].w);
                addE(es[i].endv, es[i].startv, es[i].w);
            }
        }
    }
    int Q[MAXN*10], depth[MAXN];
    bool vst[MAXN];
    inline void bfs()
    {
        int h=0, t=0, p, now;
        FILLCHAR(vst, false);
        FILLCHAR(depth, 0);
        Q[++t]=1;
        vst[Q[t]]=true;
        depth[Q[t]]=0;
        pa[Q[t]][0]=0;
        while (h<t)
        {
            now=Q[++h];
            for (p=head[now]; p; p=e[p].next)
                if (!vst[e[p].endv])
                {
                    Q[++t]=e[p].endv;
                    vst[Q[t]]=true;
                    pa[Q[t]][0]=now;
                    f[Q[t]][0]=e[p].w;
                    depth[Q[t]]=depth[now]+1;
                }
        }
    }

    inline void process()
    {
        bfs();
        lo=(int)(log2(n));
        //for (int j=1; j<=n; ++j)
           //printf("pa[%d][0]=%d ",j,pa[j][0]);
        for (int i=1; i<=lo; ++i)
            for (int j=1; j<=n; ++j)
            {
                pa[j][i]=pa[pa[j][i-1]][i-1];//printf("pa[%d][%d]=pa[%d][%d]=%d  ",j,i,pa[j][i-1],i-1,pa[j][i]);
                f[j][i]=std::max(f[pa[j][i-1]][i-1], f[j][i-1]);
            }
    }

    inline long long LCA(const int a, const int b)
    {
        int i=0, l, r, delta;
        long long ans=0;
        r=(depth[a]<depth[b])?a:b;
        l=(depth[a]<depth[b])?b:a;
        delta=depth[l]-depth[r];
        for (i=0; delta; delta>>=1, ++i)
            if (delta %2)
            {
                ans=std::max(ans, f[l][i]);
                l=pa[l][i];
            }
        if (l==r)
            return ans;
        for (i=lo; i>=0; --i)
            if (pa[l][i]!=pa[r][i])
            {
                //printf("l=%d(%d) r=%d(%d) i=%d\n",l,depth[l],r,depth[r],i);
                ans=std::max(ans,f[l][i]);
                l=pa[l][i];  
             
                ans=std::max(ans,f[r][i]);
                r=pa[r][i];
            }
        ans=std::max(ans,f[l][0]);
        ans=std::max(ans,f[r][0]);
        //printf("LCA=%d ", pa[l][0]);
        return ans;
    }
}

inline void input()
{
    int i;
    scanf("%d%d", &n, &m);
    for (i=1; i<=m; ++i)
    {
        scanf("%d%d%lld",&es[i].startv, &es[i].endv, &es[i].w);
    }
    std::sort(es+1, es+1+m, cmp);
}

inline void solve()
{
    int i, Q, x, y;
    scanf("%d", &Q);
    for (i=1; i<=Q; ++i)
    {
        scanf("%d%d", &x, &y);
        printf("%lld\n", Graph::LCA(x,y));
    }
}

int main()
{
    input();
    Graph::Kruskal();
    Graph::process();
    solve();
    return 0;
}

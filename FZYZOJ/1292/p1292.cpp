#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
const int MAXN=155;
const int MAXM=5005;
int n, m;
struct TEdge
{
    int next, endv;
} e[MAXM*2];
int ecount=1, head[MAXN];
bool vst[MAXM*2];
int timeStamp, dfn[MAXN], low[MAXN];
int acount;
struct TAns
{
    int a, b;
} ans[MAXM];

inline bool ansCmp(const TAns &a, const TAns &b)
{
    return (a.a<b.a || (a.a==b.a && a.b<b.b));
}

inline void dfs(const int prevE, const int now)
{
    dfn[now]=low[now]=++timeStamp;
    for (int p=head[now]; p; p=e[p].next) 
    {
        if (!((p^1)==prevE || p==prevE))
        {
            if (!dfn[e[p].endv])
            {
                dfs(p, e[p].endv);
                if (low[e[p].endv] > dfn[now])
                {
                    ++acount;
                    ans[acount].a=now;
                    ans[acount].b=e[p].endv;
                    if (ans[acount].a>ans[acount].b)
                        std::swap(ans[acount].a, ans[acount].b);
                }
                low[now]=std::min(low[now], low[e[p].endv]);
            }
            else
                low[now]=std::min(low[now], dfn[e[p].endv]);
        }
    }
}

inline void addE(const int a, const int b)
{
    ++ecount;
    e[ecount].endv=b;
    e[ecount].next=head[a];
    head[a]=ecount;
}

inline void input()
{
    int i, a, b;
    scanf("%d%d", &n, &m);
    for (i=1; i<=m; ++i)
    {
        scanf("%d%d", &a, &b);
        addE(a,b);
        addE(b,a);
    }
}

int main()
{
    input();
    dfs(1, 1);
    std::sort(ans+1, ans+acount+1, ansCmp);
    for (int i=1; i<=acount; ++i)
        printf("%d %d\n", ans[i].a, ans[i].b);
    return 0;
}

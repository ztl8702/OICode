#include <cstdio>
#include <cstdlib>
#include <cstring>
//#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
const int MAXM=100005;
const int MAXN=50005;
const char DEPT[]="Ryuuguu\0";
const char DEST[]="Furude\0";
int n,m;
using namespace std;
map<string, int> names;
int mcount=0;

namespace ET
{
    struct TEdge
    {
        int endv, next;
        long long w;
    } e[MAXM*2];
    int ecount=0, head[MAXN];
    
    inline void addEdge(const int a, const int b, const long long w)
    {
        ++ecount;
        e[ecount].endv=b;
        e[ecount].w=w;
        e[ecount].next=head[a];
        head[a]=ecount;
    }
    
}

inline void input()
{
    int i, a, b;
    long long d;
    char foo[50],bar[50];
    scanf("%d%d", &n, &m);
    for (i=1; i<=n; ++i)
    {
        scanf("%s", foo);
        ++mcount;
        names[foo]=(mcount);
        //printf("[%s]\n",foo);
        //ha(foo);
        //std::cerr<<i<<"\n";
    }
    for (i=1; i<=m; ++i)
    {
        scanf("%s%s%lld",foo, bar, &d);
        a=names[foo];
        b=names[bar];
        ET::addEdge(a,b,d);
        ET::addEdge(b,a,d);
        //printf("[%d] %s %s %d<->%d(%lld)\n",i,foo,bar,a,b,d);
    }
}

bool vst[MAXN+5];
int Q[MAXN+5];
inline long long SPFA()
{
    int h=0, t=0, now;
    long long dis[MAXN];
    memset(dis, 127, sizeof(dis));
    memset(vst, 0, sizeof(vst));
    ++t;
    Q[t]=names[DEPT];
    dis[Q[t]]=0;
    vst[Q[t]]=true;
    while (h<t)
    {
        now=Q[(++h)%MAXN];
        for (int p=ET::head[now]; p; p=ET::e[p].next)
            if (dis[ET::e[p].endv]>dis[now]+ET::e[p].w)
            {
                dis[ET::e[p].endv]=dis[now]+ET::e[p].w;
                if (!vst[ET::e[p].endv])
                {
                    ++t;
                    Q[t%MAXN]=ET::e[p].endv;
                    vst[ET::e[p].endv]=true;
                }
            }
        vst[now]=false;
    }
    return dis[names[DEST]];
}

int main()
{
    input();
    printf("%lld\n",SPFA());
    return 0;
}

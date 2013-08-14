#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
using std::cin;
using std::cout;
using std::max;
using std::endl;
const int MAXN=6005;
struct TEdge
{
    int fromv, endv, next;
} e[MAXN*2];
int ecount=0, head[MAXN];
int n, happy[MAXN];
int f[2][MAXN];
bool vst[2][MAXN];
inline void addE(const int a, const int b)
{
    ++ecount;
    e[ecount].fromv=a;
    e[ecount].endv=b;
    e[ecount].next=head[a];
    head[a]=ecount;
}
void input()
{
    int x,y;
    scanf("%d", &n);
    for (int i=1; i<=n; ++i)
        scanf("%d", &happy[i]);
    while (1)
    {
        scanf("%d%d" , &x, &y);
        if (x==0 || y==0)
            break;
        addE(y,x);
    }
}

int dfs(const int chosen, const int now)
{
    if (vst[chosen][now])
        return f[chosen][now];
    vst[chosen][now]=true;
    f[chosen][now]=-(1<<30);
    int tmp=0;
    if (!chosen)
    {
        for (int p=head[now]; p; p=e[p].next)
            tmp+=max(dfs(1, e[p].endv),dfs(0,e[p].endv));
        f[chosen][now]=tmp;
    }
    else
    {
        tmp=0;
        for (int p=head[now]; p; p=e[p].next)
            tmp+=dfs(0,e[p].endv);
        f[chosen][now]=tmp+happy[now];
    }
    return f[chosen][now];
}
int main()
{
    input();
    int ans=-(1<<30);
    for (int i=1; i<=n; ++i)
        ans=max(ans, max(dfs(0,i), dfs(1,i)));
    cout<<ans<<endl;
    return 0;   
}

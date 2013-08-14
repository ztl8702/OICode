#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

inline int lowbit(const int x)
{
    return x&(-x);
}
const int MAXN=200000;
int n,m;
struct TBTable
{
    long long sum[MAXN+5];
    inline void add(int pos, long long v)
    {
        while (pos<=n)
        {
            sum[pos]+=v;
            pos+=lowbit(pos);
        }
    }
    
    inline long long getsum(int p)
    {
        long long res=0;
        while (p>0)
        {
            res+=sum[p];
            p-=lowbit(p);
        }
        return res;
    }
    
    inline long long query(const int l, const int r)
    {
        return getsum(r)-getsum(l-1);
    }
    
    inline void inita()
    {
        memset(sum, 0, sizeof(sum));
    }
}table; 

int father[MAXN+5];
long long num[MAXN+5];

int getfather(const int x)
{
    return (father[x]==x)?x:(father[x]=getfather(father[x]));
}

inline void mount(const int a, const int b)
{
    father[getfather(a)]=getfather(b);
}

bool workOnce(const int id)
{
    if (scanf("%d", &n)==EOF)
        return false;
    printf("Case #%d:\n",id);
    int i, cmd, x, y;
    table.inita(); 
    for (i=1; i<=n; ++i)
    {
        scanf("%lld", &num[i]);        
        table.add(i,num[i]);
        //father[i]=i;
    }
    for (i=1; i<=n+1; ++i)
        father[i]=i;
    int j;
    scanf("%d", &m);
    for (i=1; i<=m; ++i)
    {
        scanf("%d%d%d", &cmd, &x, &y);
        if (x>y)
            std::swap(x,y);
        if (cmd==0)
        {
            //printf("modify [%d,%d]\n", x, y);
            for (j=getfather(x); j<=y; )
            {
              //  printf("[%d]",j);
                table.add(j,-num[j]);
                num[j]=(long long)floor(sqrt((double)num[j]));
                table.add(j,+num[j]);
                if (num[j]==1 && j<n)
                    mount(j,j+1);
                j=getfather(j+1);
            }
        }
        else 
            printf("%lld\n",table.query(x,y));
    }
    printf("\n");
    return true;
}

int main()
{
    freopen("GSS.in","r",stdin);
    freopen("GSS.out","w",stdout);
    int i=1;
    while (workOnce(i)) ++i;
    return 0;
} 

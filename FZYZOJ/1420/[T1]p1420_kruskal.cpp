#include <cstdio>
#include <cstring>
#include <cstdlib>
const int MAXN=1000;
const int MAXM=12000000;
int edge[MAXM+5][3];
int p[MAXN + 5][MAXN + 5],ff[MAXN + 5];
bool used[MAXM + 5];
int n,count;
inline void addedge(int u,int v,int p)
{
    ++count;
    edge[count][0]=u;
    edge[count][1]=v;
    edge[count][2]=p;
}

inline int getFather(int x)
{
    int tmp=x;
    while (ff[x]!=x)
        x=ff[x];
    while (ff[tmp]!=tmp)
    {
        int father=ff[tmp];
        ff[tmp]=x;
        tmp=father;
    }
    return x;
}

void Union(int a,int b)
{
    int fa=getFather(a),fb=getFather(b);
    ff[fa]=fb;
}

void sort(int l,int r)
{
    int x[3],i=l,j=r,mid=edge[(l+r)>>1][2];
    do
    {
        while (edge[i][2]<mid) ++i;
        while (edge[j][2]>mid) --j;
        if (i<=j)
        {
            memcpy(x,edge[i],sizeof(x));
            memcpy(edge[i],edge[j],sizeof(x));
            memcpy(edge[j],x,sizeof(x));
            ++i; --j;
        }
    }
    while (i<=j);
    if (l<j) sort(l,j);
    if (i<r) sort(i,r);
}

int main()
{
    freopen("p1420.in","r",stdin);
    int i,j,tmp,found=0,Ans=0;
    scanf("%d",&n);
    count = 0;
    for (i = 1; i<=n; ++i)
    {
        scanf("%d",&tmp);
        addedge(n+1,i,tmp);
    }
    for (i = 1; i<=n; ++i)
        for (j = 1; j<=n; ++j)
            scanf("%d",&p[i][j]);
    for (i = 1; i < n; ++i)
        for (j=i+1 ; j<=n; ++j)
            addedge(i,j,p[i][j]);
    sort(1,count);
    for (i=1;i<=n+1;++i) ff[i]=i;
    int start=0;
    while (found<n)
    {
        bool full=true;
        for (i=1;i<=count;++i)
            if ((!used[i])&&(getFather(edge[i][0])!=getFather(edge[i][1])))
            {
                ++found;
                used[i]=true;
                Union(edge[i][0],edge[i][1]);
                Ans+=edge[i][2];
                break;
            }
    }
    printf("%d",Ans);
    return 0;
}

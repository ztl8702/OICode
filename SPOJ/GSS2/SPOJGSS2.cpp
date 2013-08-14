#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <map>
#include <vector>
#include <algorithm>
#define PRT(X) (X>>1)
#define LSON(X) (X<<1)
#define RSON(X) ((X<<1)+1)
const int INF  = 2147483000;
const int MAXN = 100000;
const int MAXQ = 100000;
const int MAXV = 100000;
typedef long long QInt;
typedef struct
{
    int l,r,lazy_add,lazy_max;
    QInt sum,maxsum;
} TNode;
typedef struct
{
    int l,r,id;
    QInt ans;
} TQuery;
TNode tree[MAXN*4];
TQuery Q[MAXQ+5];
int num[MAXN+5];
int n,qq;
std::map<int, int> last;
inline QInt max(QInt a,QInt b)
{
    return a>b?a:b;
}
namespace SegTree
{
void build(int now,int l,int r)
{
    tree[now].l=l;
    tree[now].r=r;
    tree[now].sum=tree[now].maxsum=tree[now].lazy_add=tree[now].lazy_max=0;
    if (l<r)
    {
        int mid=(l+r)>>1;
        build(LSON(now),l,mid);
        build(RSON(now),mid+1,r);
    }
}

inline void pushDown(int now)
{
    tree[LSON(now)].lazy_max=
        max(tree[LSON(now)].lazy_max, tree[LSON(now)].lazy_add + tree[now].lazy_max);
    tree[LSON(now)].lazy_add += tree[now].lazy_add;
    tree[RSON(now)].lazy_max=
        max(tree[RSON(now)].lazy_max, tree[RSON(now)].lazy_add + tree[now].lazy_max);
    tree[RSON(now)].lazy_add += tree[now].lazy_add;
    tree[now].lazy_add=tree[now].lazy_max=0;
}

inline void update(int now)
{
    tree[now].sum = max(tree[LSON(now)].sum+tree[LSON(now)].lazy_add, tree[RSON(now)].sum+tree[RSON(now)].lazy_add);
    QInt lmax=max(tree[LSON(now)].maxsum, tree[LSON(now)].sum+tree[LSON(now)].lazy_max);
    QInt rmax=max(tree[RSON(now)].maxsum, tree[RSON(now)].sum+tree[RSON(now)].lazy_max);
    tree[now].maxsum = max(lmax,rmax);
}

QInt getMax(int now,int l,int r)
{
    if (l<=tree[now].l && tree[now].r<=r)
    {
        return max(tree[now].maxsum, tree[now].sum+tree[now].lazy_max);
    }
    QInt tmp=0;
    if (tree[now].l != tree[now].r)
    {
        pushDown(now);
        update(now);
        if (l<=tree[LSON(now)].r)  tmp=max(tmp,getMax(LSON(now),l,r));
        if (tree[RSON(now)].l<=r)  tmp=max(tmp,getMax(RSON(now),l,r));
    }
    return tmp;
}

void insert(int now,int l,int r,int v)
{
    if (l<=tree[now].l && tree[now].r<=r)
    {
        tree[now].lazy_add += v;
        tree[now].lazy_max = max(tree[now].lazy_max,tree[now].lazy_add);
        return;
    }
    if (tree[now].l != tree[now].r)
    {
        pushDown(now);
        if (l<=tree[LSON(now)].r)  insert(LSON(now),l,r,v);
        if (tree[RSON(now)].l<=r)  insert(RSON(now),l,r,v);
        update(now);
    }
}

} //end of namespace
inline void swap(TQuery* a,TQuery* b)
{
    TQuery x;
    x=*a;
    *a=*b;
    *b=x;
}

void sortQByR(int l,int r)
{
    int i=l,j=r,mid=Q[(l+r)>>1].r;
    do
    {
        while (Q[i].r<mid) ++i;
        while (Q[j].r>mid) --j;
        if (i<=j)
        {
            swap(&Q[i],&Q[j]);
            ++i;
            --j;
        }
    }
    while (i<=j);
    if (l<j) sortQByR(l,j);
    if (i<r) sortQByR(i,r);
}

void sortQById(int l,int r)
{
    int i=l,j=r,mid=Q[(l+r)>>1].id;
    do
    {
        while (Q[i].id<mid) ++i;
        while (Q[j].id>mid) --j;
        if (i<=j)
        {
            swap(&Q[i],&Q[j]);
            ++i;
            --j;
        }
    }
    while (i<=j);
    if (l<j) sortQById(l,j);
    if (i<r) sortQById(i,r);
}

int main()
{
    int added=0;
    scanf("%d",&n);
    for (int i=1; i<=n; ++i) scanf("%d",&num[i]);
    scanf("%d",&qq);
    for (int i=1; i<=qq; ++i)
    {
        Q[i].id=i;
        scanf("%d%d",&Q[i].l,&Q[i].r);
    }
    SegTree::build(1,1,n);
    sortQByR(1,qq);
    for (int i=1; i<=qq; ++i)
    {
        while (added<Q[i].r)
        {
            ++added;
            SegTree::insert(1,last[num[added]]+1,added,num[added]);
            last[num[added]]=added;
        }

        Q[i].ans=SegTree::getMax(1,Q[i].l,Q[i].r);
    }
    sortQById(1,qq);
    for (int i=1; i<=qq; ++i) printf("%lld\n",Q[i].ans);
    return 0;
}


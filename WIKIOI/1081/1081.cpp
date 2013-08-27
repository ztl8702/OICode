#include <cstdio>
#include <cstring>
#include <cstdlib>
#define LSON(X) ((X)<<1)
#define RSON(X) (((X)<<1)+1)
#define FATHER(X) (X>>1)
const int MAXN=100000;
int ori[MAXN+5];
namespace SegmentTree
{
    const int MINRANGE=1;
    int left[MAXN*4],right[MAXN*4];
    int sum[MAXN*4],mark[MAXN*4];
    //[l,r)
    void build(const int now, const int l, const int r)
    {
        left[now]=l;
        right[now]=r;
        mark[now]=0;
        if (r-l>MINRANGE) //dividable
        {
            int mid=(l+r)>>1;
            build(LSON(now),l,mid);
            build(RSON(now),mid,r);

        }
        else
        {
            sum[now]=ori[left[now]];
        }
    }

    void add(const int now, const int l, const int r, const int x)
    {
        if (left[now]==right[now] || right[now]<=l || left[now]>=r)
            return;
        else
        {
            if (l<=left[now] && right[now]<=r)
            {
                mark[now]+=x;
            }
            else
            {
                add(LSON(now), l,r,x);
                add(RSON(now), l,r,x);
            }
        }
    }

    int getSum(const int now,  const int l, const int r)
    {
        if (left[now]==right[now] || right[now]<=l || left[now]>=r)
            return 0;
        else
        {
            if (l<=left[now] && right[now]<r)
                return sum[now];
            else
                return (getSum(LSON(now),l,r) + getSum(RSON(now), l, r));
        }
    }

    int findX(const int now, const int x)
    {
        if (left[now]==right[now] || x<left[now] || x>=right[now])
            return 0;
        else
        {
            if (left[now]==x && right[now]==x+1)
                return mark[now]+ori[x];
            else
                return mark[now]+findX(LSON(now),x)+findX(RSON(now),x);
        }
    }
}

int main()
{
    int m,n;
    scanf("%d", &n);
    for (int i=1; i<=n; ++i)
        scanf("%d", &ori[i]);
    SegmentTree::build(1, 1, n+1);
    scanf("%d", &m);
    int cmd, a1,a2,a3;
    for (int i=1; i<=m; ++i)
    {
        scanf("%d", &cmd);
        switch (cmd)
        {
            case 1:
                scanf("%d%d%d", &a1, &a2, &a3);
                SegmentTree::add(1, a1, a2+1, a3);
            break;

            case 2:
                scanf("%d", &a1);
                printf("%d\n", SegmentTree::findX(1, a1));
            break;

        }

    }
    return 0;
}

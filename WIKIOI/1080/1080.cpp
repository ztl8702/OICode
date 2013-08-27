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
        sum[now]=0;
        if (r-l>MINRANGE) //dividable
        {
            int mid=(l+r)>>1;
            build(LSON(now),l,mid);
            build(RSON(now),mid,r);
            sum[now]= sum[LSON(now)] +sum[RSON(now)];
        }
        else
        {
            sum[now]=ori[left[now]];
        }
    }

    void add(const int now, const int x, const int delta)
    {
        if (left[now]==right[now] || right[now]<=x || left[now]>x)
            return;
        else
        {
            if (left[now]==x && right[now]==x+1)
            {
                sum[now]+=delta;
            }
            else
            {
                add(LSON(now), x, delta);
                add(RSON(now), x, delta);
                sum[now]=sum[LSON(now)] + sum[RSON(now)];
            }
        }
    }

    int getSum(const int now,  const int l, const int r)
    {
        if (left[now]==right[now] || right[now]<=l || left[now]>=r)
            return 0;
        else
        {
            if (l<=left[now] && right[now]<=r)
                return sum[now];
            else
                return (getSum(LSON(now),l,r) + getSum(RSON(now), l, r));
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
                scanf("%d%d", &a1, &a2);
                SegmentTree::add(1, a1, a2);
            break;

            case 2:
                scanf("%d%d", &a1, &a2);
                printf("%d\n", SegmentTree::getSum(1, a1,a2+1));
            break;
        }
    }
    return 0;
}


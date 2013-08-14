/*
 * FZYZ OJ P1003
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
const int MAXN = 5000;
const int MAXX = 32000;

int tree[MAXX + 5], point[MAXN + 5][2], n, Ans[MAXN + 5];

namespace TLA
{
    inline int lowbit(int x)
    {
        return x&(-x);
    }
    inline void insert(int pos,int value)
    {
        while (pos<=MAXX)
        {
            tree[pos]+=value;
            pos += lowbit(pos);
        }
    }
    inline int getSum(int end)
    {
        int ans=0;
        while (end>0)
        {
            ans+=tree[end];
            end-=lowbit(end);
        }
        return ans;
    }
}

inline void swapPoint(int a,int b)
{
    int tmp;
    tmp=point[a][0];
    point[a][0]=point[b][0];
    point[b][0]=tmp;
    tmp=point[a][1];
    point[a][1]=point[b][1];
    point[b][1]=tmp;
}
void sortByXY(int L,int R)
{
    int i=L, j=R, midx=point[(L+R)>>1][0],
        midy=point[(L+R)>>1][1];
    do
    {
        while (point[i][0]<midx || (point[i][0]==midx && point[i][1]<midy)) ++i;
        while (midx<point[j][0] || (midx==point[j][0] && midy<point[j][1])) --j;
        if (i<=j)
        {
            swapPoint(i,j);
            ++i;
            --j;
        }
    }
    while (i<=j);
    if (L<j) sortByXY(L,j);
    if (i<R) sortByXY(i,R);
}
int main()
{
    int tmp,MultiplyCount;
    scanf("%d",&n);
    for (int i=1;i<=n;++i)
        scanf("%d%d",&point[i][0],&point[i][1]);
    sortByXY(1,n);
    MultiplyCount=0;
    point[0][0]=point[0][1]=-100;
    for (int i=1;i<=n;++i)
    {
        if (point[i][0]==point[i-1][0] && point[i][1]==point[i-1][1])
            ++MultiplyCount;
        else
            MultiplyCount=0;
        tmp = TLA::getSum(point[i][1]) - MultiplyCount;
        TLA::insert(point[i][1],1);
        ++ Ans[tmp];
    }
    for (int i=0;i<n;++i) printf("%d\n",Ans[i]);
    return 0;
}

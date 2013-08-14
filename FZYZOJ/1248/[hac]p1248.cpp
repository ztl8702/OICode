/*
 * FZYZ OJ P1248
 * By Radium
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define FILLCHAR(ARR,VAL) memset(ARR,VAL,sizeof(ARR))
const int SIZE = (1<<18);
const int OFFSET = (1<<17)+1;
int tree[SIZE + 5];
int n,minSalary,countLeave=0;
namespace BTA
{
    inline int lowbit(int x)
    {
        return x & (-x);
    }
    inline void add(int pos,int v)
    {
        for (; pos<=SIZE; pos+=lowbit(pos)) tree[pos]+=v;
    }

    inline int find(int x,int k)
    {
        if (lowbit(x)==1)
            return x;
        for (int p=x-(lowbit(x)>>1); ;p+=(lowbit(p)>>1))
        {
            if (tree[p]<k)
                k-=tree[p];
            else
                return find(p,k);
            if (lowbit(p)==1) break;
        }
        return x;
    }
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("p1248.in","r",stdin);
    freopen("p1248.out","w",stdout);
    #endif
    int rd,delta=0,tt;
    char cmd[10];
    scanf("%d %d\n",&n,&minSalary);
    for (int i=1; i<=n; ++i)
    {
        scanf("%s %d\n",cmd,&rd);
        switch(cmd[0])
        {
            case 'I':
            {
                if (rd>=minSalary) BTA::add(rd-delta+OFFSET,1);
                break;
            }
            case 'A':
            {
                delta+=rd;
                break;
            }
            case 'S':
            {
                delta-=rd;
                while (tree[SIZE]>0)
                {
                    tt=BTA::find(SIZE,1);
                    if (tt+delta-OFFSET>=minSalary) break;
                    ++countLeave;
                    BTA::add(tt,-1);
                }
                break;
            }
            case 'F':
            {
                if (rd>tree[SIZE])
                    printf("-1\n");
                else
                    printf("%d\n",BTA::find(SIZE,tree[SIZE]-rd+1)-OFFSET+delta);
                break;
            }
        }
    }
    printf("%d\n",countLeave);
    return 0;
}

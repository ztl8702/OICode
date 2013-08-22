#include <cstdio>
#include <cstring>
#include <cstdlib>
#define LSON(X) (X<<1)
#define RSON(X) ((X<<1)+1)
#define FAR(X) ((X)>>1)
const int MAXN=60005;
typedef struct point
{
    int id, di[6];
} Point;
inline void swap(int &a, int &b)
{
    int tmp=a;
    a=b;
    b=tmp;
}

class Heap //BIG ROOT HEAP
{
    public:
    int count;
    int num[MAXN],id[MAXN];
    bool big;
    Heap()
    {
        count=0;
        big=true;
    }

    bool greater(const int a, const int b)
    {
        return (big && a>b) || ((!big) && b>a);
    }

    void add(int p, int pid)
    {
        num[++count]=p;
        id[count]=pid;
        int i=count;
        while (i!=1 && greater(num[i],num[FAR(i)]))
        {
            swap(num[i],num[FAR(i)]);
            swap(id[i],id[FAR(i)]);
            i=FAR(i);
        }
    }

    void remove()
    {
        if (count == 0)
            return;
        num[1]=num[count];
        id[1]=id[count];
        --count;
        int i=1,j;
        while (i<=FAR(count))
        {
            j=LSON(i);
            if (j<count && greater(num[RSON(i)],num[j]))
                j++;
            if (greater(num[j],num[i]))
            {
                swap(num[i],num[j]);
                swap(id[i],id[j]);
                i=j;
            }
            else
            {
                break;
            }
        }
    }


};
Heap hmax[33],hmin[33];
bool exist[MAXN];
int q, k;
void solve()
{
    int cmdCount=0, presentCount=0;

    memset(exist,0,sizeof(exist));
    for (int i=0; i<(1<<k); ++i)
    {
        hmax[i].big=true;
        hmax[i].count=0;
        hmin[i].big=false;
        hmin[i].count=0;
    }
    int cmd, tmp, dem[10];
    for (int i=1; i<=q; ++i)
    {
        scanf("%d", &cmd);
        ++cmdCount;
        switch (cmd)
        {
            case 0:
                for (int i=0; i<k; ++i)
                    scanf("%d",&dem[i]);
                exist[cmdCount]=true;
                ++presentCount;
                for (int i=0; i<(1<<k); ++i)
                {
                    tmp=0;
                    for (int j=1, bit=0; j<(1<<k); j<<=1,++bit)
                    {
                        if ((i & j)==0)
                            tmp-=dem[bit];
                        else
                            tmp+=dem[bit];
                    }
                    hmax[i].add(tmp,cmdCount);
                    hmin[i].add(tmp,cmdCount);
                }
                {
                    int ans=0;
                    if (presentCount>1)
                    {
                        for (int i=0; i<(1<<k); ++i)
                        {
                            if (hmax[i].count>0 && hmin[i].count>0)
                                if (hmax[i].num[1]-hmin[i].num[1]>ans)
                                    ans=hmax[i].num[1]-hmin[i].num[1];
                        }
                    }
                    printf("%d\n", ans);
                }
                break;
            case 1:
                scanf("%d", &tmp);
                if (exist[tmp])
                {
                    --presentCount;
                    exist[tmp]=false;
                }
                for (int i=0; i<(1<<k); ++i)
                {
                    while (hmax[i].count>0 && !(exist[hmax[i].id[1]]))
                        hmax[i].remove();
                    while (hmin[i].count>0 && !(exist[hmin[i].id[1]]))
                        hmin[i].remove();
                }
                {
                    int ans=0;
                    if (presentCount>1)
                    {
                        for (int i=0; i<(1<<k); ++i)
                        {
                            if (hmax[i].count>0 && hmin[i].count>0)
                                if (hmax[i].num[1]-hmin[i].num[1]>ans)
                                    ans=hmax[i].num[1]-hmin[i].num[1];
                        }
                    }
                    printf("%d\n", ans);
                }
                break;
            default:
                ;
        }
    }
}

int main()
{

    while (scanf("%d%d",&q,&k)!=EOF)
    {
        solve();
    }

    return 0;
}

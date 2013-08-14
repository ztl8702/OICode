/*
 * OJ P1605
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

#define MAXN 100005
#define LSON(x) ((x)<<1)
#define RSON(x) ((((x)<<1))+1)
#define PRT(x) ((x)>>1)

typedef struct __heap
{
    int tot,a[MAXN];
    bool type;
    inline void swap(const int ai,const int bi);
    void heapify(int n,int now);
    inline int getTop();
    void insert(const int value) ;
    int pop();
} THeap;

THeap HMax,HMin;
int n;

inline bool cmp(const bool swc,const int a,const int b)
{
    if (swc)
        return a>b?1:0;
    else
        return a>b?0:1;
}

int main()
{
    int rd;
#ifndef ONLINE_JUDGE
    freopen("p1605.in","r",stdin);
    freopen("p1605.out","w",stdout);
#endif
    HMax.type=true;
    HMin.type=false;
    scanf("%d",&n);
    for (int i=1; i<=n; ++i)
    {
        scanf("%d",&rd);
        HMax.insert(rd);
        if (i%2==1)
        {
            while (HMax.tot>0 && HMax.getTop()>HMin.getTop())
                HMin.insert(HMax.pop());
            while (HMin.tot>0 && HMax.tot<HMin.tot)
                HMax.insert(HMin.pop());
            while (HMax.tot>0 && HMax.tot>HMin.tot+1)
                HMin.insert(HMax.pop());
            printf("%d\n",HMax.getTop());
        }
    }
    return 0;
}

inline void __heap::swap(const int ai,const int bi)
{
    int t=this->a[ai];
    this->a[ai]=this->a[bi];
    this->a[bi]=t;
}

void __heap::heapify(int n,int now) //sink
{
    int left=LSON(now);
    int right=RSON(now);
    int maxi=now;
    if (left<=n) maxi =cmp(this->type,this->a[left],this->a[maxi])?left:maxi;
    if (right<=n) maxi=cmp(this->type,this->a[right],this->a[maxi])?right:maxi;
    if (maxi!=now)
    {
        this->swap(maxi,now);
        this->heapify(n,maxi);
    }
}

inline int __heap::getTop()
{
    return this->a[1];
}

void __heap::insert(const int value)  //rise
{
    ++(this->tot);
    this->a[this->tot]=value;
    int p=this->tot;
    while (p>1&&cmp(this->type,value,this->a[PRT(p)]))
    {
        this->a[p]=this->a[PRT(p)];
        p=PRT(p);
    }
    this->a[p]=value;
}

int __heap::pop()
{
    int ans=this->a[1];
    this->a[1]=this->a[tot];
    --(this->tot);
    this->heapify(this->tot,1);
    return ans;
}

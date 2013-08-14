#include <cstdio>
#include <cstring>
#include <cstdlib>
const int MAXN=50000;
int rel[MAXN + 5], father[MAXN + 5];
int n,k,fakeCount=0;

int find(int x)
{
    if (father[x]==x) return x;
    int fx=father[x];
    father[x]=find(father[x]);
    rel[x]=(rel[fx]+rel[x]) % 3;
    return father[x];
}

void unionSet(int a,int b,int delta)
{
    int fa=find(a), fb=find(b);
    father[fa]=fb;
    rel[fa]=(rel[b]+delta-rel[a]+3) % 3;
}

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("p1649.in","r",stdin);
    freopen("p1649.out","w",stdout);
    #endif
    int r1,r2,r3,fx,fy,tmp;
    scanf("%d%d",&n,&k);
    for (int i=1;i<=n;++i)
        father[i]=i;
    for (int i=1;i<=k;++i)
    {
        scanf("%d%d%d",&r1,&r2,&r3);

        if (r2>n || r3>n || (r1==2 && r2==r3))
        {
            ++fakeCount;
            continue;
        }
        fx=find(r2);
        fy=find(r3);
        if (fx==fy)
        {
            tmp=(rel[r2]-rel[r3]+3) % 3; 
            if (tmp!=r1-1)
              ++fakeCount;
        }
        else
        {
            unionSet(r2,r3,r1-1);
        }    
    }
    printf("%d\n",fakeCount);

    return 0;   
}

/*
 * FZYZ OJ P1650
 */
#include<cstdio>
const int MAXN=1000000;
const int MAXM=10000000;
int n,m,p,q;
int color[MAXN + 5], next[MAXN + 5],path[MAXN + 5];
inline int max(int a,int b) {return a>b?a:b;}
inline int min(int a,int b) {return a<b?a:b;}

inline int findNext(int x)
{
    int t,tot=0;
    if (color[x]==0) return x;
    for (t=next[x];color[t]!=0;path[++tot]=t,t=next[t]);
    for (int i=tot;i>0;--i) next[path[i]]=t;
    next[x]=t;
    return next[x];
}

int main()
{
    int low,l1,l2,head,tail;
    #ifndef ONLINE_JUDGE
    freopen("p1650.in","r",stdin);
    freopen("p1650.out","w",stdout);
    #endif
    scanf("%d%d%d%d",&n,&m,&p,&q);
    for (int i=1;i<=n+1;++i) next[i]=i+1;
    low=max(m-n+1,0);
    for (int i=m;i>=low;--i)
    {
        l1=(i*p+q)%n +1;
        l2=(i*q+p)%n +1;
        head=min(l1,l2);
        tail=max(l1,l2);
        head=findNext(head);
        while (head<=tail)
        {
            color[head]=i;
            head=findNext(head);
        }
    }
    for (int i=1;i<=n;++i)
        printf("%d\n",color[i]);
    return 0;
}



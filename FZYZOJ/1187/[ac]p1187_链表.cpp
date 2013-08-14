/*
  FZYZOJ 1187
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXN 30
#define MAXM 30
#define MAXLL 1000000000
int n,m,size;
int mach[MAXN][MAXM], tm[MAXN][MAXM], last[MAXN];
int ord[MAXN*MAXM];
int l[MAXM*MAXN+MAXM],len[MAXM*MAXN+MAXM],next[MAXM*MAXN+MAXM],prev[MAXM*MAXN+MAXM];
int count;


inline int max(int a,int b)
{
    return a>b?a:b;
}


inline int min(int a,int b)
{
    return a<b?a:b;
}

void add(int wi,int mi)
{
    for (int i=next[mi];i!=0;i=next[i])
    {
        if (len[i]>=tm[wi][tm[wi][0]] && last[wi]+tm[wi][tm[wi][0]]<=len[i]+l[i]-1)
        {
            int p1=max(last[wi]+1,l[i]);
            int p2=p1+tm[wi][tm[wi][0]]-1;
            last[wi]=p2;
            tm[wi][0]++;
            if (p1==l[i]&&(p2==l[i]+len[i]-1))
            {
                len[i]=0;
                next[prev[i]]=next[i];
                prev[next[i]]=prev[i];
                prev[0]=next[0]=0;
                break;
            }
            if (p1==l[i])
            {
                len[i]-=p2-l[i]+1;
                l[i]=p2+1;
                break;
            }
            if (p2==l[i]+len[i]-1)
            {
                len[i]=p1-l[i];
                break;
            }

            {
                count++;
                prev[count]=i;
                next[count]=next[i];
                prev[next[i]]=count;
                next[i]=count;
                prev[0]=next[0]=0;
                l[count]=p2+1;
                len[count]=len[i]-(p2-l[i]+1);
                len[i]=p1-l[i];
            }
            break;
        }
    }
}

void process()
{
    for (int i=1;i<=size;++i)
    {
        add(ord[i],mach[ord[i]][tm[ord[i]][0]]);
    }
}

void readdata()
{
    scanf("%d%d",&m,&n);
    size=m*n;
    for (int i=1; i<=size; ++i)
        scanf("%d",&ord[i]);
    for (int i=1; i<=n; ++i)
        for (int j=1; j<=m; ++j)
            scanf("%d",&mach[i][j]);
    for (int i=1; i<=n; ++i)
    {
        for (int j=1; j<=m; ++j)
            scanf("%d",&tm[i][j]);
        last[i]=0;
        tm[i][0]=1;
    }
    count=m;
    for (int i=1;i<=m;++i)
    {
        l[++count]=1;
        len[count]=MAXLL;
        next[count]=0;
        prev[count]=i;
        next[i]=count;
    }
}

int main()
{
    readdata();
    process();
    int ans=-MAXLL;
    for (int i=1;i<=n;++i)
      if (last[i]>ans) ans=last[i];
    printf("%d",ans);
    return 0;
}

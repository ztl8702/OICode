/*
 * FZYZOJ P1504
 * 2nd MARCH, 2012
 */
 
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define FILLCHAR(A,X) memset(A,X,sizeof(A))
const int MAXN=1005;
const int MAXM=10005;
const int INFINITY=2147483647;
int f[MAXN][MAXM],pop[MAXN][MAXM],t[MAXN][MAXM];
int Q[MAXM],V[MAXM],QHead,QTail;
//  f[LINE][END POS]

int n,m,K;
inline void Input()
{
    int i,j;
    scanf("%d%d%d",&n,&m,&K);
    for (i=1;i<=n+1;++i)
    {
        for (j=2;j<=m+1;++j)
        {
            scanf("%d",&pop[i][j]);
            pop[i][j]=pop[i][j-1]+pop[i][j];
        }
        for (j=2;j<=m+1;++j)
        {
            scanf("%d",&t[i][j]);
            t[i][j]=t[i][j-1]+t[i][j];
        }
    }
}

inline int g(int i,int k) //j>=k
{
    return (f[i+1][k]-pop[i][k]);
}

inline int gm(int i,int k)
{
    return (f[i+1][k]+pop[i][k]);
}
inline int max(int a,int b)
{
    return a>b?a:b;
}
int main()
{
    int i,j,k,Ans=-INFINITY,tmp;
    #ifndef DEBUG
    #ifndef ONLINE_JUDGE
    freopen("p1504.in","r",stdin);
    freopen("p1504.out","w",stdout);
    #endif
    #endif
    Input();
    for (i=n+1;i>=1;--i)
    {

        QTail=1;
        QHead=0;
        Q[QTail]=1;
        V[QTail]=g(i,1);
        for (j=1;j<=m+1;++j) //j>=k
        {
            while (QHead<QTail && V[QTail]<=g(i,j))
                --QTail;
            Q[++QTail]=j;
            V[QTail]=g(i,j);
            while (QHead<QTail && (t[i][j]-t[i][Q[QHead+1]])>K) 
                ++QHead;
            f[i][j]=V[QHead+1]+pop[i][j];
        }
        
        QTail=1;
        QHead=0;
        Q[QTail]=m+1;
        V[QTail]=gm(i,m+1);
        for (j=m+1;j>=1;--j) //j<=k
        {
            while (QHead<QTail && V[QTail]<=gm(i,j))
                --QTail;
            Q[++QTail]=j;
            V[QTail]=gm(i,j);
            while (QHead<QTail && (t[i][Q[QHead+1]]-t[i][j])>K)
                ++QHead;
            f[i][j]=max(f[i][j],V[QHead+1]-pop[i][j]);
        }
        
    }
    for (i=1;i<=m+1;++i)
        Ans=max(Ans,f[1][i]);
    printf("%d\n",Ans);
    return 0;
}

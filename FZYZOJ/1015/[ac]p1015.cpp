#include <cstdio>
#include <cstring>
#include <cstdlib>
const int MAXN=2005;
int n,num[MAXN*2];
int f[MAXN*2];
int len;

inline void input()
{
    int i;
    scanf("%d",&n);
    for (i=n+1; i<=2*n; ++i)
    {
        scanf("%d",&num[i]);
        num[2*n-i+1]=num[i];
    }
}

inline int find(const int L, const int R, const int intToFind)
{
    int l=L,r=R,mid;
    while (l<r)
    {
        mid=(l+r)>>1;
        if (f[mid]<intToFind)
            l=mid+1;
        else
            r=mid;
    }
    return l;
}

inline void work()
{
    int i,pos;
    len=0;
    for (i=1; i<=2*n; ++i)
    {
        if (f[len]<num[i])
        {
            f[++len]=num[i]; //printf("new f[%d]\n",len);
        }
        else
        {
            pos=find(1,len,num[i]);
            f[pos]=num[i];
            /*printf("f[%d]\n",pos);*/
        }
    }
}

int main()
{
    input();
    work();
    printf("%d\n",len);
    return 0;
}

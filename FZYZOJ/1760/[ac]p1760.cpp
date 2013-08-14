#include <cstdio>
#include <cstdlib>
int a,b,c;
int ans;

inline int getMin(const int a, const int b)
{
    return (a<b)?a:b;
}

int main()
{
    int i,len,col,delta,incLimit;
    scanf("%d%d%d",&a,&b,&c);
    col=b+c-1;
    len=a;
    delta=1;
    incLimit=getMin(b,c);
    for (i=1; i<=col; ++i)
    {
        ans+=len;
        if (i<incLimit)
            delta=1;
        else if (i>=col-incLimit+1)
            delta=-1;
        else
            delta=0;
        len+=delta; 
    }
    printf("%d\n",ans);
    return 0;
}

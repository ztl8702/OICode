#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
int n,ans;
int main()
{
    int i;
    scanf("%d",&n);
    if (n==1)   
        printf("1\n");
    else
    {
        i=1;
        ans=1;
        do
        {
            i=(int)ceil((double)i/(1-(double)i/n));
            //printf("(%d) ",i);
            ++ans;
        } while (i<n);
        //puts("while end");
        printf("%d\n",ans);
    }
    
    return 0;
}

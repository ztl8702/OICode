#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
int n;
int a[205], sum[2], countLeft, ans=0;
bool team[205];
int main()
{
    int i,j,mini,minj,minDelta;
    bool found;
    scanf("%d", &n);
    countLeft=n>>1;
    for (i=1; i<=n; ++i)
        scanf("%d", &a[i]);
    for (i=1; i<=countLeft; ++i)
    {
        sum[false]+=a[i];
        team[i]=false;
    }
    for (i=countLeft+1; i<=n; ++i)
    {
        sum[true]+=a[i];
        team[i]=true;
    }
    ans=abs(sum[true]-sum[false]);
    
    do
    {
        found=false;
        minDelta=0;
        for (i=1; i<=n; ++i)
            if (team[i]==true)
            for (j=1; j<=n; ++j)
                if (team[j]==false)
                    if (abs((sum[team[i]]+a[j]-a[i])-(sum[team[j]]+a[i]-a[j]))<ans)
                        {
                            ans=abs((sum[team[i]]+a[j]-a[i])-(sum[team[j]]+a[i]-a[j]));
                            mini=i;
                            minj=j;
                            found=true;
                        }
                    
        if (found)
        {
            sum[team[mini]]+=a[minj]-a[mini];
            sum[team[minj]]+=a[mini]-a[minj];
            team[mini]=!team[mini];
            team[minj]=!team[minj];
            ans=abs(sum[true]-sum[false]);
        }
    }
    while (found);
    printf("%d %d\n", std::min(sum[true],sum[false]), std::max(sum[false], sum[true]));
    while(1);return 0; 
}

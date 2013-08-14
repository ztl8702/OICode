#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;
int n,m;
bool f[2005],r[25];
int v[25];
int ans=0;
    void readdata()
    {
        scanf("%d%d",&n,&m);
        for (int i=1;i<=n;++i) scanf("%d",&v[i]);
    }

    int dp()
    {
        int i,j,tot;
        tot=0;
        memset(f,0,sizeof(f));
        int count=0;
        f[0]=1;
        for (i=1;i<=n;++i)
            if (!r[i])
            {
                tot+=v[i];
                for (j=tot;j>=v[i];--j)
                   f[j]=f[j] | f[j-v[i]];
            }
        for (i=1;i<=tot;++i)
          if (f[i]) ++count;
        return count;
    }

    void dfs(int now,int sum)
    {
        if (sum==m)
        {
            ans=max(ans,dp());
            return;
        }
        for (int i=now+1;i<=n;++i)
        {
            r[i]=true;
            dfs(i,sum+1);
            r[i]=false;
        }
    }

int main()
{
    readdata();
    dfs(0,0);
    printf("%d\n",ans);

    return 0;
}

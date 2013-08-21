#include <cstdio>
#include <cstring>
#include <cstdlib>
int n,m;
int f[45][45][45][45];
int balance[5], value[350];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i=1; i<=n; ++i)
        scanf("%d", &value[i]);
    int rd;
    memset(balance,0,sizeof(balance));
    for (int i=1; i<=m; ++i)
    {
        scanf("%d", &rd);
        ++balance[rd];
    }
    f[0][0][0][0]=value[1];
    for (int i=1; i<=m; ++i)
    {
        for (int a1=0; a1<=i && a1<=balance[1]; ++a1)
            for (int a2=0; a2<=i-a1 && a2<=balance[2]; ++a2)
                for (int a3=0; a3<=i-a1-a2 && a3<=balance[3]; ++a3)
                {
                    int a4=i-a1-a2-a3;
                    if (a4<=balance[4])
                    {
                        f[a1][a2][a3][a4]=value[1+a1+a2*2+a3*3+a4*4];
                        int max=0;
                        if (a1>0)
                            max=(f[a1-1][a2][a3][a4]>max)?f[a1-1][a2][a3][a4]:max;
                        if (a2>0)
                            max=(f[a1][a2-1][a3][a4]>max)?f[a1][a2-1][a3][a4]:max;
                        if (a3>0)
                            max=(f[a1][a2][a3-1][a4]>max)?f[a1][a2][a3-1][a4]:max;
                        if (a4>0)
                            max=(f[a1][a2][a3][a4-1]>max)?f[a1][a2][a3][a4-1]:max;
                        f[a1][a2][a3][a4]+=max;
                    }
                }
    }
    printf("%d\n",f[balance[1]][balance[2]][balance[3]][balance[4]]);
    return 0;
}

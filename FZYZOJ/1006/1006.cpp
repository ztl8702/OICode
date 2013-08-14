#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using std::cout;
using std::endl;
using std::max;
int n;
int m[50][50],f[50][25][25][25];

void input()
{
    int i,j;
    scanf("%d", &n);
    for (i=1; i<=n; ++i)
        for (j=1; j<=n; ++j)
            scanf("%d", &m[i][j]);
}

void work()
{
    int i,a,b,c, k1, k2, k3;
    int tmp;
    bool get[50];
    f[0][0][0][0]=m[1][1];
    for (i=1; i<=2*n-2; ++i)
        for (a=0; a<=i; ++a)
            for (b=0; b<=i; ++b)
                for (c=0; c<=i; ++c)
                {
                    memset(get,false, sizeof(get));
                    tmp=0;
                    for (k1=-1; k1<=0; ++k1)
                        if (0<=a+k1 && a+k1<=i-1)
                        for (k2=-1; k2<=0; ++k2)
                            if (0<=b+k2 && b+k2<=i-1)
                            for (k3=-1; k3<=0; ++k3)
                                if (0<=c+k3 && c+k3<=i-1)
                                    tmp=max(tmp, f[i-1][a+k1][b+k2][c+k3]);
                    f[i][a][b][c]=tmp+m[1+a][1+i-a]+m[1+b][1+i-b]+m[1+c][1+i-c]-(a==c)*m[1+a][1+i-a]-(a==b)*m[1+a][1+i-a]-(b==c)*m[1+b][1+i-b]+(a==b && b==c)*m[1+a][1+i-a];
                    //printf("f[%d][%d][%d][%d] =%d\n", i,a,b,c,f[i][a][b][c]);
                }
    cout<<f[2*n-2][n-1][n-1][n-1]<<endl;    
} 

int main()
{
    input();
    work();
    //system("pause");
    return 0;
}

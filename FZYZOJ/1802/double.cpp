#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
char c[10][5];
bool vst[2000000];
double f[2000000];
int power[20];
int h[20];
double dfs(const int now)
{
    if (now==power[9]-1)
        return 1.00;
    if (vst[now])
        return f[now];
    vst[now]=true;
    int count=0;
    double tmp=0.0;
    for (int i=1; i<=8; ++i)
        for (int j=i+1; j<=9; ++j)
            if (h[i]>0 && h[j]>0 && c[i][h[i]]==c[j][h[j]])
            {
                ++count;
                --h[i];
                --h[j];
                tmp+=dfs(now+power[i-1]+power[j-1]);
                ++h[i];
                ++h[j];
            }
    if (count)
        return f[now]=tmp/count;
    else
        return f[now]=0.00;
    
}
void input()
{
    int i;
    char tmp[5][10];
    for (i=1; i<=9; ++i)
    {
        scanf("%s%s%s%s", tmp[1], tmp[2], tmp[3], tmp[4]);
        c[i][1]=tmp[1][0];
        c[i][2]=tmp[2][0];
        c[i][3]=tmp[3][0];
        c[i][4]=tmp[4][0];
    }
    power[0]=1;
    for (i=1; i<=9; ++i)
        h[i]=4;
    for (i=1; i<=9; ++i)
        power[i]=power[i-1]*5;
}

int main()
{
    input();
    printf("%.6lf", dfs(0));
    return 0;
}

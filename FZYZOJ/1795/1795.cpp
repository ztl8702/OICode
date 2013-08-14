#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
const int d[][2]={{+1,0}, {-1,0}, {0,+1},{0,-1}};
int n,m,k;
char map[1005][1005];
const int QSIZE=100000;
int Q[QSIZE+5][4];
bool vst[1005][1005][7];

void bfs()
{
    int nowx,nowy,dx,dy,newk, i,QHead=0, QTail=1;
    vst[1][1][k]=true;
    Q[1][0]=1;
    Q[1][1]=1;
    Q[1][2]=0;
    Q[1][3]=k;
    while (QHead<QTail)
    {
        ++QHead;
        nowx=Q[QHead%QSIZE][0];
        nowy=Q[QHead%QSIZE][1];
        for (i=0; i<=3; ++i)
        {
            dx=nowx+d[i][0];
            dy=nowy+d[i][1];
            newk=Q[QHead%QSIZE][3]-(map[dx][dy]=='*');
            if (dx>0 && dx<=n && dy>0 && dy<=m)
                if (map[dx][dy]=='.' || (map[dx][dy]=='*' && newk>=0))
                    if (!vst[dx][dy][newk])
                    {
                        ++QTail;
                        Q[QTail%QSIZE][0]=dx;
                        Q[QTail%QSIZE][1]=dy;
                        Q[QTail%QSIZE][2]=Q[QHead%QSIZE][2]+1;
                        Q[QTail%QSIZE][3]=newk;
                        vst[dx][dy][newk]=true;
                        if (dx==n && dy==m)
                        {
                            printf("%d\n", Q[QTail%QSIZE][2]);
                            return;
                        }
                    }
        }
    }    
    printf("POOR LMX\n");
}

void input()
{
    int i,j;
    scanf("%d%d%d\n", &n, &m, &k);
    for (i=1; i<=n; ++i)
    {
        gets(map[i]+1);
    }
}

int main()
{   
   //freopen("rob10.in","r",stdin);
    input();
    if (n==1 && m==1)
        puts("0");
    else
        bfs(); while(1);
    return 0;
}

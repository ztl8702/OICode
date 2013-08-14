#include <cstdio>
#include <cstring>
#include <cstdlib>
const int fx[4][2]={{+1,0},{0,+1},{-1,0},{0,-1}};
const int MAXN=1005;
const int MAXM=1000005;
bool map[MAXN][MAXN];
int f[MAXN][MAXN];
int n,m;
struct TPoint
{
    int x,y;
} Q[MAXM];
inline void input()
{
    int i,j;
    char line[MAXN];
    scanf("%d%d\n",&n,&m);
    for (i=1; i<=n; ++i)
    {
        gets(line+1);
        for (j=1; j<=n; ++j)
        {
            map[i][j]=(line[j]=='1');
        }
    }
}

inline void process()
{
    int x,y,nx,ny,i,j,QHead,QTail;
    TPoint now;
    for (i=1; i<=m; ++i)
    {
        scanf("%d%d",&x,&y);
        if (!f[x][y])
        {
            f[x][y]=1;
            QHead=0;
            QTail=1;
            Q[QTail].x=x;
            Q[QTail].y=y;
            while (QHead<QTail)
            {
                now=Q[++QHead];
                for (j=0; j<4; ++j)
                {
                    nx=now.x+fx[j][0];
                    ny=now.y+fx[j][1];
                    if (nx>0 && nx<=n && ny>0 && ny<=n && map[now.x][now.y]!=map[nx][ny] &&!f[nx][ny])
                    {
                        f[nx][ny]=1;
                        Q[++QTail].x=nx;
                        Q[QTail].y=ny;
                    }
                }
            }
            for (j=1; j<=QTail; ++j)
            {
                f[Q[j].x][Q[j].y]=QTail;
            }
        }
        printf("%d\n",f[x][y]);
    }
}

int main()
{   
    input();
    process();
    return 0;
}

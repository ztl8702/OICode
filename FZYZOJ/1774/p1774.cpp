#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
const int drt[][2]={{-1,0},{+1,0},{0,-1},{0,+1}};
int n,m;
bool map[100][100];
int space[3000][2];
int scount, blocked=0;
inline void input()
{
    int i,j;
    char rd[100];
    scanf("%d%d\n", &n, &m);
    for (i=1; i<=n; ++i)
    {
        gets(rd);
        for (j=1; j<=m; ++j)
        {
            map[i][j]=(rd[j-1]=='.');
            if (!map[i][j])
                space[++scount][0]=i, space[scount][1]=j;
        }
    }
}

bool vst[100][100];
int tot;
void fill(const int x, const int y)
{
    vst[x][y]=true;
    ++tot;
    int i, nx, ny;
    for (i=0; i<=4; ++i)
    {
        nx=x+drt[i][0];
        ny=y+drt[i][1];
        if (nx>0 && nx<=n && ny>0 && ny<=m)
            if ((!map[nx][ny]) &&(!vst[nx][ny]))
                fill(nx,ny);
    }
}

inline bool check()
{
    int i;
    for (i=1; i<=scount; ++i)
        if (!map[space[i][0]][space[i][1]])
        {
            tot = 0;
            memset(vst, 0, sizeof(vst));
            fill(space[i][0],space[i][1]);
            //printf("tot=%d s=%d",tot,scount-blocked);
            if (tot<scount-blocked)
            {
                //printf("(%d,%d) %d", space[i][0],space[i][1], tot);
                return true;
            } else
                return false;
        }
    return false;
}

inline int work()
{
    int x1,y1;
    if (scount==1 || scount==2)
        return -1;
    for (x1=1; x1<=n; ++x1)
        for (y1=1; y1<=m; ++y1)
            if (!map[x1][y1])
            {
                map[x1][y1]=true;
                blocked=1;
                if (check()) return 1;
                map[x1][y1]=false;
            }
    return 2;
}

int main()
{
    input();
    printf("%d\n", work());
    return 0;
}

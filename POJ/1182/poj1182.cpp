#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
const int rel[4][4]={{0,0,0,0},
          /*a-b b-c*/{0,3,1,2},
                     {0,1,2,3},
                     {0,2,3,1}};
const int relb[4][4]={{0,0,0,0},
          /*a-c b-c*/ {0,2,1,3},
                      {0,3,2,1},
                      {0,1,3,2}};
int father[50005];
int relation[50005];
int n,m;
int find(const int x)
{
    if (father[x]==x)
        return x;
    int fx=father[x];
    father[x]=find(father[x]);
    relation[x]=rel[relation[x]][relation[fx]];
    return father[x];
}

void mount(const int a, const int b, const int r)
{                                           //b->a
    int fa=find(a), fb=find(b);
    father[fa]=fb;
    relation[fa]=rel[relb[relation[a]][r]][relation[b]];
    father[fa]=fb;
}
bool check(const int a, const int b, const int c)
{
    if (a>n || b>n)
        return false;
    if (c==1)
    {
        find(a);
        find(b);
        if ((father[a]==father[b])&&(relation[a]!=relation[b]))
            return false;
    }
    if (c==2)
    {
        find(a);
        find(b);
        if (father[a]==father[b] && relation[a]==relation[b])
            return false;
        if (father[a]==father[b] && relb[relation[a]][relation[b]]!=1)
            return false;   
    }
    return true;
}
int fakeCount;

int main()
{
    scanf("%d%d", &n,&m);
    int i,cmd,x,y;
    for (i=1; i<=n; ++i)
    {
        father[i]=i;
        relation[i]=2;
    }
    for (i=1; i<=m; ++i)
    {
        scanf("%d%d%d", &cmd, &x, &y);
        if (!check(x,y,cmd))
        {
            ++fakeCount;
            puts("x");
        }
        else
        {
            if (cmd==1)
                mount(x,y,2);
            if (cmd==2)
                mount(x,y,3);
        }
    }
    printf("%d\n", fakeCount);
    system("pause");
    return 0;
}

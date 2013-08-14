#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
const char NOT_SURE[]="Not sure yet.";
const char DIFFERENT[]="In different gangs.";
const char SAME[]="In the same gang.";
using std::cin;
int n,m,test;
int father[100005*2];

int getFather(const int x)
{
    return (father[x]==x)?x:father[x]=getFather(father[x]);
}

void mount(const int a, const int b)
{
    father[getFather(a)]=getFather(b);
}

int main()
{  
    int i,x,y;
    char cmd;
    std::ios::sync_with_stdio(false);
    cin>>test;
    for (; test; --test)
    {
        cin>>n>>m; //std::cout<<n<<' '<<m;// gets(Endl);//puts("S");
        for (i=1; i<=n*2; ++i)     father[i]=i;
        for (i=1; i<=m; ++i)
        {
            //scanf("%c%d%d\n",&cmd,&x,&y);// puts("S");
            cin>>cmd>>x>>y;
           // printf("%c,%d,%d", cmd, x,y);
           // while(1);
            if (cmd=='D')
            {
                mount(x,y+n);
                mount(y,x+n);
            }
            else
            {
                if (getFather(x)==getFather(y+n) && getFather(x+n)==getFather(y))
                    puts(DIFFERENT);
                else if (getFather(x)==getFather(y) && getFather(x+n)==getFather(y+n))
                    puts(SAME);
                else
                    puts(NOT_SURE);
            }
        }
    }
    return 0;
} 

#include <cstdlib>
#include <cstdio>
#include <cstring>
#define HASHSIZE 2147483
#define MAXN 50005
int n;
char name[MAXN][220];
int next[MAXN];
int hash[HASHSIZE];
int count;
inline int BKDR(char arr[220])
{
    int base=131;
    int hash=0;
    for (int i=1;i<=strlen(arr);++i)
        hash=(hash*base+arr[i])%HASHSIZE;
    if (hash<0||hash>=HASHSIZE)
        hash+=HASHSIZE;
    return hash;
}

int find(char arr[220])
{
    int p,tmp;
    tmp=BKDR(arr);
    p=hash[tmp];
    while (p!=0)
    {
        if (strcmp(name[p],arr)==0)
            return(p);
        p=next[p];
    }
    return 0;
}

void work()
{
    char rd[220];
    scanf("%d\n",&n);
    for (int i=1;i<=n;++i)
    {
        gets(rd);
        int pos=find(rd);
        if (pos>0) printf("%d\n",i);
        else
        {
            int tmp=BKDR(rd);
            count++;
            strcpy(name[count],rd);
            next[count]=hash[tmp];
            hash[tmp]=count;
        }
    }
}

int main()
{
    work();
}

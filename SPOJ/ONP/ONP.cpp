#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
char str[1000];
int pri[1000];
int n;

void print(const int l, const int r)
{
    int minp=1<<30, mini=-1, i;
    for (i=l; i<=r; ++i)
        if (pri[i]<minp && pri[i]!=0)
        {
            minp=pri[i];
            mini=i;
        }
    if (mini>=0)
    {
        print(l,mini-1);
        print(mini+1, r);
        printf("%c", str[mini]);
    }
    else
    {
        for (i=l; i<=r; ++i)
            if (str[i]>='a' && str[i]<='z')
            {
                printf("%c", str[i]);
                break;
            }
    }
}

void process()
{
    gets(str);
    memset(pri,0,sizeof(pri));
    int high=0,p,len=strlen(str);
    for (p=0; p<len; ++p)
    {
        if (str[p]=='(')
            high+=3;
        if (str[p]==')')
            high-=3;
        if (str[p]=='^')
            pri[p]=high+3;
        if (str[p]=='*' || str[p]=='/')
            pri[p]=high+2;
        if (str[p]=='+' || str[p]=='-')
            pri[p]=high+1;
    }
    print(0,len-1);
    printf("\n");
}

int main()
{
    scanf("%d\n", &n);
    for (int i=1; i<=n; ++i)
        process();
    return 0;
} 

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;
typedef struct bigint
{
    int dig[500];
    int len;
} BigInt;

BigInt toBigInt(string str)
{
    BigInt tmp;
    tmp.len=0;
    memset(tmp.dig, 0, sizeof(tmp.dig));
    int buffer=0,base=1;
    for (int i=str.length()-1; i>=0; --i)
    {
        if ('0'<=str[i] && str[i]<='9')
        {
            buffer+=base*(int)(str[i]-'0');
            base*=10;
            if (base==10000)
            {
                tmp.dig[++tmp.len]=buffer;
                buffer=0;
                base=1;
            }
        }
    }
    if (buffer>0)
        tmp.dig[++tmp.len]=buffer;
    return tmp;
}

int compare(const BigInt a, const BigInt b)
{
    if (a.len>b.len)
    {
        return 1;
    }
    else if (a.len<b.len)
    {
        return -1;
    }
    else
    {
        for (int i=a.len; i>=1; --i)
        {
            if (a.dig[i]>b.dig[i])
            {
                return 1;
            }
            else if (a.dig[i]<b.dig[i])
            {
                return -1;
            }
        }
    }
    return 0;
}

BigInt Minus(const BigInt a, const BigInt b)
{
    BigInt c;
    c.len=0;
    memset(c.dig,0,sizeof(c.dig));
    int x=1;
    for (int i=1; i<=a.len; ++i)
    {
        x=x-1+10000+a.dig[i]-b.dig[i];
        c.dig[i]=x%10000;
        x/=10000;
    }
    c.len=a.len;
    while (c.dig[c.len]==0 && c.len>1)
        --c.len;
    return c;
}

void print(const BigInt x)
{
    for (int i=x.len; i>0; --i)
    {
        if (i!=x.len)
        {
            if (x.dig[i]<1000) printf("0");
            if (x.dig[i]<100) printf("0");
            if (x.dig[i]<10) printf("0");
        }
        printf("%d",x.dig[i]);
    }
    printf("\n");
}

int main()
{
    string s1,s2;
    cin>>s1>>s2;
    BigInt aa=toBigInt(s1), bb=toBigInt(s2);
    switch (compare(aa,bb))
    {
        case 0:
            puts("0");
            break;
        case 1:
            print(Minus(aa,bb));
            break;
        case -1:
            printf("-");
            print(Minus(bb,aa));
            break;
        default:
        ;
    }
    return 0;
}

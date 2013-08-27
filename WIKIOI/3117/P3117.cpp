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

BigInt Multi(const BigInt a, const BigInt b)
{
    BigInt c;
    c.len=0;
    memset(c.dig,0,sizeof(c.dig));
    for (int i=1; i<=a.len; ++i)
        for (int j=1; j<=b.len; ++j)
        {
            c.dig[i+j-1]+=a.dig[i]*b.dig[j];
            c.dig[i+j]+=c.dig[i+j-1]/10000;
            c.dig[i+j-1]%=10000;
        }
    for (int i=1; i<=a.len+b.len+1; ++i)
        {
            c.dig[i+1]+=c.dig[i]/10000;
            c.dig[i]%=10000;
        }
    c.len=a.len+b.len+1;
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
    print(Multi(bb,aa));

    return 0;
}

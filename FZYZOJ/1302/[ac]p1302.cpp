#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
struct TFrac
{
    int num,den;
};

TFrac x,y,res;
int n;

inline int gcd(int a, int b)
{
    int r=a%b;
    while (r)
    {
        a=b;
        b=r;
        r=a%b;
    }
    return b;
}

inline void simplify(TFrac &f)
{
    int g=gcd(abs(f.num), abs(f.den));
    f.num/=g;
    f.den/=g;
    if (f.den<0)
    {
        f.den*=-1;
        f.num*=-1;
    }
}

inline void convert(TFrac &a, TFrac &b)
{
    int g=gcd(abs(a.den), abs(b.den));
    int common=a.den/g*b.den;
    a.num*=(common/a.den);
    b.num*=(common/b.den);
    b.den=a.den=common;
}

inline TFrac minus(TFrac a, TFrac b)
{
    if (a.den!=b.den)
        convert(a,b);
    TFrac c;
    c.den=a.den;
    c.num=a.num-b.num;
    simplify(c);
    return c;
}

inline void printFrac(const TFrac t)
{
    if (t.den==1)
        printf("%d\n",t.num);
    else
        printf("%d/%d\n",t.num,t.den);
}

inline void readExp()
{
    char line[200];
    gets(line);
    int i,count,len=strlen(line),tmp=0,arg[4];
    for (i=0, count=0; i<=len; ++i)
    {
        if ('0'<=line[i] && line[i]<='9')
        {
            tmp=tmp*10+(line[i]-'0');
        }
        else
        {
            arg[count++]=tmp;
            tmp=0;
        }
    }
    x.num=arg[0];
    x.den=arg[1];
    y.num=arg[2];
    y.den=arg[3];
    simplify(x);
    simplify(y);
}

int main()
{
    int i;
    scanf("%d\n",&n);
    for (i=1; i<=n; ++i)
    {
        readExp();
        res=minus(x,y);
        printFrac(res);
    }
    return 0;
}

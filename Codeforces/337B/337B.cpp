#include <cstdio>
#include <cstdlib>
#include <cmath>

inline int gcd(int a, int b)
{
    if (a==0)
        return b; 
    int q; 
    do 
    {
        q=b%a;
        b=a;
        a=q;
    } while (q);
    return b;
}

int main()
{
    
    int a,b,c,d;

    scanf("%d%d%d%d", &a, &b,&c,&d);
    int gg=gcd(a,b);
    a/=gg;
    b/=gg;
    gg=gcd(c,d);
    c/=gg;
    d/=gg;
    // fit vetical
    int p,q;
    bool solved=false;
    {
        int commonHeight=b*d/gcd(b,d);
        int ScreenWidth=a*commonHeight/b;
        int FilmWidth=c*commonHeight/d;
        if (FilmWidth<=ScreenWidth)
        {
            solved=true;
            q=ScreenWidth;
            p=ScreenWidth-FilmWidth;
        }
    }
    if (!solved) // fit horizontal
    {
        int commonWidth=a*c/gcd(a,c);
        int ScreenHeight=b*commonWidth/a;
        int FilmHeight=d*commonWidth/c;
        if (FilmHeight<=ScreenHeight)
        {
            solved=true;
            q=ScreenHeight;
            p=ScreenHeight-FilmHeight;
        }
    }
    if (p==0)
        puts("0/1");
    else
    {
        int tmp=gcd(p,q);
        p/=tmp;
        q/=tmp;
        printf("%d/%d\n",p,q);
    }

    return 0;
}

#include <cstdio>
#include <cstring>
#include <cstdlib>
int missleCount=0, missleHeight[3000];
int f[3000];
int main()
{
    int rd;
    while (scanf("%d", &rd)!=EOF)
    {
        missleHeight[++missleCount]=rd;
    }
    memset(f,0,sizeof(f));
    //puts("done");
    f[missleCount]=1;
    int maxlen=0;
    for (int i=missleCount-1; i>0; --i)
    {
        for (int j=i+1; j<=missleCount; ++j)
            if (missleHeight[j]<=missleHeight[i])
                if (f[j]>f[i])
                    f[i]=f[j];
        f[i]+=1;
        if (f[i]>maxlen) maxlen=f[i];
    }
    int hh[300],ans=0;
    for (int i=1; i<=missleCount; ++i)
    {
        bool shoot=false;
        for (int j=1; j<=ans; ++j)
            if (missleHeight[i]<=hh[j])
            {
                shoot=true;
              //  printf("shot #%d @ %d with NO.%d(last:%d)\n", i, missleHeight[i],j,hh[j]);
                hh[j]=missleHeight[i];
                break;
            }
        if ((!shoot) || ans==0)
        {
       //     printf("shot #%d @ %d with NO.%d(last:%d)\n", i, missleHeight[i],ans+1,0);
            hh[++ans]=missleHeight[i];
        }
    }
    printf("%d\n%d\n",maxlen,ans);
    return 0;
}

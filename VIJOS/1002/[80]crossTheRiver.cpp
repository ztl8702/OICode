#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
int l;
int s,t,m;
int pos[105];
int f[200005];
bool stone[200005],vst[200005];
int main()
{
    scanf("%d", &l);
    scanf("%d%d%d", &s,&t,&m);
    for (int i=1; i<=m; ++i)
        scanf("%d", &pos[i]);
    std::sort(pos+1,pos+1+m);
    int reduced=0;
    if (pos[1]>=102)
    {
        reduced=pos[1];
        pos[1]=0;
    }
    for (int i=2; i<=m; ++i)
    {
        pos[i]-=reduced;
        if (i>1 && pos[i]-pos[i-1]>=102)
        {
            reduced+=pos[i]-pos[i-1];
            pos[i]=pos[i-1];
        }
        stone[pos[i]]=true;
    }
    l-=reduced;
    if (m>0 && l-pos[m]>=102)
    {
        reduced+=l-pos[m];
        l=pos[m];
    }
    memset(vst,false,sizeof(vst));
    f[0]=0;
    vst[0]=true;
    int min;
    for (int i=1; i<=l+10; ++i)
    {
        min=10000;
        for (int j=s; j<=t; ++j)
        {
            if (i-j>=0 && f[i-j]<min && vst[i-j])
            {
                vst[i]=true;
                min=f[i-j];
            }
        }
        if (stone[i])
            f[i]=1+min;
        else
            f[i]=min;
    }
    min=10000;
    for (int i=l; i<=l+10; ++i)
    {
        if (vst[i] && f[i]<min)
            min=f[i];

    }
    printf("%d\n",min);

    return 0;
}

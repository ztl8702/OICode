#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
char s[300];
int T;
int p,len;
bool vst[3][300][300];
bool value[3][300][300];
bool isList(const int, const int);
bool isSet(const int, const int);
bool isElement(const int, const int);

bool isElement(const int l, const int r)
{//printf("Ele(%d,%d) ",l,r); system("pause");
    if (vst[0][l][r])
        return value[0][l][r];
    vst[0][l][r]=true;
    if (l==r)
        return value[0][l][r]=true;
    else
        return value[0][l][r]=isSet(l,r);
}

bool isSet(const int l, const int r)
{
    if (vst[1][l][r])
        return value[1][l][r];  
    vst[1][l][r]=true;
    if (s[l]=='{' && s[r]=='}')
    {
  
        if (l+1==r)
            return value[1][l][r]=true;
        else
            return value[1][l][r]=isList(l+1, r-1);
    }
    else
        return value[1][l][r]=false;
}

bool isList(const int l, const int r)
{
    if (vst[2][l][r])
        return value[2][l][r];
    vst[2][l][r]=true;
    if (isElement(l,r))
        return value[2][l][r]=true;
    for (int i=l+1; i<=r-1; ++i)
        if (s[i]==',')
            if (isList(l,i-1) && isList(i+1, r))
                return value[2][l][r]=true;
    return value[2][l][r]=false;
}

void workOnce(const int id)
{
    gets(s);
    p=0;
    len=strlen(s);
    memset(vst,false, sizeof(vst));
    printf("Word #%d: %s\n", id, isSet(0, len-1)?"Set":"No Set");
}

int main()
{
    scanf("%d\n", &T);
    for (int foo=1; foo<=T; ++foo)
        workOnce(foo); system("pause");
    return 0;
}

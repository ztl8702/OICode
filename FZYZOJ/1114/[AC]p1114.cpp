#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
int n,r,c,count;
char str[105], temp[105][105];
int main()
{
    int i,j;
    gets(str);
    n=strlen(str);
    r=(int)floor(sqrt(n));
    for (;n%r&&r>1;--r);
    c=n/r;
    count=0;
    for (i=1; i<=c; ++i)
        for (j=1; j<=r; ++j)
        {
            temp[j][i]=str[count];
            ++count;
        }
    for (i=1; i<=r; ++i)
        for (j=1; j<=c; ++j)
        {
            printf("%c",temp[i][j]);
        }
    printf("\n");
    return 0;
}

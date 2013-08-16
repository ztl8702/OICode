#include <cstring>
#include <cstdlib>
#include <cstdio>

int n;
char str[1005];
int f[1005][1005];
int choice[1005][1005];
int dp(int l, int r)
{
    if (l>r) return 0;
    if (l==r) return 1;
    if (f[l][r]>-1)
        return f[l][r];
    if (str[l]==str[r])
    {
        f[l][r]=dp(l+1,r-1)+2;   
        choice[l][r]=1;
    }
    else
    {
        int left = dp(l+1,r);
        int right = dp(l,r-1);
        if (left>right)
        {
            f[l][r]=left;
            choice[l][r]=2;
        }
        else if (left<right)
        {
            f[l][r]=right;
            choice[l][r]=3;
        }
        else
        {
            f[l][r]=left;
            choice[l][r]=4;
        }
    }
    return f[l][r];
}

int main()
{

    int test;
    scanf("%d", &test);
    getc(stdin);
    /*VERY TRICKY
    if I change the two lines above to: 
        scanf("%d\n", &test);
    I will get WA on UVA.
    because in case of an empty line, the commented code will wait for a new line, 
    while the uncommented one will proceed and gives a "0" answer.
    
    Thus, must study the mechinary of scanf!
    */
    while (test--)
    {
        gets(str);
        n=strlen(str);
        if (n==0)
        {
            printf("0\n");
            continue;
        }
        memset(f,-1, sizeof(f));
       // memset(choice,0,sizeof(choice));
        printf("%d\n", dp(0,n-1));
    }

    return 0;
} 

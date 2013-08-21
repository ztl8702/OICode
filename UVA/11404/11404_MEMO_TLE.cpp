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
char sleft[1000];
char sright[1000];
char ans[2][1000];
int ansCount;
bool found;

void print(int l, int r, int llen, int rlen)
{
    if (found && sleft[llen-1]>ans[ansCount][llen-1])
    {
/*        puts("BREAK!");
        for (int i=0; i<llen; ++i)
            printf("%c", sleft[i]);
        puts("");
        for (int i=0; i<llen; ++i)
            printf("%c", ans[ansCount][i]);
        puts("");*/
        return;
    }
    if (l>r)
    {
        int newAns=ansCount^1;
        for (int i=0; i<llen; ++i)
            ans[newAns][i]=sleft[i];
        for (int i=0; i<rlen; ++i)
            ans[newAns][llen+i]=sright[rlen-i-1];
        ans[newAns][llen+rlen]='\0';
       // if ((!found) || strcmp(ans[newAns],ans[ansCount])<0)
        //{
            found=true;
            //puts("take it !");
            ansCount=newAns;
        //}
        //else
        //{
          //  puts("don't take!");
       // }
        //for (int i=0; i<strlen(ans[newAns]); ++i)
         //   printf("%c",ans[newAns][i]);
        //puts("");
        return;        
    }
    if (l==r)
    {
        if ((!found) || str[l]<ans[ansCount][llen])
        {
            int newAns=ansCount^1;
            for (int i=0; i<llen; ++i)
                ans[newAns][i]=sleft[i];
            ans[newAns][llen]=str[l];
            for (int i=0; i<rlen; ++i)
                ans[newAns][llen+1+i]=sright[rlen-i-1];
            ans[newAns][llen+1+rlen]='\0';
       //     if ((!found) || strcmp(ans[newAns], ans[ansCount])<0)
        //    {   
                found=true;
                ansCount=newAns;
          //      puts("take it !");
          //  }
           // else
       // {
        //    puts("don't take!");
        //}
           // for (int i=0; i<strlen(ans[newAns]); ++i)
              //  printf("%c",ans[newAns][i]);
            //p\uts("");
        }
        /*else{
        printf("%d(%d):", ansCount,strlen(ans[ansCount]));
        for (int i=0; i<strlen(ans[ansCount]); ++i)
            printf("%c",ans[ansCount][i]);
        puts("");}*/
        return;
    }
    switch (choice[l][r])
    {
        case 1:
           // if ((!found) || str[l]<=ans[ansCount][llen])
            {
                sleft[llen]=str[l];
                sright[rlen]=str[r];
                print(l+1,r-1,llen+1,rlen+1);
            }    
            break;
        case 2:
            print(l+1, r,llen,rlen);
            break;
        case 3:
            print(l,r-1,llen,rlen);
            break;
        case 4:
            print(l, r-1,llen,rlen);
            print(l+1, r,llen,rlen);
            break;
        default:
            ;
    }
    
} 

int main()
{
    while (gets(str)!=NULL)
    {
        n=strlen(str);
        if (n==0)
        {
            printf("0\n");
            continue;
        }
        memset(f,-1, sizeof(f));
       // memset(choice,0,sizeof(choice));
         dp(0,n-1);
        found=false;
        ansCount=0;
        print(0,n-1,0,0);
        
        puts(ans[ansCount]);
    }

    return 0;
} 

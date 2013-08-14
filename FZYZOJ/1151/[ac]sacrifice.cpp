#include <cstdio>
#include <cstdlib>
#include <cstring>
#define FILLCHAR(A,X) memset(A,X,sizeof(A))
/*
   FZYZOJ 1151
   sacrifice
*/
const int MAXN=1000000;
int n,m,testcase;
int dcount, drt[15];
int rmdTen;
int QHead, QTail;
int Q[5000000][4]; //0:len, 1:rmd, 2:father, 3:choice;
bool vst[MAXN+5];
int Ans[5000000];
inline void Input()
{
    bool tmp[10]={};
    int i,rd;
    scanf("%d%d",&n,&m);
    for (i=1; i<=m; ++i)
    {
        scanf("%d",&rd);
        tmp[rd]=true;
    }
    dcount=0;
    for (i=0; i<10; ++i)
        if (tmp[i]) drt[++dcount]=i;
    rmdTen=10%n;
}

inline void Output()
{
    int i,count=0;
    for (i=QTail; i>0; i=Q[i][2])
        Ans[++count]=Q[i][3];
    for (i=count; i>0; --i)
        printf("%d",Ans[i]);
    printf("\n");
}

int search()
{
    int i,len,r,newNum;
    FILLCHAR(vst,false);
    QHead=QTail=0;
    for (i=(drt[1]==0)+1; i<=dcount; ++i)
    {
        ++QTail;
        Q[QTail][0]=1;
        Q[QTail][1]=drt[i]%n;
        Q[QTail][2]=0;
        Q[QTail][3]=drt[i];
        if (!vst[Q[QTail][1]])
        {
            vst[Q[QTail][1]]=true;
            if (Q[QTail][1]==0)
            {
                Output();
                return 1;
            }
        }
        else
            --QTail;
    }
    while (QHead<QTail)
    {
        ++QHead;
        len=Q[QHead][0];
        r=Q[QHead][1];
        for (i=1; i<=dcount; ++i)
        {
            newNum=(int)((long long)r*rmdTen+drt[i])%n;
            if (!vst[newNum])
            {
                vst[newNum]=true;
                ++QTail;
                Q[QTail][0]=len+1;
                Q[QTail][1]=newNum;
                Q[QTail][2]=QHead;
                Q[QTail][3]=drt[i];
                if (newNum==0)
                {
                    Output();
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("sacrifice.in","r",stdin);
    freopen("sacrifice.out","w",stdout);
#endif
    scanf("%d",&testcase);
    for (int i=1; i<=testcase; ++i)
    {
        Input();
        if (search()==0)
            printf("0\n");;
    }
    return 0;
}

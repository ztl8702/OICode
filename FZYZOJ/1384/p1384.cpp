#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using std::swap;
using std::max;
using std::min;
using std::abs;
const int power[]={1,10,100,1000,10000,100000};
const int INF=2147483600;

struct TStatus
{
    int num;
    bool swap1;
    int maxright, pos, step;
} start, fi;

int target[6],vst[1000000][6][6][2];
int QHead, QTail;
TStatus Q[9000000];
int ans=INF;

inline void InQueue(const int num, const int pos,const bool swap1, const int maxright, const int ss)
{
    ++QTail;
    vst[num][pos][maxright][swap1]=true;
    Q[QTail].num=num;
    Q[QTail].swap1=swap1;
    Q[QTail].maxright=maxright;
    Q[QTail].pos=pos;
    Q[QTail].step=ss;
}

inline int getAns(const int h)
{
    int res=Q[h].step, tmp=Q[h].num;
    for (int i=0; i<=5; ++i, tmp/=10)
        if ((tmp%10)!=target[i])
        {
            if (Q[h].maxright>=i || (i==5 && Q[h].swap1))
                res+=abs((tmp%10) - target[i]);
            else
                return INF;
        }
    return res;
}

void search()
{
    //int QHead=0, QTail=0;
    InQueue(start.num, 0, false, 0, 0);
    while (QHead<QTail)
    {
        
        ++QHead;
        //printf("[%d]\n", Q[QHead].num);
        
        if (Q[QHead].step>=ans)
            break;
        ans=min(ans, getAns(QHead));
        /*Swap0*/
        int num=Q[QHead].num,position=Q[QHead].pos,newnum,n1,n2,step=Q[QHead].step;
        if (Q[QHead].pos!=0)
        {
            n1=num%10;
            n2=num%(power[position]*10)/power[position];
            newnum=num+power[position]*(n1-n2)+(n2-n1);
            if (!vst[newnum][position][Q[QHead].maxright][Q[QHead].swap1])
                InQueue(newnum, position, Q[QHead].swap1, Q[QHead].maxright, step+1);
        }
        /*Swap1*/
        if (Q[QHead].pos!=5)
        {
            n1=num/power[5];
            n2=num%(power[position]*10)/power[position];
            newnum=num+power[position]*(n1-n2)+power[5]*(n2-n1);
            if (!vst[newnum][position][Q[QHead].maxright][true])
                InQueue(newnum, position, true, Q[QHead].maxright, step+1);
        }
        /*Left*/
        if (Q[QHead].pos>0)
            if (!vst[num][position-1][position][Q[QHead].swap1])
                InQueue(num, position-1, Q[QHead].swap1, Q[QHead].maxright, step+1);
        /*Right*/
        if (Q[QHead].pos<5)
            if (!vst[num][position+1][max(Q[QHead].maxright, position+1)][Q[QHead].swap1])
                InQueue(num, position+1, Q[QHead].swap1, max(Q[QHead].maxright, position+1), step+1);
    }
    printf("%d\n", ans);
}

int main()
{
    char rd[100];
    scanf("%s", rd);
    for (int i=0; i<=5; ++i)
        start.num+=power[i]*(rd[i]-'0');
    scanf("%s", rd);
    for (int i=0; i<=5; ++i)
    {
        target[i]=rd[i]-'0';
    }
    search();
    return 0;
}

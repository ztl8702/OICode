#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define COUNTONE(X) countOne[(X)+65536]
const int BITSET_SHIFT=5; //2^5=3;
const int BITSET_MASK=(1<<5)-1;
const int BITSET_MAX=512;
const int BITSET_SIZE=BITSET_MAX/32;
const int MAXX=100005;
const int MAXN=1005;

inline int lowbit(const int x)
{
    return  x&(-x);
}
struct TBitSet
{
    int bits[BITSET_SIZE+1];
    void set(int x)
    {
        bits[x>>BITSET_SHIFT]|=1<<(x&BITSET_MASK);
    }
    void clear(int x)
    {
        bits[x>>BITSET_SHIFT]&=~(1<<(x&BITSET_MASK));   
    }
    bool test(int x)
    {
        return (bool)(bits[x>>BITSET_SHIFT]&(1<<(x&BITSET_MASK)));
    }
}ocr[MAXX];
int sum[MAXX];
int countOne[(1<<17)+5];
const int MASK=((1<<16)-1);
void initCountOne()
{
    int i,tmp;
    for (i=-65536; i<=+65536; ++i)
    {
        tmp=i&MASK;
        while (tmp)
        {
            ++COUNTONE(i);
            tmp-=lowbit(tmp);
        }
    }
}

int n, ans[MAXN], num[MAXN][MAXN];

inline int getJiao(const TBitSet &a, const TBitSet &b)
{
    int tmp,i,count=0;
    for (i=0; i<=BITSET_SIZE-1; ++i)
    {
        tmp=a.bits[i]&b.bits[i];
        count+=COUNTONE(tmp>>16)+COUNTONE(tmp&MASK);
    }
    return count;
}


void input()
{
    int i,j;
    scanf("%d", &n);
    for (i=1; i<=n; ++i)
    {
        scanf("%d", &num[i][0]);
        for (j=1; j<=num[i][0]; ++j)
        {
            scanf("%d", &num[i][j]);
            if (!ocr[num[i][j]].test(i))
            {
                ++sum[num[i][j]];
                ocr[num[i][j]].set(i);
            }
        }
    }
    
}

void work()
{
    int i,r1,r2,same;
    for (i=1; i<=n; ++i)
    {
        for (r1=1; r1<num[i][0]; ++r1)
            for (r2=r1+1; r2<=num[i][0]; ++r2)
            {
                same=getJiao(ocr[num[i][r1]],ocr[num[i][r2]]);
                ans[i]+=(sum[num[i][r1]]-same)*(sum[num[i][r2]]-same);
            }
    }
    for (i=1; i<=n-1; ++i)
        printf("%d ", ans[i]);
    printf("%d\n",ans[n]);
}


int main()
{
    
    
   // printf("%d", BITSET_SIZE);
    initCountOne();
    //printf("%d(%d) %d(%d)", -2046752704>>16,COUNTONE(-2046752704>>16), -2046752704&MASK,COUNTONE(-2046752704&MASK));
    input();
    work();
    system("pause");
    return 0;
}

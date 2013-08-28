#include <cstdio>
#include <cstring>
#include <cstdlib>
const int MAXN=30005;
int n,k;
int h[MAXN];
typedef struct qu
{
    int head, tail;
    bool great;
    int ind[MAXN];
    int value[MAXN];

    inline bool cmp(const int a, const int b)
    {
        if (great)
            return a>b;
        else
            return a<b;
    }

    bool empty()
    {
        return (head==tail);
    }

    void add(const int index, const int v)
    {
        while (head<tail && cmp(v,value[tail]))
            --tail;
        ++tail;
        value[tail]=v;
        ind[tail]=index;
    }

    void pop(const int indexLimit)
    {
        while (head<tail && ind[head+1]<indexLimit)
            ++head;
    }

} QQQ;
QQQ min, max;

int main()
{
    scanf("%d%d", &n, &k);
    min.great=false;
    max.great=true;
    int now;
    int maxLen=1;
    int left=1;
    for (int i=1; i<=n; ++i)
    {
        scanf("%d", &now);
        min.add(i,now);
        max.add(i,now);
        //printf("i=%d min=%d, max=%d\n",i,min.value[min.head+1],max.value[max.head+1]);
        while ((left<i) && (!min.empty()) && (!max.empty()) && (max.value[max.head+1]-min.value[min.head+1]>k))
        {
            ++left;
            min.pop(left);
            max.pop(left);
        }


        if (i-left+1>maxLen)
            maxLen=i-left+1;
    }
    printf("%d\n", maxLen);
    return 0;
}

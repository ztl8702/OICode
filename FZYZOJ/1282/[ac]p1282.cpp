#include <cstdio>
#include <cstring>
#include <cstdlib>
const int INF = 2147483600;
int n, rd, fi, gi, minSum, maxSum, sum;
int main()
{
    int i;
    scanf("%d",&n);
    maxSum=-INF;
    minSum=INF;
    for (i=1; i<=n; ++i)
    {
        scanf("%d",&rd);
        sum+=rd;
        fi=fi>0?fi+rd:rd;
        gi=gi<0?gi+rd:rd;
        minSum=gi<minSum?gi:minSum;
        maxSum=fi>maxSum?fi:maxSum;
    }
    printf("%d\n",sum-minSum>maxSum?sum-minSum:maxSum);
    return 0;
}

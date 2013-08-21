#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
const int MAXN=105;
const int OFFSET=1005;
typedef struct segment
{
    int left,right;
} Segment;
Segment lines[MAXN];
int rightPointCount=0,rightPoint[MAXN],rightIndex[MAXN];
int rightReverseIndex[OFFSET*2];

int sortCmp(const Segment a, const Segment b)
{
    return (a.right<b.right) || (a.right==b.right && a.left>b.left);
}

inline int findRightPoint(const int target, const int limitL, const int limitR)
{
    for (int i=limitL; i<=limitR; ++i)
        if (target<=lines[rightIndex[i]].left)
            return i;
    return -1;
}

inline int findSegment(const int target, const int rangeL, const int rangeR)
{
    int l=rangeL, r=rangeR, mid;
    while (l<r)
    {
        mid=(l+r+1)>>1;
        if (lines[mid].left>=target)
            l=mid;
        else
            r=mid-1;
    }
    return l;
}

int main()
{
    int n;
    scanf("%d", &n);
    for (int i=1; i<=n; ++i)
    {
        scanf("%d%d", &lines[i].left, &lines[i].right);
        if (lines[i].left>lines[i].right)
        {
            int tmp=lines[i].left;
            lines[i].left=lines[i].right;
            lines[i].right=tmp;
        }
    }
    std::sort(lines+1, lines+n+1, sortCmp);
  /*for (int i=1; i<=n; ++i)
    {
        printf("%d _ %d\n", lines[i].left,lines[i].right);
    }*/
        rightPointCount=0;
    for (int i=1; i <= n ; ++i)
    {
        if (i==1 || lines[i].right!=lines[i-1].right)
        {
            rightPoint[++rightPointCount]=lines[i].right; //a new right point value that has occured;
            rightIndex[rightPointCount]=i; //first segment that ends with rightPoint[rightPointCount];
            rightReverseIndex[lines[i].right+OFFSET]=rightPointCount; //the id of value lines[i].right;
        }
    }
   // puts("done");
    int ans=0,lastRight=-1000,i=1,j;
    while (i>0)
    {
        i=findRightPoint(lastRight,rightReverseIndex[lastRight+OFFSET]+1,rightPointCount); //find the rightpointblockstart where first left point>=lastRight
       // printf("i=%d\n",i);
        if (i>0)
        {
         //   printf("looking for j from %d to  %d", rightIndex[i],(i==rightPointCount)?n:(rightIndex[i+1]-1));
            j=findSegment(lastRight,rightIndex[i],(i==rightPointCount)?n:(rightIndex[i+1]-1)); //find the first segment whose left point>=lastRight;
            ++ans;
            lastRight=lines[j].right;
           // printf("[%d,%d]\n",lines[j].left,lines[j].right);
        }
    }
    printf("%d\n",ans);
    return 0;
}

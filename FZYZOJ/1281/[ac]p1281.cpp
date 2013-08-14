/*
 * OJ 1281
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LSON(x) ((x)<<1)
#define RSON(x) (((x)<<1)+1)
const int MAXN=1000005;

int heap[1000005];
int n,heapcount;
int mark[MAXN],next[MAXN],start[700005];
int maxlimit;
/* Table */
inline int PARENT(int x)
{ return (x)>>1;}
inline void AddWork(const int wid,const int limit,const int value)
{
	mark[wid]=value;
	next[wid]=start[limit];
	start[limit]=wid;
}

/* Heap */

void Insert(const int key)
{
	heap[++heapcount]=key;
	int p=heapcount;
	while ((p>1) && (heap[PARENT(p)]< key))
	{
		heap[p] = heap[PARENT(p)];
		p = PARENT(p);
	}
	heap[p] = key;
	return;
}

int GetMax()
{
	int i,j;
	if (heapcount==0) return 0;
	int ans=heap[1];
	heap[1]  = heap[heapcount];
	int key=heap[1];
	heapcount--;
	i=1;
	j=LSON(i);
	while (j<=heapcount)
	{
		int maxi=-1;
		int max=key;
		if (j<=heapcount&&heap[j]>max) {max=heap[j]; maxi=j;}
		if (j+1<=heapcount&&heap[j+1]>max) {max=heap[j+1]; maxi=j+1;}
		if (maxi==-1) break;
		heap[i]=heap[maxi];
		i=maxi;
		j=LSON(i);
	}
	heap[i]=key;
	return ans;
}

/* MAIN */
inline void ReadData()
{
	int a,b;
	int max=0;
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
	{
		scanf("%d%d",&a,&b);
		AddWork(i,a,b);
		max=a>max?a:max;
	}
	maxlimit=max;
}

inline void Process()
{
	int ans=0;
	for (int i=maxlimit;i>0;--i)
	{
		for (int p=start[i];p!=0;p=next[p])
			Insert(mark[p]);
		ans+=GetMax();
	}
	printf("%d\n",ans);
}

int main()
{
	ReadData();
	Process();
	return 0;
}

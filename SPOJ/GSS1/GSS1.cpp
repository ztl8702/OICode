#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#define FILLCHAR(A,X) memset(A,X,sizeof(A))
#define PRT(X) (X>>1)
#define LSON(X) (X<<1)
#define RSON(X) ((X<<1)+1)
const int MAXN = 50005;
struct TNode
{
	int l,r;
	int max, lmax, rmax, sum;
} tree[MAXN*4];
int a[MAXN];
int n,m;
inline int getMax(int a, int b)
{
	return a>b?a:b;
}
inline void maintain(int x)
{
	tree[x].lmax=getMax(tree[LSON(x)].lmax,tree[LSON(x)].sum+tree[RSON(x)].lmax);
	tree[x].rmax=getMax(tree[RSON(x)].rmax,tree[RSON(x)].sum+tree[LSON(x)].rmax);
	tree[x].max=getMax(getMax(tree[LSON(x)].max, tree[RSON(x)].max), tree[LSON(x)].rmax+tree[RSON(x)].lmax);
	tree[x].sum=tree[LSON(x)].sum+tree[RSON(x)].sum;
}

inline TNode getAns(const int x, const int left, const int right)
{
	//printf("getAns(%d)\n",x);
	if (left<=tree[x].l && tree[x].r<=right) 
		return tree[x];
	int mid=(tree[x].l+tree[x].r)>>1;
	if (mid<left)
		return getAns(RSON(x),left,right);
	if (right<mid+1)
		return getAns(LSON(x),left,right);
	TNode ans={0},tmpl=getAns(LSON(x),left,right),tmpr=getAns(RSON(x),left,right);
	ans.lmax=getMax(tmpl.lmax,tmpl.sum+tmpr.lmax);
	ans.rmax=getMax(tmpr.rmax,tmpr.sum+tmpl.rmax);
	ans.max=getMax(getMax(tmpl.max, tmpr.max), tmpl.rmax+tmpr.lmax);
	ans.sum=tmpl.sum+tmpr.sum;
	return ans;
}

inline void build(int now, int left, int right)
{
	tree[now].l=left;
	tree[now].r=right;
	if (left==right)
		tree[now].lmax=tree[now].rmax=tree[now].sum=tree[now].max=a[left];
	if (left<right)
	{
		int mid=(left+right)>>1;
		build(LSON(now),left,mid);
		build(RSON(now),mid+1,right);
		maintain(now);
	}
}

inline void work()
{
	int i,x,y;
	scanf("%d",&n);
	for (i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	//puts("READ");
	build(1,1,n);
	scanf("%d",&m);
	for (i=1; i<=m; ++i)
	{
		scanf("%d%d",&x,&y);
		printf("%d\n",getAns(1,x,y).max);
	}
}

int main()
{
	work();
    return 0;
}

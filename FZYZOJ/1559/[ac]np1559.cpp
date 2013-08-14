#include <cstdio>
#include <cstdlib>
#include <cstring>
//tree
const int MAXN=205;
const int MAXM=205;
struct TTreeNode
{
	int id,score;
	TTreeNode *son,*brother;
} tree[MAXN];
int n,m;
int f[MAXN][MAXM],ans;
inline void addSon(const int target, const int son)
{
	if (tree[target].son==NULL)
	{
		tree[target].son=&tree[son];
	}
	else
	{
		tree[son].brother=tree[target].son;
		tree[target].son=&tree[son];
	}
}

inline int getMax(const int a, const int b)
{
	return (a>b?a:b);
}

int dp(const int now, const int rm)
{
	if (f[now][rm]>=0)
		return f[now][rm];
	int i,tmp=0;
	f[now][rm]=(tree[now].brother!=NULL)?dp(tree[now].brother->id,rm):0;
	if (rm>1)
	{
		if (tree[now].brother!=NULL && tree[now].son!=NULL)
		{
			for (i=0; i<=rm-1; ++i)
				tmp=getMax(tmp,dp(tree[now].brother->id,i)+dp(tree[now].son->id,rm-i-1));
		}
		else
		{
			if (tree[now].brother!=NULL)
				tmp=getMax(tmp,dp(tree[now].brother->id,rm-1));
			if (tree[now].son!=NULL)
				tmp=getMax(tmp,dp(tree[now].son->id, rm-1));
		}
	    
	}
	f[now][rm]=getMax(f[now][rm],tmp+tree[now].score);
	//printf("f[%d][%d]=%d ", now, rm, f[now][rm]);
	return f[now][rm];
}

inline void work()
{
	memset(f,-1,sizeof(f));
	for (int i=1; i<=n; ++i)
		f[i][0]=0;
	ans=dp(n+1,m+1);
}

inline void input()
{
	int i,tmp;
	scanf("%d%d",&n,&m);
	for (i = 1; i <= n; ++i)
	{
		tree[i].id=i;
		scanf("%d%d",&tmp,&tree[i].score);
		if (tmp) 
			addSon(tmp, i);
		else
			addSon(n+1, i);
	}
}

int main()
{
	input();
	work();
	printf("%d\n",ans);
	/*for (int i=1; i<=n+1; ++i)
	{
		printf("(%d) score=%d son=%d, bro=%d\n",tree[i].id,tree[i].score, (tree[i].son!=NULL)?tree[i].son->id:-1, (tree[i].brother!=NULL)?tree[i].brother->id:-1);
	}*/
	return 0;
}

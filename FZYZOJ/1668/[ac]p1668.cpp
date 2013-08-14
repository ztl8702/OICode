/* 
 * FZYZ OJ P1668
 */
#include <cstdio>
#include <cstring>
#define FILLCHAR(ARR,VAL) memset(ARR,VAL,sizeof(ARR))
int Q[1005],next[3][200000],va[3][200000],vb[3][200000],count[3],start[3][1005],tot[1005],c[1005];
bool vst[1005],map[1005][1005];
int n,m,ColorCount,QTail,Least,Most;
namespace Graph
{
	inline void add(int swc,int a,int b)
	{
		++count[swc];
		va[swc][count[swc]]=a;
		vb[swc][count[swc]]=b;
		next[swc][count[swc]]=start[swc][a];
	    start[swc][a]=count[swc];
	}
	
	void dfs(int i)
	{
		vst[i]=true;
		for (int p=start[0][i];p;p=next[0][p])
			if (!vst[vb[0][p]])
				dfs(vb[0][p]);
		Q[++QTail]=i;
	}
	
	void dfs2(int i,int col)
	{
		c[i]=col;
		tot[col]++;
		for (int p=start[1][i];p;p=next[1][p])
			if (c[vb[1][p]]==0)
				dfs2(vb[1][p],col);
	}
	
	void passOn(int a,int b)
	{
		map[a][b]=true;
		for (int p=start[2][b];p;p=next[2][p])
			if (a!=vb[2][p] && !map[a][vb[2][p]])
				passOn(a,vb[2][p]);
	}
}
int main()
{
	int i,j,r1,r2,tmp;
	bool needed;
	scanf("%d%d\n",&n,&m);
	for (i=1;i<=m;++i)
	{
		scanf("%d%d",&r1,&r2);
		if (r1!=r2)
		{
			++tmp;
			Graph::add(0,r1,r2);
			Graph::add(1,r2,r1);
		}
	}
	m=tmp;
	QTail=0;
	for (i=1;i<=n;++i)
		if (!vst[i])
			Graph::dfs(i);
	for (i=QTail;i>0;--i)
		if (c[Q[i]]==0)
		{
			Graph::dfs2(Q[i],++ColorCount);
			if (tot[ColorCount]>1)
				Least+=tot[ColorCount];
		}
	for (i=1;i<=count[0];++i)
		if (c[va[0][i]] != c[vb[0][i]] && !map[c[va[0][i]]][c[vb[0][i]]])
		{
			Graph::add(2,c[va[0][i]],c[vb[0][i]]);
			map[c[va[0][i]]][c[vb[0][i]]]=true;
		}
	//puts("DFS2 DONE");
	FILLCHAR(map,false);
	for (i=1;i<=ColorCount;++i)	Graph::passOn(i,i);
	//puts("PASSON DONE");
	for (i=1;i<=count[2];++i)
	{
		needed=true;
		for (j=1;j<=ColorCount;++j)
			if (j != va[2][i] && j != vb[2][i]
			     && map[va[2][i]][j] && map[j][vb[2][i]])
			{
				needed=false;
				break;
			}
		if (needed) ++Least;
	}
	for (i=1;i<=ColorCount;++i)
	{
		Most+=tot[i]*(tot[i]-1);
		for (j=1;j<=ColorCount;++j)
			if (i!=j && map[i][j])
				Most+=tot[i]*tot[j];
	}
	printf("%d %d\n",Least,Most);
	return 0;
}

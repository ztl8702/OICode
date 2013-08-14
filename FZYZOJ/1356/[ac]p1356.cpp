/*
 * FZYZ OJ
 * P1356
 * 8 May 2012
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#define FILLCHAR(A,X) memset(A,X,sizeof(A));
const int INF=2147483600;
const int MAXN=2000;
const int MAXM=MAXN*MAXN*3;
int n,m;
bool vst[MAXN];
namespace NW
{
	struct __a{int endv,next,cap;} E[MAXM];
	int head[MAXN],nowhead[MAXN],d[MAXN],gap[MAXN];
	struct __b{int aug,preEdge,path;} stack[MAXN];
	int ecount=1,fsum=0,Vcount,Source,Sink;
	inline void addEdge(const int a, const int b, const int c)
	{
		++ecount;
		E[ecount].endv=b;
		E[ecount].cap=c;
		E[ecount].next=head[a];
		head[a]=ecount;
		++ecount;
		E[ecount].endv=a;
		E[ecount].cap=0;
		E[ecount].next=head[b];
		head[b]=ecount;
	}
	void sap()
	{
		int aug=INF,x=Source,p;
		bool flag;
		FILLCHAR(d,0);
		FILLCHAR(gap,0);
		FILLCHAR(stack,0);
		gap[0]=Vcount;
		memcpy(nowhead,head,sizeof(head));
		while (d[Source]<Vcount)
		{
			flag=false; 
			stack[x].aug=aug;
			//printf("[%d] ",x); if (x==0) break;
			for (p=nowhead[x]; p; p=E[p].next)
				if (E[p].cap && d[E[p].endv]+1==d[x])
				{
					flag=true;
					nowhead[x]=p;
					aug=std::min(aug,E[p].cap);
					stack[E[p].endv].preEdge=p; stack[E[p].endv].path=x;
					x=E[p].endv;
					if (x==Sink)
					{
						fsum+=aug;
						for (; x!=Source; x=stack[x].path)
						{
							E[stack[x].preEdge].cap-=aug;
							E[stack[x].preEdge^1].cap+=aug;
						}
						aug=INF;
					}
					break;
				}
			if (!flag)
			{
				int i,minD=Vcount,minIndex=0,tmp;
				for (i=head[x]; i; i=E[i].next)
					if (E[i].cap && minD>d[E[i].endv])
					{
						minD=d[E[i].endv];
						minIndex=i;
					}
				nowhead[x]=minIndex;
				tmp=d[x];
				d[x]=minD+1;
				++gap[d[x]];
				if (--gap[tmp]==0)break;
				if (x!=Source)
				{
					x=stack[x].path;
					aug=stack[x].aug;
				}
			}
		}
	}
}
void dfs(const int now)
{
	using namespace NW;
	if (!(now>n && now<=n*2)||vst[now-n]) return;
	printf(" %d",now-n);
	vst[now-n]=true;
	for (int i=head[now-n]; i; i=E[i].next)
		if (E[i].cap==0)
			dfs(E[i].endv);
}
inline void Input()
{
	//using namespace NW;
	int a,b;
	scanf("%d%d",&n,&m);
	NW::Source=2*n+1;
	NW::Sink= 2*n+2;
	NW::Vcount=2*n+2;
	for (int i=1; i<=n; ++i)
	{
		NW::addEdge(NW::Source,i,1);
		NW::addEdge(i+n,NW::Sink,1);
	}
	for (int i=1; i<=m; ++i)
	{
		scanf("%d%d",&a,&b);
		NW::addEdge(a,b+n,1);
	}
}
inline void Output()
{
	using namespace NW;
	int i,p;
	FILLCHAR(vst,false);
	for (i=1; i<=n; ++i)
		if (!vst[i]) {
			vst[i]=true;
			printf("%d",i);
			for (p=head[i]; p; p=E[p].next)
				if (E[p].cap==0)
					dfs(E[p].endv);
			printf("\n");
		}
	printf("%d\n",n-fsum);
}
int main()
{	
	Input();
	NW::sap();
	Output();
	return 0;
}

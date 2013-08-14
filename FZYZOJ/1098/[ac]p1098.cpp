#include <cstdio>
#include <cstdlib>
#include <cstring>
int n,t;
int next[10005][10];
int suc[10005];
char move[10005];
char rd[10005];
void init()
{
	memset(next[t],-1,sizeof(next[t]));
    for (int i=t-1;i>=0;--i)
    {
		memcpy(next[i],next[i+1],sizeof(next[i]));
		next[i][(int)move[i]-'0']=i;
	}
}

bool check(int code)
{
	int c[4];
	for (int i=0;i<4;++i)
	{
		c[i]=code % 10;
	    code /= 10;
	}
	//printf("%d-%d %d %d %d",code,c[0],c[1],c[2],c[3]);
	int i=0;
	int p=next[0][c[0]];
	while (p!=-1)
	{
		i++;
		if (i==4) return 1;
		p=next[p][c[i]];
	}
	return 0;
}

void readdata()
{
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
	{
		int len;
		scanf("%d ",&len);
		gets(rd);
		//puts(rd);
		t=0;
		move[0]=rd[0];
		for (int j=1;j<len;++j)
			if (rd[j]!=rd[j-1])
			    move[++t]=rd[j];
		t++;
		init();
		for (int j=0;j<10000;++j)
	       if (check(j))
	         ++ suc[j];
	}
	int ans=0;
	for (int i=0;i<10000;++i)
	  if (suc[i]==n) 
	    ++ans;
	printf("%d",ans);
}

int main()
{
	readdata();
	return 0;
}

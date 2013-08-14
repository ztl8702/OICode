#include <cstdio>
#include <cstdlib>
#include <cstring>
int p1,p2,p3;
char rd[105];
char out[10005];
int tot;

inline void fillone(const char now)
{
	for (int k=1;k<=p2;++k)
	{
		if (p1==2&&now>='a'&&now<='z')
		{
			out[tot++]=now-32;
		} else
		if (p1==3) out[tot++]='*';
		else out[tot++]=now;
	}
}

void work()
{
	int len=strlen(rd);
	tot=0;
	for (int i=0;i<len;++i)
	{
		if (rd[i]=='-'&&i>0&&i<len-1)
			if (((rd[i-1]>='0'&&rd[i-1]<='9'&&rd[i+1]>='0'&&rd[i+1]<='9')||(rd[i-1]>='a'&&rd[i-1]<='z'&&rd[i+1]>='a'&&rd[i+1]<='z'))&&rd[i-1]<rd[i+1])
			{
			    if (p3==1)
					for (int j=(int)rd[i-1]+1;j<=(int)rd[i+1]-1;++j) fillone((char)j);
				else
					for (int j=(int)rd[i+1]-1;j>=(int)rd[i-1]+1;--j) fillone((char)j);
				out[tot++]=rd[i+1];
				++i;
				continue;
			}

		out[tot++]=rd[i];
	}
}

int main()
{
	scanf("%d%d%d\n",&p1,&p2,&p3);
	gets(rd);
	work();
	for (int i=0;i<tot;++i)
	  printf("%c",(char)out[i]);
	return 0;
}

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define MAXLEN 400005

using namespace std;

int pre[MAXLEN];
char str[MAXLEN];
int out[MAXLEN];

void processOnce()
{
	int tot=0;
	int len,j;
	memset(pre,0,sizeof(pre));
	len=strlen(str);
	j=0;
	pre[1]=0;
	for (int i=2;i<=(int)len;++i)
	{
		while (j>0&&str[j]!=str[i-1]) 
			j=pre[j];
		if (str[j]==str[i-1]) j++;
		pre[i]=j;
	}
	for (int p=len;p>0;p=pre[p])
	{
		out[++tot]=p;
	}
	for (int i=tot;i>1;--i)
		printf("%d ",out[i]);
	printf("%d\n",out[1]);
}

int main()
{
	#ifndef ONLINE_JUDGE
	freopen("p1677.in","r",stdin);
	freopen("p1677.out","w",stdout);
	#endif
	while (gets(str)!=NULL)
		processOnce();
	return 0;
	
}

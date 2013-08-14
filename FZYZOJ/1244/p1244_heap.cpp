#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define FILLCHAR(A,X) memset(A,X,sizeof(A))
#define LSON(X) ((X)<<1)
#define RSON(X) (((X)<<1)+1)
#define PRT(X) ((X)>>1)

const int SIZE=10005;
int n;

class THeap
{
	private:
		inline void swap(int a,int b)
		{
			int tmp=heap[a];
			heap[a]=heap[b];
			heap[b]=tmp;
		}
		inline void rise()
		{
			int p=count;
			while (p>1 && heap[p]<heap[PRT(p)])
			{
				swap(p,PRT(p));
				p=PRT(p);
			}
		}
		inline void sink()
		{
			int p=1,smallest;
			while (p<count)
			{
				smallest=p;
				smallest=(LSON(p)<=count && heap[LSON(p)]<heap[smallest])?LSON(p):smallest;
				smallest=(RSON(p)<=count && heap[RSON(p)]<heap[smallest])?RSON(p):smallest;
				swap(p,smallest);
				if (p==smallest) break;
				p=smallest;
			}
		}
	public:
        int heap[SIZE],count;
		inline int pop()
		{
			int res=heap[1];
			heap[1]=heap[count];
			--count;
			sink();
			return res;
		}
		
		inline void insert(int value)
		{
			heap[++count]=value;
			rise();
		}
};
THeap h;


inline void Input()
{
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
	{
		scanf("%d",&h.heap[i]);
	}
	h.count=n;
	std::sort(h.heap+1,h.heap+1+n);
}

int main()
{
	int i,j,a,b,Ans=0;
	Input();
	while (h.count>1)
	{
		a=h.pop();
		b=h.pop();
		Ans+=a+b;
		h.insert(a+b);
	}
	printf("%d\n",Ans);
	return 0;
}

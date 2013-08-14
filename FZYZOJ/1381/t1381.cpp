/*
 * 2010-09-07  Token  <token@token-desktop>

 * 
 */
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

#define MaxiN 100005
#define MaxiM 3000005
#define Inc(x, y) (x = (x + y < Q) ? x + y : x + y - Q)

int N, M, Q, EdgeNum, SeqNum, Block, OrderNum, Ans, Count;
int Head[MaxiN], Next[MaxiM], Edge[MaxiM], OppHead[MaxiN], Seq[MaxiN], Color[MaxiN], Order[MaxiN], Last[MaxiN], InDegree[MaxiN], Num[MaxiN], Queue[MaxiN], Len[MaxiN], Amount[MaxiN];
bool Known[MaxiN];

inline void AddEdge(int U, int V, int H[])
{
	Next[++ EdgeNum] = H[U];
	H[U] = EdgeNum;
	Edge[EdgeNum] = V;
}

inline void InsEdge(int U, int V)
{
	AddEdge(U, V, Head);
	AddEdge(V, U, OppHead);
}

void DFS1(int Cur)
{
	Known[Cur] = 1;
	for (int i = Head[Cur]; i; i = Next[i])
		if (!Known[Edge[i]])
			DFS1(Edge[i]);
	Seq[++ SeqNum] = Cur;
}

void DFS2(int Cur)
{
	Known[Cur] = 1;
	Color[Cur] = Block;
	++ Num[Block];
	Order[++ OrderNum] = Cur;
	for (int i = OppHead[Cur]; i; i = Next[i])
		if (!Known[Edge[i]])
			DFS2(Edge[i]);
}

inline void StrongConnect()
{
	for (int i = 1; i <= N; ++ i)
		if (!Known[i])
			DFS1(i);
	memset(Known, 0, sizeof(Known));
	for (int i = N; i > 0; -- i)
		if (!Known[Seq[i]])
		{
			++ Block;
			DFS2(Seq[i]);
		}
	for (int i=1; i<=N; ++i) printf("%d ",Color[i]); puts("");
    memset(OppHead, 0, sizeof(OppHead));
	for (int i = 1; i <= N; ++ i)
		for (int j = Order[i], k = Head[j]; k; k = Next[k])
			if (Color[Edge[k]] != Color[j] && Last[Color[Edge[k]]] != Color[j])
			{
				AddEdge(Color[j], Color[Edge[k]], OppHead);
				++ InDegree[Color[Edge[k]]];
                printf("ADD %d->%d\n",Color[j], Color[Edge[k]]);
				Last[Color[Edge[k]]] = Color[j];
			}
	memcpy(Head, OppHead, sizeof(Head));
}

inline void BFS()
{
	int QHead = 0, QTail = 0;
    for (int i=0; i<= Block; ++i)     printf(" %d",Head[i]);
    
	for (int i = 1; i <= Block; ++ i)
		if (InDegree[i] == 0)
			Amount[Queue[++ QTail] = i] = 1;
	while (QHead < QTail)
	{
		int Cur = Queue[++ QHead];
		Len[Cur] += Num[Cur];
		if (Ans < Len[Cur])
		{
			Ans = Len[Cur];
			Count = 0;
		}
		if (Ans == Len[Cur])
			Inc(Count, Amount[Cur]);
		for (int i = Head[Cur]; i; i = Next[i])
		{
			if (Len[Edge[i]] < Len[Cur])
			{
				Len[Edge[i]] = Len[Cur];
				Amount[Edge[i]] = 0;
			}
			if (Len[Edge[i]] == Len[Cur])
				Inc(Amount[Edge[i]], Amount[Cur]);
			-- InDegree[Edge[i]];
			if (InDegree[Edge[i]] == 0)
				Queue[++ QTail] = Edge[i];
		}
	}
}

int main()
{
    freopen("p1381.in","r",stdin);
	scanf("%d%d%d", &N, &M, &Q);
	for (int i = 1; i <= M; ++ i)
	{
		int U, V;
		scanf("%d%d", &U, &V);
		InsEdge(U, V);
	}
	StrongConnect();
	BFS();
	printf("%d\n%d\n", Ans, Count); while(1);
	return 0;
}

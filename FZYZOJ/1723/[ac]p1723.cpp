#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
const int MAXN=100005;

struct TNode
{
    int dist,num;
    TNode *lSon, *rSon, *father;
    long long v,sum;
};
typedef TNode* PNode;
TNode eNode,heap[MAXN];
int hcount=0;
PNode Empty=&eNode, root[MAXN];
int n,m;
int boss[MAXN],money[MAXN],ld[MAXN],head[MAXN];
long long Ans=0;
PNode merge(PNode nodeA, PNode nodeB)
{
    if (nodeA==Empty) return nodeB;
    if (nodeB==Empty) return nodeA;
    if (nodeB->v > nodeA->v)
        std::swap(nodeA, nodeB);
   // nodeA->sum+=nodeB->sum;
    nodeA->rSon=merge(nodeA->rSon, nodeB);
    nodeA->rSon->father=nodeA;
    if (nodeA->lSon->dist < nodeA->rSon->dist)
        std::swap(nodeA->lSon, nodeA->rSon);
    if (nodeA->rSon == Empty)
        nodeA->dist = 0;
    else
        nodeA->dist = nodeA->rSon->dist+1;
    nodeA->sum = nodeA->lSon->sum + nodeA->rSon->sum + nodeA->v;
    nodeA->num = nodeA->lSon->num + nodeA->rSon->num +1;
    return nodeA;
}

inline PNode popMax(const PNode node)
{
    return merge(node->lSon, node->rSon);
}

void init()
{
    int now;
    for (now=1; now<=n+1; ++now)
    {
        root[now]=&heap[++hcount];
        root[now]->lSon=root[now]->rSon=root[now]->father=Empty;
        root[now]->v=root[now]->sum=money[now];
        root[now]->dist=0;
        root[now]->num=1;
    }
}

inline void process()
{
    long long tmp;
    int now;
    init();
    //puts("DONE");
    for (now=n+1; now>=2; --now)
    {
        while (root[now]->sum > m)
            root[now]=popMax(root[now]);
        tmp=(long long)root[now]->num * ld[now];
        Ans=std::max(Ans,tmp);
        root[boss[now]]=merge(root[boss[now]],root[now]);
    }
    printf("%lld\n",Ans);
}

inline void input()
{
    scanf("%d%d",&n,&m);
    for (int i=2; i<=n+1; ++i)
    {
        scanf("%d%d%d",&boss[i],&money[i],&ld[i]);
        ++boss[i];
    }
}

int main()
{
    input();
    process();
    system("pause");
    return 0;
}

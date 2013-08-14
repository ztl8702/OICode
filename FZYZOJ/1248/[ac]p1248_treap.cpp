#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
const int SIZE = 210000;
//typedef struct TNode;
typedef struct TNode* PNode;
struct TNode
{
    PNode left,right;
    int value,key,count;
};

PNode root,NULLNODE;
TNode tree[SIZE+5];
int size,old,out,countLeave=0;
namespace Treap
{
inline void maintain(PNode x)
{
    x->count = x->left->count + x->right->count + 1;
}

/*
          p
          |
          X
        /   \
       A    Y
          /  \
         B   C
    Left-Rotate:
          p
          |
          Y
         /  \
        X   C
       / \
      A  B
*/

inline void LRotate(PNode &p)
{
    PNode X=p,Y=X->right;
    X->right = Y->left;
    Y->left  = X;
    maintain(X);
    maintain(Y);
    p=Y;
}

inline void RRotate(PNode &p)
{
    PNode Y=p,X=Y->left;
    Y->left  = X->right;
    X->right = Y;
    maintain(Y);
    maintain(X);
    p=X;
}

void insert(PNode &p,int v)
{
    if (p==NULLNODE)
    {
        ++size;
        p=&tree[size];
        p->left=p->right=NULLNODE;
        p->value = v;
        p->key   = rand();
        p->count = 1;
    }
    else if (v < p->value)
    {
        insert(p->left,v);
        maintain(p);
        if (p->left->key < p->key)
            RRotate(p);
    }
    else
    {
        insert(p->right,v);
        maintain(p);
        if (p->right->key < p->key)
            LRotate(p);
    }
}

int find(PNode p,int k)
{
    while (1)
    {
        if (p->left->count >=k)
            p = p->left;
        else if (p->left->count + 1 == k)
            return p->value;
        else
        {
            k -= p->left->count + 1;
            p = p->right;
        }
    }
}

void remove(PNode &p,int tkey)
{
    if (tkey < p->value)
    {
        remove(p->left,tkey);
        maintain(p);
        return;
    }
    if (tkey > p->value)
    {
        remove(p->right,tkey);
        maintain(p);
        return;
    }
    if (p->left != NULLNODE || p->right != NULLNODE)
    {

        if (p->left->key < p->right->key)
        {
            RRotate(p);
            remove(p->right,tkey);
            maintain(p);
        }
        else
        {
            LRotate(p);
            remove(p->left,tkey);
            maintain(p);
        }
    }
    else
    {
        ++countLeave;
        memset(p,0,sizeof(p));
        p=NULLNODE;
        return;
    }
}

inline void Init()
{
    srand(time(0));
    size=0;
    NULLNODE = new TNode();
    NULLNODE->left = NULLNODE->right = NULL;
    NULLNODE->key  = 2147483600;
    NULLNODE->value= NULLNODE->count = 0;
    root=NULLNODE;
}

inline void print(PNode p)
{
    if (p->left!=NULLNODE)
        print(p->left);
    std::cout<<p->value<<"\n";
    if (p->right!=NULLNODE)
        print(p->right);
}
};
int n,minSalary,delta=0;
int main()
{
#ifndef ONLINE_JUDGE
    freopen("p1248.in","r",stdin);
    freopen("p1248.out","w",stdout);
#endif
    int i,argu,tmp;
    char cmd;
    Treap::Init();
    scanf("%d%d",&n,&minSalary);
    for (i=1; i<=n; ++i)
    {
        do
            cmd=getchar();
        while (cmd==' ' || cmd==13 || cmd==10);
        scanf("%d",&argu);
        switch(cmd)
        {
        case 'I':
            if (argu<minSalary)
                countLeave+=0; //一进就辞退不算入答案！！！！！！
            else
            {
                Treap::insert(root,argu-delta);
            }
            break;
        case 'A':
            delta+=argu;
            break;
        case 'S':
            delta-=argu;
            while (root!=NULLNODE && (tmp=Treap::find(root,1))<minSalary-delta)
            {
                Treap::remove(root,tmp);
                //countLeave++;
            }
            break;
        case 'F':
            argu<=root->count ? printf("%d\n",Treap::find(root,root->count-argu+1)+delta) : printf("-1\n");
            break;
        case 'P':
            Treap::print(root);
        }
    }
    printf("%d\n",countLeave);
}

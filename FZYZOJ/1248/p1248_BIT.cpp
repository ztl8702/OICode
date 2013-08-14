/*
 * FZYZOJ P1248
 * BIT
 * March 16, 2012
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

const int SIZE = (1<<18);
const int OFFSET = (1<<17);
class BIT //Binary Indexed Tree with minus range
{
    int tree[SIZE + 5];
    inline int lowbit(const int x)
    {
        return x&(-x);
    }
    inline void add(const int pos, const int value)
    {
        for (int i=pos;i<=SIZE;i+=lowbit(i))
            tree[i]+=value;       
    }
    inline int find(const int now,int k)
    {
        if (lowbit(now)==1)
            return now;
        for (int i=now-(lowbit(now)>>1);;i+=(lowbit(i)>>1))  //Search the left subtree
        {
            if (tree[i]<k)
            {
                k-=tree[i];
            
            }else
                return find(i,k);
            if (lowbit(i)==1)
                break;
        }
        return now;
    }
    public:
    inline void Add(const int pos, const int value) {
        add(pos+OFFSET,value);
    }
    inline int Find(const int k)
    {
        return find(SIZE,k)-OFFSET;
    }
};
BIT tree;
int n,minSalary,delta=0;
int main()
{

    int i,argu,countLeave=0,count=0,tmp;
    char cmd;
    scanf("%d%d",&n,&minSalary);
    for (i=1;i<=n;++i)
    {
        do
            cmd=getchar();
        while (cmd==' ' || cmd==13 || cmd==10);
        scanf("%d",&argu);
        switch(cmd)
        {
            case 'I':
                if (argu<minSalary)
                    ++countLeave;
                else
                {
                    tree.Add(argu-delta,+1);
                    ++count;
                }
                break;
            case 'A':
                delta+=argu;
                break;
            case 'S':
                delta-=argu;
                while ((tmp=tree.Find(1))<minSalary-delta)
                {
                    tree.Add(tmp,-1);
                    ++countLeave;
                    --count;
                }
                break;
            case 'F':
                if (argu<=count)
                    printf("%d\n",tree.Find(count-argu+1)+delta);
                else
                    printf("-1\n");
                break;
        }
    }
    printf("%d\n",countLeave);
    system("pause");
}

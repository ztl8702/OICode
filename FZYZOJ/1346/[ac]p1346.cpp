#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>

#define MAXN 1000005
#define MAXQ 200005

typedef struct __req
{
    int ans,y,next;
}TReq;

TReq req[MAXQ*2];
int dis[MAXN];
int reqnext[MAXN];
int qcount,father[MAXN],root[MAXN];
bool vst[MAXN];
int N,Q;

inline int min(const int a,const int b)
{
    return a<b?a:b;
}

inline void addreq(const int xx,const int yy)
{
    qcount++;
    req[qcount].y=yy;
    req[qcount].next=reqnext[xx];
    req[qcount].ans=2147483600;
    reqnext[xx]=qcount;
}

int getRoot(int now)
{  
    return root[now]==now?root[now]:(root[now]=getRoot(root[now]));
}

namespace Graph
{
    typedef struct __node
    {
        int next,b,v;
    } TEdge;
    int count;
    int start[MAXN];
    TEdge poi[MAXN*2];
    inline void init() {count=0;}
    inline void addedge(const int a,const int b,const int v)
    {
        count++;
        poi[count].b=b;
        poi[count].next=start[a];
        poi[count].v=v;
        start[a]=count;
    }
}

namespace Solve
{   
    inline void dfs(int now,int dst,int sender)
    {
        vst[now]=true;
        
        dis[now]=dst;
        father[now]=sender;
        root[now]=now;
        
        for (int p=reqnext[now];p;p=req[p].next)
        {
            if (vst[req[p].y]) 
            {
                int z=getRoot(req[p].y);
                req[p].ans=dis[now]+dis[req[p].y]-2*dis[z];
            }        
        }
        
        for (int p=Graph::start[now];p;p=Graph::poi[p].next)
        {
            if (!vst[Graph::poi[p].b]) dfs(Graph::poi[p].b,dst+Graph::poi[p].v,now);
        }    
        root[now]=father[now];
    }
    
    inline void readData()
    {
        int x,y,z;
        scanf("%d%d",&N,&Q);
        for (int i=1;i<N;++i)
        {
            scanf("%d%d%d",&x,&y,&z);
            Graph::addedge(x,y,z);
            Graph::addedge(y,x,z);
        }
        for (int i=1;i<=Q;++i)
        {
            scanf("%d%d",&x,&y);
            addreq(x,y);
            addreq(y,x);
        }
    }
    
    inline void run()
    {
        dfs(1,0,1);
        for (int i=1;i<=2*Q;i+=2)
        {
            printf("%d\n",min(req[i].ans,req[i+1].ans));
        }
    }
}


int main()
{
    Graph::init();
    Solve::readData();
    Solve::run();
    system("pause");
    return 0;
    
}

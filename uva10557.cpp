#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef pair<int,int> PII;

#define PB push_back
#define MP make_pair
#define MS(m,what)		memset(m,what,sizeof(m))
#define FOR(i,a,b)		for( int i = (a) ; i < (b) ; i ++ )
#define FOE(i,a,b)		for( int i = (a) ; i <=(b) ; i ++ )
#define FOD(i,a,b)		for( int i = (a) ; i >=(b) ; i -- )
#define SS(a)			scanf("%d",&a)
#define LL(a)			((a)<<1)
#define RR(a)			((a)<<1|1)
#define SZ(a)			((int)a.size())
#define two(x)			((LL)1<<(x))
#define include(a,b)	(((a)&(b))==(b))
#define PP(n,m,a)		puts("---");FF(i,n){FF(j,m)cout << a[i][j] << ' ';puts("");}

template<class T> inline T countbit(T n)	{return n?1+countbit(n&(n-1)):0;}
template<class T> inline T sqr(T a)	{return a*a;}
template<class T> inline void checkmin(T &a,T b)	{if(a == -1 || a > b)a = b;}
template<class T> inline void checkmax(T &a,T b)	{if(a < b)	a = b;}

const double eps = 1e-11;
const double Pi = acos(-1.0);
int dx[] = {-1,0,1,0};//up Right down Left
int dy[] = {0,1,0,-1};

const int INF = 0x1fffffff;
const int N = 107;

struct Node{
    int v,val,next;
}edge[N*N];
int len;

int head[N],  n,  rt;
int dist[N];   //最短距离
int pre[N];    //前一个节点
int inQue[N];  //是否在队列中
int pLen[N];   //path length 路径长度

int ene[N]; //每个房间的能量
int fu[N];  //该点在负环里

void add(int &kind, int v, int val){//起点  终点  权值
    edge[len].next = kind;
    edge[len].v = v;
    edge[len].val = val;
    kind = len++;
}

deque<int> que;

bool spfa(){
    que.push_back(rt);  dist[rt]=0;  pLen[rt]=0;  pre[rt]=-1;
    int cnt = 1, sum = 0;   //LLL优化  队列中元素个数  以及dist的和
    while( !que.empty() ){
        while( dist[que.front()] > sum/cnt ) {  //LLL
            que.push_back(que.front());  que.pop_front();
        }
        int u = que.front(); que.pop_front(); inQue[u] = 0;
        cnt--;   sum -= dist[u];  //LLL
        for(int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].v,  val = edge[i].val;
            if(fu[v]) continue;
            if(dist[u]+val>=100) continue;  //能量为空
            if(v==n) return true;
            if(dist[v] > dist[u]+val) {
                dist[v] = dist[u]+val;  pre[v]=u;  pLen[v] = pLen[u]+1;
                if(pLen[v] >= n) fu[v]=1;   //路径长度>=n 有负环
                if( !inQue[v] ){
                    if(!que.empty() && dist[v] < dist[que.front()]){  //SLF优化
                        que.push_front(v);
                    }else {
                        que.push_back(v);
                    }
                    cnt++;   sum += dist[v];  //LLL
                    inQue[v] = 1;
                }
            }
        }
    }
    return false;
}

int vis[N];
bool solve(int u) {
    if(u == n) return true;
    if(vis[u]) return false;
    vis[u] = 1;
    for(int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].v;
        if( solve(v) ) return true;
    }
    return false;
}

void init(){
    len = 0;
    memset(head,-1, sizeof head);
    memset(dist, 1, sizeof dist);
    memset(inQue, 0, sizeof inQue );
    memset(fu, 0, sizeof fu);
    while(!que.empty()) que.pop_front();
}

void build(){
    rt = 1;
    for(int i=1; i<=n; i++) {
        int cnt, v;
        scanf("%d%d", &ene[i], &cnt);
        for(int j=0; j<cnt; j++) {
            scanf("%d",&v);
            add(head[i], v, 0);
        }
    }
    for(int i=0; i<len; i++) {
        int v = edge[i].v;
        edge[i].val = -ene[v];
    }
}

int main() {
    while(scanf("%d", &n)){
        if(n==-1) break;
        init();
        build();

        if(spfa()) {
            printf("winnable\n");
            continue;
        }

        bool flag = 0;
        for(int i=1; i<=n; i++) {
            if(fu[i]){
                memset(vis, 0, sizeof vis);
                if( solve(i) ){
                    flag = 1;
                    break;
                }
            }
        }
        if(flag) {
            printf("winnable\n");
        }else{
            printf("hopeless\n");
        }

    }

    return 0;
}


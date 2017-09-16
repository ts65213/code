#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <queue>
#include <stack>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <sstream>
#include <set>
#include <list>
#include <cctype>
#include <bitset>
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

#define N 1000010
struct Node{
    int v,val,next;
}edge[N];

int len;
int head[N],  n,  rt;
long long dist[N];
int pre[N], vis[N];

void add(int &kind, int v, int val){//起点  终点  权值
    edge[len].next = kind;
    edge[len].v = v;
    edge[len].val = val;
    kind = len++;
}

struct nod{ int u; long long dist; };

struct cmp{
    bool operator()(nod e1, nod e2) {
        return e1.dist > e2.dist;//最小堆
    }
};

priority_queue<nod, vector<nod>, cmp> que;

void Dijkstra(){
    int cnt = 0;
    dist[rt] = 0; pre[rt] = -1;
    nod h;   h.u = rt;  h.dist = 0;   que.push(h);
    while( !que.empty() ){
        h = que.top();   que.pop();   int u = h.u;
        if(vis[u]) continue;    vis[u] = 1;		if(++cnt == n) break;
        for(int i = head[u]; i != -1; i = edge[i].next){
            int v = edge[i].v, val = edge[i].val;
            if(dist[v] > dist[u] + val){
                dist[v] = dist[u] + val;  pre[v] = u;
                h.u = v;  h.dist = dist[v];
                que.push(h);
            }
        }
    }
}

void init(){
    len = 0;
    memset(head, -1, sizeof head);
    memset(dist, 0x3f, sizeof dist);
    memset( vis, 0, sizeof vis );
    while(!que.empty()) que.pop();
}

int tu[N], tv[N], tval[N], tlen;  //暂存输入数据，两次建图
long long tdist[N];  //存第一次图的最短路径

void build(){
    rt = 1;
    for(int i=0; i<tlen; i++) {
        add(head[tu[i]], tv[i], tval[i]);
    }
}
void rbuild(){
    rt = 1;
    for(int i=0; i<tlen; i++) {
        add(head[tv[i]], tu[i], tval[i]);
    }
}


int main(){
    int T;
    scanf("%d", &T);
    while(T--) {
        int cnt;
        scanf("%d%d", &n, &cnt);
        tlen = 0;
        for(int i=0; i<cnt; i++) {
            scanf("%d%d%d", &tu[tlen], &tv[tlen], &tval[tlen]);
            tlen++;
        }
        init();
        build();
        Dijkstra();
        for(int i=1; i<=n; i++) {
            tdist[i] = dist[i];
        }
        init();
        rbuild();
        Dijkstra();
        long long ans = 0;
        for(int i=1; i<=n; i++) {
            ans += tdist[i]+dist[i];
        }
        printf("%lld\n", ans);
    }

    return 0;
}





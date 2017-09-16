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

#define N 105
struct Node{
    int v,next;
}edge[N*N];
int len;

int head[N],  n;
int rd[N];
int ans[N], p;
stack<int> s;

void add_edge(int u, int v){
    edge[len].next = head[u];
    edge[len].v = v;
    head[u] = len++;
}

void init(){
    len = p = 0;
    memset(head,-1, sizeof head);
    memset(rd, 0, sizeof rd);
    while(!s.empty()) s.pop();
}

void build(){
    int m;
    scanf("%d", &m);
    while( m-- ){
        int a, b;
        scanf("%d%d", &a, &b);
        add_edge(a, b);
        rd[b]++;
    }
}

void topo(){
    for(int i=1; i<=n; i++) {
        if(rd[i] == 0) {
            s.push(i);
        }
    }
    while(!s.empty()){
        int u = s.top();
        s.pop();
        ans[p++] = u;
        for(int i = head[u]; i != -1; i = edge[i].next) {
            int v=edge[i].v;
            rd[v]--;
            if(rd[v]==0){
                s.push(v);
            }
        }
    }
    for(int i=0; i<n; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");
}

int main() {
    while(scanf("%d", &n), n){
        init();
        build();
        topo();    
    }
    return 0;
}


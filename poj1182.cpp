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
const int N = 50007;


int rank[N];   // 节点高度的上界
int parent[N]; // 根节点
int r[N];      // 相对于parent的偏移量

int FindSet(int x){
    int px=parent[x];
    if(x!=parent[x]) parent[x]=FindSet(parent[x]);
    r[x]=(r[px]+r[x])%3;
    return parent[x];
}

void UnionSet(int x,int y,int rx,int ry,int d){
     if(rx==ry) return;
     if(rank[rx]>rank[ry]){
         parent[ry]=rx;
         r[ry]=(r[x]-r[y]+2+d)%3;
     }
     else{
         parent[rx]=ry;
         r[rx]=(r[y]-r[x]-d+4)%3;
         if(rank[rx]==rank[ry])rank[ry]++;
     }
}

void MakeSet(){
     for(int i=0;i<=N;i++) {
         parent[i]=i; r[i]=rank[i]=0;
     }
}

int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    int d,x,y,cnt=0;
    int rx,ry;

    MakeSet();
    while(k--){
        scanf("%d%d%d",&d,&x,&y);
        rx=FindSet(x); ry=FindSet(y);
        if(d==1){
            if(x>n||y>n)cnt++;
            else if(rx==ry&&r[x]!=r[y])cnt++;
            else UnionSet(x,y,rx,ry,d);
        }
        else{
            if(x>n||y>n||x==y)cnt++;
            else if(rx==ry&&r[x]!=(r[y]+2)%3)cnt++;
            else UnionSet(x,y,rx,ry,d);
        }
    }
    cout<<cnt<<endl;
    return 0;
}

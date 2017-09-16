#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <queue>
#include <stack>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <set>
#include <map>

#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <sstream>
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
const int N = 10007;

string s, t;
int a[N], b[N], h[N], n, p, ans, sum;
struct node {
    int l, r, v;
}nd[N];

void str2arr(string *s, int *a){
    int pos = 0, i=0, t = 0;
    while((*s)[i]) {
        if('0'<=(*s)[i] && (*s)[i]<='9'){
            t = t*10+((*s)[i]-'0');
        }else if(t) {
            a[pos++] = t;
            t = 0;
        }
        i++;
    }
    if(t) a[pos++] = t;
    n = pos;
}

void init(){
    p = 0, sum = 1e9, ans=1e9;
    str2arr(&s, a);
    str2arr(&t, b);
    for(int i = 0; i < n; i++ ) {
        h[a[i]] = i;
    }
    memset(nd, -1, sizeof nd);
}

int d(int pa, int pb, int n, int sum1){
    int pos = h[b[pb+n-1]];
    int cnt = pos-pa;
    int rt = p++;
    nd[rt].v = a[pos];
    int sum2 = sum1 + nd[rt].v;
    if(cnt>0) nd[rt].l = d(pa, pb, cnt, sum2);
    if(n-cnt-1>0) nd[rt].r = d(pos+1, pb+cnt, n-cnt-1, sum2);
    if(n==1) {
        if(sum2 < sum) {
            sum = sum2;
            ans = nd[rt].v;
        }else if(sum2==sum && ans>nd[rt].v) {
            ans = nd[rt].v;
        }
    }
    return rt;
}

int main(){
    while(getline(cin, s)){
        getline(cin, t);
        init();
        d(0, 0, n, 0);
        cout<<ans<<endl;
    }
    return 0;


}








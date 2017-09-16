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
const int N = 60;


stack<string> s[N];
int pre[N], nxt[N];

void init(){
  for(int i = 0; i<=52; i++) {
	while(!s[i].empty()) s[i].pop();
	pre[i] = i-1;
	nxt[i] = i+1;
  }
  pre[0] = 0;
  s[0].push("sb");
}

int move(int p, int k){  //第p堆牌往前移k位
  int t = p;
  for(int i = 0; i<k; i++) t = pre[t];
  string s1 = s[t].top(), s2 = s[p].top();
  if(s1[0]==s2[0] || s1[1]==s2[1]) {
	s[t].push(s2);
	s[p].pop();
	if(s[p].empty()){
	  nxt[pre[p]] = nxt[p];
	  pre[nxt[p]] = pre[p];
	}
	return t;
  }
  return 0;
}

void solve(){
  int p = 1;
  while(p<=52){
	int t = move(p, 3);
	if(t) {p = t; continue;}
	t = move(p, 1);
	if(t) {p = t; continue;}
	p = nxt[p];
  }

  int c = 0, ans[N] = {0};
  p = 1;
  while(p<=52) {
	while(!s[p].empty()){
	  s[p].pop();
	  ans[c]++;
	}
	c++;
	p = nxt[p];
  }

  if(c==1) cout<<"1 pile remaining: 52"<<endl;
  else {
	cout<<c<<" piles remaining:";
	for(int i = 0; i<c; i++) cout<<' '<<ans[i];
	cout<<endl;
  }
}

int main(){
  while(1) {
	init();
	string str;
	cin>>str;
	if(str[0]=='#') break;
	s[1].push(str);
	for(int i = 2; i<53; i++) {
	  cin>>str;
	  s[i].push(str);
	}
	solve();
  }


  return 0;
}

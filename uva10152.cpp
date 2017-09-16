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
const int N = 200+5;

string s[N], t[N];
int n;

int main(){
  int K;
  cin>>K;
  while(K--){
	cin>>n;
	getline(cin, s[0]);
	for(int i = 0; i < n; i++ ) getline(cin, s[i]);
	for(int i = 0; i < n; i++ ) getline(cin, t[i]);

	int i = n-1, j = n-1;
	while(i >= 0 && j >= 0) {
	  while(i>=0 && s[i] != t[j]) i--;
	  if(i>=0) {
		i--; j--;
	  }
	  else break;
	}
	for(int k = j; k >= 0; k-- ) cout<<t[k]<<endl;
	cout<<endl;
  }
  return 0;
}














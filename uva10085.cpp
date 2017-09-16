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

const int INF = 0x1fffffff;
const int N = 500007;

// 012
// 345
// 678

int dir[4] = {-1, 3, 1, -3};  //方向
char Dir[4] = {'L', 'D', 'R', 'U'};
int facts[10] = {1};  //g[i] = i的阶乘

int a[9];  //编码前的状态
int last;  //最后一个状态

int h[N];
int pre[N];    //前一个状态
char path[N];   //移动到该状态的方向

queue<int> q;

//康托展开  最小的排列<=>(code==0)
int cantor(int a[], int n){// a[0~n-1] => int
    int code = 0;
    for(int i=0; i<n; i++) {
        int cnt = 0;
        for(int j=i+1; j<n; j++) {
            if(a[i]>a[j]) cnt++;
        }
        code += cnt*facts[n-i-1];
    }
    return code;
}

//逆康托展开  最小的排列<=>(code==0)
void deCantor(int code, int a[], int n){//int => a[0~n-1]
    long long state = 0;
    for(int i = n-1; i >= 0; i--) {
        int k = code / facts[i] + 1;
        code = code % facts[i];
        int cnt = 0;
        for(int j=1; ; j++) {
            if(!(state & (1<<j))) cnt++;
            if(cnt==k) {
                a[n-1-i] = j-1;//a[]里最小的数是0
                state |= (1<<j);
                break;
            }
        }
    }
}

void move(int u, int i, int d){//上一个状态 0所在位置 方向
    if((i%3)==0 && d==0) return;
    if((i%3)==2 && d==2) return;
    if((i/3)==0 && d==3) return;
    if((i/3)==2 && d==1) return;

    int j = i+dir[d];
    swap(a[i], a[j]);
    int v = cantor(a, 9);
    if(!h[v]){
        h[v] = 1;
        pre[v] = u;
        path[v] = Dir[d];
        last = v;  //最后一个状态
        q.push(v);
    }
    swap(a[i], a[j]);
}

void bfs(){
    //while(!q.empty()) q.pop();
    int code = cantor(a, 9);
    h[code] = 1;    pre[code] = -1;
    q.push(code);
    while(!q.empty()) {
        int u = q.front();  q.pop();
        deCantor(u, a, 9);
        int i=0;
        while(a[i]) i++;
        for(int d=0; d<4; d++) {
            move(u, i, d);
        }
    }
}

void print_path(int i){
    if(pre[i]==-1)return;
    print_path(pre[i]);
    cout<<path[i];
}

int main(){
    for(int i=1; i<10; i++) {  //计算阶乘
        facts[i] = i*facts[i-1];
    }

	int T;
    cin>>T;
    for(int t=1; t<=T; t++) {
        memset(h, 0, sizeof h);
        for(int j=0; j<9; j++) {
            cin>>a[j];
        }
        bfs();

        cout<<"Puzzle #"<<t<<endl;
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                cout<<a[i*3+j]<<' ';
            }
            cout<<endl;
        }
        print_path(last);
        cout<<endl<<endl;
    }


    return 0;
}





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
const int N = 20;

int n,m,ans;
char Map[N][N];
int ship[7][4][3][2],dir[7];
int lp[N*N],rp[N*N],lx[N*N],rx[N*N],b[N*N];
int c[58][N*N];

void init(){
    ship[0][0][0][0]=1; ship[0][0][0][1]=0; ship[0][0][1][0]=1; ship[0][0][1][1]=1; ship[0][0][2][0]=0; ship[0][0][2][1]=1; dir[0]=1;
    ship[1][0][0][0]=0; ship[1][0][0][1]=1; ship[1][0][1][0]=0; ship[1][0][1][1]=2; ship[1][0][2][0]=0; ship[1][0][2][1]=3; dir[1]=2;
    ship[2][0][0][0]=0; ship[2][0][0][1]=1; ship[2][0][1][0]=1; ship[2][0][1][1]=1; ship[2][0][2][0]=1; ship[2][0][2][1]=2; dir[2]=2;
    ship[3][0][0][0]=0; ship[3][0][0][1]=1; ship[3][0][1][0]=-1; ship[3][0][1][1]=1; ship[3][0][2][0]=-1; ship[3][0][2][1]=2; dir[3]=2;
    ship[4][0][0][0]=1; ship[4][0][0][1]=0; ship[4][0][1][0]=1; ship[4][0][1][1]=1; ship[4][0][2][0]=1; ship[4][0][2][1]=2; dir[4]=4;
    ship[5][0][0][0]=0; ship[5][0][0][1]=1; ship[5][0][1][0]=0; ship[5][0][1][1]=2; ship[5][0][2][0]=-1; ship[5][0][2][1]=2; dir[5]=4;
    ship[6][0][0][0]=1; ship[6][0][0][1]=-1; ship[6][0][1][0]=1; ship[6][0][1][1]=0; ship[6][0][2][0]=1; ship[6][0][2][1]=1; dir[6]=4;
    FOR(i,0,7) FOR(j,1,dir[i]) FOR(k,0,3) ship[i][j][k][0]=ship[i][j-1][k][1], ship[i][j][k][1]=-ship[i][j-1][k][0];
}

inline void add(int i,int *r,int *l){ r[l[i]]=i; l[r[i]]=i; }
inline void del(int i,int *r,int *l){ l[r[i]]=l[i]; r[l[i]]=r[i]; }
void Del(int x,int y,int i,int j){
    FOD(k,2,0){
        int u = x+ship[i][j][k][0], v = y+ship[i][j][k][1];
        b[u*m+v]=0;
        if(Map[u][v]=='x') add(u*m+v,rx,lx);
        else add(u*m+v,rp,lp);
    }
    b[x*m+y]=0;
    if(Map[x][y]=='x') add(x*m+y,rx,lx);
    else add(x*m+y,rp,lp);
}
int Add(int x,int y,int i,int j){
    int cnt = Map[x][y]=='x'?1:0;
    b[x*m+y]=1;
    if(Map[x][y]=='x') del(x*m+y,rx,lx);
    else del(x*m+y,rp,lp);
    FOR(k,0,3){
        int u = x+ship[i][j][k][0], v = y+ship[i][j][k][1];
        cnt += Map[u][v]=='x'?1:0;
        b[u*m+v]=1;
        if(Map[u][v]=='x') del(u*m+v,rx,lx);
        else del(u*m+v,rp,lp);
    }
    return cnt;
}
bool can(int x,int y,int i,int j){
    FOR(k,0,3){
        int u = x+ship[i][j][k][0], v = y+ship[i][j][k][1];
        if(u<0 || v<0 || u>=n || v>=m || b[u*m+v]) return false;
    }
    return true;
}

void find_ans(){
    int len = n*m;
    FOR(i,0,ans){
        int j;
        for(j=0; j<len; j++) if(c[i][j]!=b[j]) break;
        if(j==len) return;
    }
    FOR(i,0,len) c[ans][i]=b[i];
    ans++;
}

void d(int i,int cntx){
    if(ans==58) return;
    if(cntx>(7-i)*4) return;
    if(i==7) {find_ans();return;}

    for(int e=rx[300];e!=300;e=rx[e]){
        int u=e/m, v=e%m;
        FOR(j,0,dir[i]){
            if(!can(u,v,i,j)) continue;
            int cnt = Add(u,v,i,j);
            d(i+1,cntx-cnt);
            Del(u,v,i,j);
        }
    }

    for(int e=rp[300];e!=300;e=rp[e]){
        int u=e/m, v=e%m;
        FOR(j,0,dir[i]){
            if(!can(u,v,i,j)) continue;
            int cnt = Add(u,v,i,j);
            d(i+1,cntx-cnt);
            Del(u,v,i,j);
        }
    }
}

int flag,len,f[60],sum[N*N];

void dfs(int t){
    if(t==0) flag=1;
    if(flag) return;

    FOR(j,0,len){
        if(sum[j]!=t-1) continue;
        int i;
        for(i=0;i<ans;i++) if(!f[i] && !c[i][j]) break;
        FOR(k,0,len) sum[k]-=c[i][k]; f[i]=1;
        dfs(t-1);
        FOR(k,0,len) sum[k]+=c[i][k]; f[i]=0;
    }
}


int main(){
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    #endif

    init();

    int G=0;
    while(cin>>m>>n,n){
        memset(b,0,sizeof b);
        FOR(i,0,n*m) lp[i]=lx[i]=i-1, rp[i]=rx[i]=i+1;
        lp[0] = lx[0] = rp[n*m-1] = rx[n*m-1] = 300;
        lx[300] = lp[300] = n*m-1; rx[300] = rp[300] =0;

        int cntx = 0;
        FOR(i,0,n) {
            cin>>Map[i];
            FOR(j,0,m){
                int u=i*m+j;
                if(Map[i][j]=='x') {cntx++; del(u,rp,lp);}
                else if(Map[i][j]=='o') {b[u]=1; del(u,rp,lp); del(u,rx,lx);}
                else {del(u,rx,lx);}
            }
        }

        ans = 0;
        d(0,cntx);
        cout<<"Game #"<<++G<<endl;
        if(ans==58||ans==0){cout<<"no."<<endl<<endl; continue;}
        else if(ans<=2){cout<<"yes."<<endl<<endl; continue;}

        memset(f,0,sizeof f);
        memset(sum,0,sizeof sum);
        flag=0, len=n*m;
        FOR(j,0,len) FOR(i,0,ans) sum[j]+=c[i][j];
        dfs(ans);
        if(flag)cout<<"yes."<<endl<<endl;
        else cout<<"no."<<endl<<endl;
    }

    return 0;
}









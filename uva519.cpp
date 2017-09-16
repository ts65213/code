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

int n,m,N;
int a[37][4],c[8][8],b[36];
int edge[4][4],mid[16];

bool test(){
    int ping[4]={0},tu[4]={0},ao[4]={0},ud=0,lr=0,ul=-1,ur=-1,dl=-1,dr=-1,d[4][2][2];
    memset(d,0,sizeof d);
    FOR(i,0,N){
        FOR(j,0,4){
            if(a[i][j]==-1) ping[j]++;
            else if(a[i][j]==0) tu[j]++;
            else ao[j]++;
        }
        if(a[i][0]==-1 && a[i][2]==-1) ud++;
        if(a[i][1]==-1 && a[i][3]==-1) lr++;
        if(a[i][0]==-1 && a[i][3]==-1) {if(ul!=-1) return false; ul=i; c[1][1]=i; b[i]=1;}
        if(a[i][0]==-1 && a[i][1]==-1) {if(ur!=-1) return false; ur=i; c[1][m]=i; b[i]=1;}
        if(a[i][2]==-1 && a[i][3]==-1) {if(dl!=-1) return false; dl=i; c[n][1]=i; b[i]=1;}
        if(a[i][2]==-1 && a[i][1]==-1) {if(dr!=-1) return false; dr=i; c[n][m]=i; b[i]=1;}
        if(a[i][0]==-1){
            if(a[i][1]==0) d[0][1][0]++;
            else if(a[i][1]==1) d[0][1][1]++;
            if(a[i][3]==0) d[0][0][0]++;
            else if(a[i][3]==1) d[0][0][1]++;
        }
        if(a[i][2]==-1){
            if(a[i][1]==0) d[2][1][0]++;
            else if(a[i][1]==1) d[2][1][1]++;
            if(a[i][3]==0) d[2][0][0]++;
            else if(a[i][3]==1) d[2][0][1]++;
        }
        if(a[i][1]==-1){
            if(a[i][0]==0) d[1][0][0]++;
            else if(a[i][0]==1) d[1][0][1]++;
            if(a[i][2]==0) d[1][1][0]++;
            else if(a[i][2]==1) d[1][1][1]++;
        }
        if(a[i][3]==-1){
            if(a[i][0]==0) d[3][0][0]++;
            else if(a[i][0]==1) d[3][0][1]++;
            if(a[i][2]==0) d[3][1][0]++;
            else if(a[i][2]==1) d[3][1][1]++;
        }
    }
    if(c[1][1]==-1||c[1][m]==-1||c[n][1]==-1||c[n][m]==-1) return false;
    if(ping[0]!=m || ping[2]!=m || ping[1]!=n || ping[3]!=n) return false;
    if(tu[0]!=ao[2] || tu[2]!=ao[0] || tu[1]!=ao[3] || tu[3]!=ao[1]) return false;
    if((n>1&&ud)||(m>1&&lr)) return false;
    if(d[0][0][0]!=d[0][1][1] || d[0][0][1]!=d[0][1][0] ||
       d[2][0][0]!=d[2][1][1] || d[2][0][1]!=d[2][1][0] ||
       d[1][0][0]!=d[1][1][1] || d[1][0][1]!=d[1][1][0] ||
       d[3][0][0]!=d[3][1][1] || d[3][0][1]!=d[3][1][0]) return false;
    return true;
}

void fen(){
    int d[5]={0};
    FOR(i,0,N){
        if(b[i]) continue;
        FOR(j,0,4) if(a[i][j]==-1){edge[j][d[j]++]=i; b[i]=1;}
        if(!b[i]) mid[d[4]++] = i;
    }
    memset(b,0,sizeof b);
}

bool can(int i,int j,int k){
    int t;
    t = c[i-1][j];
    if(t!=-1 && a[t][2]+a[k][0]!=1) return false;
    t = c[i+1][j];
    if(t!=-1 && a[t][0]+a[k][2]!=1) return false;
    t = c[i][j-1];
    if(t!=-1 && a[t][1]+a[k][3]!=1) return false;
    t = c[i][j+1];
    if(t!=-1 && a[t][3]+a[k][1]!=1) return false;
    return true;
}

int d[4][24][4],e[4];
int dd[4];
void dfs(int cnt,int i,int j,int di,int dj,int k){
    int lim = (k&1)?n-2:m-2;
    if(cnt==lim){
        FOR(q,0,cnt) d[k][e[k]][q]=dd[q];
        e[k]++;
        return;
    }
    FOR(t,0,lim){
        int p = edge[k][t];
        if(b[p] || !can(i,j,p)) continue;
        b[p]=1; c[i][j]=p; dd[cnt]=p;
        dfs(cnt+1,i+di,j+dj,di,dj,k);
        b[p]=0; c[i][j]=-1;
    }
}

int test1(){
    if(m>2) {
        dfs(0,1,2,0,1,0);
        if(!e[0]) return 1;
        if(e[0] && n==1)return 2;
    }
    if(m>2 && n>1) {
        dfs(0,n,2,0,1,2);
        if(!e[2]) return 1;
        if(e[2] && n==2)return 2;
    }
    if(n>2) {
        dfs(0,2,1,1,0,3);
        if(!e[3]) return 1;
        if(e[3] && m==1)return 2;
    }
    if(n>2 && m>1) {
        dfs(0,2,m,1,0,1);
        if(!e[1]) return 1;
        if(e[1] && m==2)return 2;
    }
    return 0;
}

int so[30],rk[30],y[4][30];
bool cmp(int i,int j){return so[i]<so[j];}
void Sort(){
    memset(y,0,sizeof y);
    FOR(t,0,4){
        FOR(i,0,30) so[i]=0, rk[i]=i;
        int lim = (t&1)?n-2:m-2, tt=t^2;
        FOR(i,0,e[t]) FOR(j,0,lim) so[i]=so[i]*2+a[d[t][i][j]][tt];
        sort(rk,rk+e[t],cmp);
        y[t][rk[0]]=1;
        FOR(i,1,e[t]) if(so[rk[i]]!=so[rk[i-1]]) y[t][rk[i]]=1;
    }
}

int flag;

void dfs1(int i,int j){
    if(i>=n) flag = 1;
    if(flag) return;
    int lim = (n-2)*(m-2);
    FOR(t,0,lim){
        int p = mid[t];
        if(b[p] || !can(i,j,p)) continue;
        b[p]=1; c[i][j]=p;
        if(j<m-1)dfs1(i,j+1);
        else dfs1(i+1,2);
        b[p]=0; c[i][j]=-1;
    }
}

void solve(){
    flag = 0;
    FOR(i0,0,e[0]){
        if(!y[0][i0]) continue;
        FOR(j0,0,m-2) c[1][j0+2]=d[0][i0][j0];
        FOR(i2,0,e[2]){
            if(!y[2][i2]) continue;
            FOR(j2,0,m-2) c[n][j2+2]=d[2][i2][j2];
            FOR(i1,0,e[1]){
                if(!y[1][i1]) continue;
                FOR(j1,0,n-2) c[j1+2][m]=d[1][i1][j1];
                FOR(i3,0,e[3]){
                    if(!y[3][i3]) continue;
                    FOR(j3,0,n-2) c[j3+2][1]=d[3][i3][j3];
                    dfs1(2,2);
                    if(flag) return;
                    FOR(j3,0,n-2) c[j3+2][1]=-1;
                }
                FOR(j1,0,n-2) c[j1+2][m]=-1;
            }
            FOR(j2,0,m-2) c[n][j2+2]=-1;
        }
        FOR(j0,0,m-2) c[1][j0+2]=-1;
    }

}

int main(){
    #ifndef ONLINE_JUDGE
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    #endif

    char s[10];
    FOR(i,0,4) a[36][i]=2;
    while(scanf("%d%d",&n,&m), n){
        N = n*m;
        FOE(i,0,n+1) FOE(j,0,m+1) c[i][j]=36;
        FOE(i,1,n) FOE(j,1,m) c[i][j]=-1;
        memset(b,0,sizeof b);
        memset(e,0,sizeof e);

        FOR(i,0,N){
            scanf("%s",s);
            FOR(j,0,4){
                if(s[j]=='F') a[i][j]=-1;
                else if(s[j]=='O') a[i][j]=1;
                else a[i][j]=0;
            }
        }

        if(!test()){printf("NO\n");continue;}
        if(m<=2 && n<=2){printf("YES\n");continue;}
        fen();

        int t1 = test1();
        if(t1==1){printf("NO\n");continue;}
        else if(t1==2){printf("YES\n");continue;}

        Sort();
        solve();
        if(flag) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}

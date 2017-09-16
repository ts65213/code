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
const int N = 200007;

#define keyTree (ch[ ch[root][1] ][0])
struct SplayTree{
    int sz[N];
    int ch[N][2];//ch[][0]左孩子  ch[][1]右孩子
    int pre[N];
    int root,top;
    stack<int> sta;
    queue<int> que;

    void Rotate(int x,int f) {//f==0左旋转  f==1右旋转
        int y=pre[x], z=pre[y];
        // PushDown(y); PushDown(x);
        ch[y][!f]=ch[x][f]; pre[ch[x][f]]=y;
        pre[x]=z;
        if(z) ch[z][ch[z][1]==y]=x;
        ch[x][f]=y; pre[y]=x;
        PushUp(y);
        //if(y==root)root=x;
    }
    void Splay(int x,int goal) {//将x旋转到goal的下面
        // PushDown(x);
        while(pre[x]!=goal) {
            int y=pre[x],z=pre[y],f=(ch[z][0]==y);
            if(z==goal) Rotate(x,ch[y][0]==x);
            else{
                if(ch[y][f]==x) Rotate(x,!f),Rotate(x,f);//之字形
                else Rotate(y,f),Rotate(x,f);//一字型
            }
        }
        PushUp(x);
        if(goal==0) root=x;
    }
    void SplayKth(int k,int goal) {//将第k个数旋转到goal下面
        int x=root;
        k++; //由于加入了两个边界结点  所以应为k+1位
        while(sz[ch[x][0]]!=k-1) {
            if(k-1<sz[ch[x][0]]) x=ch[x][0];
            else k-=(sz[ch[x][0]]+1), x=ch[x][1];
        }
        Splay(x,goal);
    }
    //以上一般不修改//////////////////////////////////////////////////

    void NewNode(int &x,int c) {     //需再处理pre[x]
        if(!sta.empty()) x=sta.top(), sta.pop();
        else x=++top;
        ch[x][0]=ch[x][1]=pre[x]=0;
        sz[x]=1;

		Max[x]=score[x]=c;    //
    }
    void makeTree(int &x,int l,int r,int father){
        if(l>r) return;
        int m=(l+r)>>1;
        NewNode(x,num[m]);//
        pre[x]=father;
        makeTree(ch[x][0],l,m-1,x);
        makeTree(ch[x][1],m+1,r,x);
        PushUp(x);
    }
    void init(int n) {
        ch[0][0]=ch[0][1]=pre[0]=sz[0]=0;
        top=0;
        while(!sta.empty()) sta.pop();
        //为了方便处理边界,加两个边界顶点    区间操作有用
        NewNode(root,0);   //边界点不要影响正常的计算
        NewNode(ch[root][1],0);
        pre[top]=root;

        makeTree(keyTree,0,n-1,ch[root][1]);
        PushUp(ch[root][1]); PushUp(root);
    }

    void PushUp(int x) {
		sz[x]=1+sz[ch[x][0]]+sz[ch[x][1]];
        Max[x]=max(Max[ch[x][0]],Max[ch[x][1]]);
        Max[x] = max(score[x], Max[x]);
	}

	void UpDate(int a,int b){
	    SplayKth(a,0);
	    score[root]=b;
	    PushUp(root);
	}

	void Query(int a,int b) {
	    SplayKth(a-1,0);
	    SplayKth(b+1,root);
		printf("%d\n",Max[keyTree]);
	}
    int num[N];
    int score[N];
	int Max[N];
}spt;


int main() {
	int n, m, a, b;
	char ch;
	while(~scanf("%d%d", &n, &m)){
        for(int i=0;i<n;i++) scanf("%d",&spt.num[i]);
        spt.init(n);
        while(m--){
            scanf("%c",&ch);
            while(ch!='U'&&ch!='Q')scanf("%c",&ch);
            scanf("%d%d",&a,&b);
            if(ch=='U'){
                spt.UpDate(a,b);
            }
            else{
                spt.Query(a,b);
            }
        }
	}
	return 0;
}

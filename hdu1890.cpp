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

const int INF = 0x3fffffff;
#define keyTree (ch[ ch[root][1] ][0])
const int N = 100005;
int a[N];
struct SplayTree{
    int sz[N];
    int ch[N][2];//ch[][0]左孩子  ch[][1]右孩子
    int pre[N];//父结点
    int root,top;
    stack<int> sta;  //复用删掉的节点
    queue<int> que;  //bfs删除子树时用到

    //基本操作     各种操作参数的合法性  以及边界情况
    void rotate(int x,int f) {//f==0左旋转  f==1右旋转
        int y=pre[x], z=pre[y];
        pushDown(y); pushDown(x);
        ch[y][!f]=ch[x][f]; pre[ch[x][f]]=y;
        pre[x]=z;
        if(z) ch[z][ch[z][1]==y]=x;
        ch[x][f]=y; pre[y]=x;
        pushUp(y);
        //if(y==root)root=x;
    }
    void splay(int x,int goal) {//将x旋转到goal的下面  goal为0则旋转到根
        pushDown(x);
        while(pre[x]!=goal) {
            int y=pre[x],z=pre[y],f=(ch[z][0]==y);
            if(z==goal) rotate(x,ch[y][0]==x);
            else{
                if(ch[y][f]==x) rotate(x,!f),rotate(x,f);//之字形
                else rotate(y,f),rotate(x,f);//一字型
            }
        }
        pushUp(x);
        if(goal==0) root=x;
    }
    int findKth(int k) {//找第k个节点  k从1开始
        k++; //由于加入了两个边界结点  所以应为k+1位
        int x=root;
        pushDown(x);
        while(sz[ch[x][0]]!=k-1) {
            if(k-1<sz[ch[x][0]]) x=ch[x][0];
            else k-=(sz[ch[x][0]]+1), x=ch[x][1];
            pushDown(x);
        }
        return x;
    }
    void splayKth(int k, int goal) {//将第k个节点 旋转到goal下面 goal为0则旋转到根
        int x = findKth(k);
        splay(x, goal);
    }

    void makeTree(int &x,int l,int r,int arr[],int father){//根据arr数组的 [l,r]区间 在x位置建立子树
        if(l>r) return;
        int m=(l+r)>>1;
        newNode(x,arr[m],father);  //
        makeTree(ch[x][0],l,m-1,arr,x);
        makeTree(ch[x][1],m+1,r,arr,x);
        pushUp(x);
    }
    void ins(int arr[], int n) {//在keyTree的位置，用arr[0,n)建立子树，即添加区间
        makeTree(keyTree,0,n-1,arr,ch[root][1]);
        pushUp(ch[root][1]);
        pushUp(root);
    }
    void del(int x) {//删除x及其子树
        int fa=pre[x];
        // while(!que.empty()) que.pop();
        que.push(x);
        while(!que.empty()) {
            int t = que.front();
            que.pop();
            sta.push(t);
            if(ch[t][0]) que.push(ch[t][0]);
            if(ch[t][1]) que.push(ch[t][1]);
        }
        ch[fa][ch[fa][1]==x]=0;
        splay(fa, 0);
    }

    int pred(int x){//在x的子树中找x的前驱  不存在返回0
        pushDown(x);
        int y=ch[x][0]; pushDown(y);
        while(ch[y][1]) y=ch[y][1],pushDown(y);
        return y;
    }
    int succ(int x){//在x的子树中找x的后继  不存在返回0
        pushDown(x);
        int y=ch[x][1]; pushDown(y);
        while(ch[y][0]) y=ch[y][0],pushDown(y);
        return y;
    }

    //以上一般不修改//////////////////////////////////////////////////
    void init() {
        while(!sta.empty()) sta.pop();
        ch[0][0]=ch[0][1]=pre[0]=sz[0]=0;
        root=top=0;
        rev[0]=0;    //
        val[0]=Min[0]=0;

        newNode(root,0,0);   //为了方便处理边界,加两个边界顶点    区间操作有用
        newNode(ch[root][1],0,root);  //边界点里的值不要影响正常的计算
    }

    void newNode(int &x,int c,int father) {
        if(!sta.empty()) x=sta.top(), sta.pop();
        else x=++top;
        ch[x][0]=ch[x][1]=0;
        sz[x]=1;  pre[x]=father;

        Min[x] = val[x]=c;    //
        rev[x]=0;    //
    }

    void pushDown(int x) {
        if(x==0) return;
        if(rev[x]){
            swap(ch[x][0], ch[x][1]);
            rev[ch[x][0]]^=1;
            rev[ch[x][1]]^=1;
            rev[x]^=1;
        }
    }

    void pushUp(int x) {
        if(x==0) return;
        sz[x]=1+sz[ch[x][0]]+sz[ch[x][1]];
        int i = Min[ ch[x][0]], j = Min[ch[x][1]];
        Min[x] = val[x];
        if(a[i]<a[Min[x]] || a[i]==a[Min[x]]&&i<Min[x]) Min[x]=i;
        if(a[j]<a[Min[x]] || a[j]==a[Min[x]]&&j<Min[x]) Min[x]=j;
    }

    void update(){
        pushUp(ch[root][1]);
        pushUp(root);
    }

    void query(int i) {
        int k = minValue(root)-1;
        if(i) printf(" ");
        printf("%d", k+i);
        splayKth(k-1,0);
        splayKth(k+1,root);
        del(keyTree);//删除第k个数
        splayKth(0,0);
        splayKth(k,root);
        rev[keyTree]^=1;
        // printf("         %d\n", i);
        // shuchu();
    }

    int minValue(int x){//求最小值是第几个数
        pushDown(x);
        if(Min[ch[x][0]]==Min[x]) return minValue(ch[x][0]);
        if(val[x]==Min[x]) return sz[ch[x][0]]+1;
        return sz[ch[x][0]]+1+minValue(ch[x][1]);
    }

    int num[N];//暂存数据  用来建树
    int val[N];
    int Min[N];
    int rev[N];

    queue<int> qe;
    void pr(int x){
        if(x==1) printf("L ");
        else if(x==2) printf("R ");
        else if(val[x]==INF) printf("inf ");//
        else printf("%d ", val[x]);
    }
    void shuchu(int x=0){
        if(!x) x=root;
        while(!qe.empty())qe.pop();
        qe.push(x);
        while(!qe.empty()) {
            int t = qe.front(); qe.pop();
            int c1 = ch[t][0], c2 = ch[t][1];
            if(c1) qe.push(c1);
            if(c2) qe.push(c2);
            pr(t); pr(c1); pr(c2); printf("\n");
        }
    }

}spt;


int main() {
    int n;
    a[0]=INF;
    while(scanf("%d", &n), n) {
        for(int i=0;i<n;i++) {
            scanf("%d",&a[i+1]);
            spt.num[i]=i+1;
        }
        spt.init();
        spt.ins(spt.num, n);
        for(int i=1; i<=n; i++) {
            spt.query(i-1);
        }
        printf("\n");
    }
    return 0;
}

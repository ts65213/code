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

const int INF = -1e9-1e5;
#define keyTree (ch[ ch[root][1] ][0])
const int N = 500505;
struct SplayTree{
    int sz[N];
    int ch[N][2];//ch[][0]左孩子  ch[][1]右孩子
    int pre[N];//父结点
    int root,top;
    stack<int> sta;  //复用删掉的节点
    queue<int> que;  //bfs删除子树时用到

    //基本操作
    inline void rotate(int x,int f) {//f==0左旋转  f==1右旋转
        int y=pre[x], z=pre[y];
        // pushDown(y); pushDown(x);
        ch[y][!f]=ch[x][f]; pre[ch[x][f]]=y;
        pre[x]=z;
        if(z) ch[z][ch[z][1]==y]=x;
        ch[x][f]=y; pre[y]=x;
        pushUp(y);
        //if(y==root)root=x;
    }
    inline void splay(int x,int goal) {//将x旋转到goal的下面  goal为0则旋转到根
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
    inline int findKth(int k) {//找第k个节点  k从1开始
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
    inline void splayKth(int k, int goal) {//将第k个节点 旋转到goal下面 goal为0则旋转到根
        int x = findKth(k);
        splay(x, goal);
    }

    inline void makeTree(int &x,int l,int r,int arr[],int father){//根据arr数组的 [l,r]区间 在x位置建立子树
        if(l>r) return;
        int m=(l+r)>>1;
        newNode(x,arr[m],father);  //
        makeTree(ch[x][0],l,m-1,arr,x);
        makeTree(ch[x][1],m+1,r,arr,x);
        pushUp(x);
    }
    inline void ins(int arr[], int n) {//在keyTree的位置，用arr[0,n)建立子树，即添加区间
        makeTree(keyTree,0,n-1,arr,ch[root][1]);
        pushUp(ch[root][1]);
        pushUp(root);
    }
    inline void del(int x) {//删除x及其子树
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

        sum[0]=0;   //
        L[0]=R[0]=M[0]=INF;    //

        newNode(root,0,0);   //
        newNode(ch[root][1],0,root);  //
    }

    inline void newNode(int &x,int c,int father) {
        if(!sta.empty()) x=sta.top(), sta.pop();
        else x=++top;
        ch[x][0]=ch[x][1]=0;
        sz[x]=1;  pre[x]=father;

        val[x]=c;    //
        rev[x] = 0;
        same[x]=INF;
    }

    inline void pushDown(int x) {
        // if(!x) return;
        if(same[x] != INF){
            int sm = same[x];
            for(int i=0; i<2; i++) {
                int c = ch[x][i];
                if(c){
                    same[c] = val[c] = sm;
                    sum[c] = sm*sz[c];
                    if(sm<=0){
                        L[c]=R[c]=M[c]=sm;
                    }else {
                        L[c]=R[c]=M[c]=sum[c];
                    }
                }
            }
            same[x] = INF;
        }
        if(rev[x]){
            for(int i=0; i<2; i++) {
                int c = ch[x][i];
                if(c) {
                    rev[c]^=1;
                    swap(ch[c][0],ch[c][1]);
                    swap(L[c], R[c]);
                }
            }
            rev[x]^=1;
        }
    }

    inline void pushUp(int x) {
        int c0 = ch[x][0], c1 = ch[x][1];
        sz[x]=1+sz[c0]+sz[c1];

        sum[x] = sum[c0]+sum[c1]+val[x];

        M[x] = val[x];
        L[x] = sum[c0]+val[x];
        R[x] = sum[c1]+val[x];
        if(c0){
            M[x] = max(M[x], M[c0]);
            M[x] = max(M[x], R[c0]+val[x]);
            L[x] = max(L[x], L[c0]);
            R[x] = max(R[x], sum[c1]+val[x]+R[c0]);
        }
        if(c1){
            M[x] = max(M[x], M[c1]);
            M[x] = max(M[x], L[c1]+val[x]);
            L[x] = max(L[x], sum[c0]+val[x]+L[c1]);
            R[x] = max(R[x], R[c1]);
        }
        if(c0 && c1){
            M[x] = max(M[x], R[c0]+val[x]+L[c1]);
        }
    }

    inline void INSERT(int p, int n){
        for(int i=0; i<n; i++) {
            scanf("%d",&num[i]);
        }
        splayKth(p, 0);
        splayKth(p+1, root);
        ins(num, n);
    }

    inline void DELETE(int a, int b){
        splayKth(a-1, 0);
        splayKth(b+1, root);
        del(keyTree);
        pushUp(ch[root][1]);
        pushUp(root);
    }

    inline void MAKE_SAME(int a, int b, int c){
        splayKth(a-1, 0);
        splayKth(b+1, root);
        int kt = keyTree;
        same[kt] = c;
        val[kt] = c;
        sum[kt] = sz[kt]*c;
        if(c<=0){
            L[kt] = R[kt] = M[kt] = c;
        }else {
            L[kt] = R[kt] = M[kt] = sum[kt];
        }
        pushUp(ch[root][1]);
        pushUp(root);
    }

    inline void REVERSE(int a, int b){
        splayKth(a-1, 0);
        splayKth(b+1, root);
        int kt = keyTree, &c0 = ch[kt][0], &c1 = ch[kt][1];
        rev[kt]^=1;
        swap(c0, c1);
        swap(L[kt], R[kt]);
        pushUp(ch[root][1]);
        pushUp(root);
    }

    inline void GET_SUM(int a, int b){
        splayKth(a-1, 0);
        splayKth(b+1, root);
        printf("%d\n", sum[keyTree]);
    }

    inline void MAX_SUM(){
        splayKth(0, 0);
        splayKth(sz[root]-1, root);
        printf("%d\n", M[keyTree]);
    }

    int num[N];//暂存数据  用来建树
    int val[N];
    int same[N];
    int rev[N];
    int sum[N];
    int L[N],M[N],R[N];


    queue<int> qe;
    void pr(int x){
        if(x==1) printf("L ");
        else if(x==2) printf("R ");
        else if(val[x]==INF || !x) printf("null ");//
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
    int n , m, p, c;
    char s[100];
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++) scanf("%d",&spt.num[i]);
    spt.init();
    spt.ins(spt.num, n);
    while(m--){
        scanf("%s", s);
        if(s[0] == 'I') {
            scanf("%d%d", &p, &n);
            spt.INSERT(p, n);
        }else if(s[0] == 'D'){
            scanf("%d%d", &p, &n);
            spt.DELETE(p, p+n-1);
        }else if(s[2] == 'K'){
            scanf("%d%d%d", &p, &n, &c);
            spt.MAKE_SAME(p, p+n-1, c);
        }else if(s[0] == 'R'){
            scanf("%d%d", &p, &n);
            spt.REVERSE(p, p+n-1);
        }else if(s[0] == 'G'){
            scanf("%d%d", &p, &n);
            spt.GET_SUM(p, p+n-1);
        }else if(s[2] == 'X'){
            spt.MAX_SUM();
        }
    }
    return 0;
}

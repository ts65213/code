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

#define keyTree (ch[ ch[root][1] ][0])
const int N = 100005;
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
        top=0;
        ch[0][0]=ch[0][1]=pre[0]=sz[0]=0;
        val[0]=sum[0]=add[0]=0;  //

        newNode(root,0,0);   //为了方便处理边界,加两个边界顶点    区间操作有用
        newNode(ch[root][1],0,root);  //边界点里的值不要影响正常的计算
    }

    void newNode(int &x,int c,int father) {//调用后一定要处理pre[x]
        if(!sta.empty()) x=sta.top(), sta.pop();
        else x=++top;
        ch[x][0]=ch[x][1]=0;
        sz[x]=1;  pre[x]=father;

        val[x]=c;    //
        add[x]=0;    //
    }

    void pushDown(int x) {
        if(x==0) return;
        if(add[x]){
            val[x]+=add[x];
            sum[x]=sum[x]+sz[x]*add[x];
            if(ch[x][0]) add[ch[x][0]]+=add[x];
            if(ch[x][1]) add[ch[x][1]]+=add[x];
            add[x]=0;
        }
    }

    void pushUp(int x) {
        if(x==0) return;
        sz[x]=1+sz[ch[x][0]]+sz[ch[x][1]];

        pushDown(ch[x][0]);
        pushDown(ch[x][1]);
        sum[x]=sum[ch[x][0]]+sum[ch[x][1]]+val[x];

        // int x1 = ch[x][0], x2 = ch[x][1];    //为何WA？？
        // long long sum1 = sum[x1], sum2 = sum[x2];
        // if(x1 && add[x1]) sum1+=(long long)sz[x1]*add[x1];
        // if(x2 && add[x2]) sum2+=(long long)sz[x2]*add[x2];
        // sum[x] = sum1+sum2+val[x];
    }

    void update(int a, int b, long long c){
        splayKth(a-1,0);
        splayKth(b+1,root);
        add[keyTree]=(long long)add[keyTree]+c;
        pushUp(ch[root][1]);
        pushUp(root);
    }

    void query(int a, int b) {
        splayKth(a-1,0);
        splayKth(b+1,root);
        printf("%lld\n", sum[keyTree]);
    }
    int num[N];//暂存数据  用来建树
    long long val[N];
    long long add[N];
    long long sum[N];

    void shuchu(int x){
        cout<<"结点 "<<x<<"   左结点 "<<ch[x][0]<<"   右结点 "<<ch[x][1]<<"   值 "<<val[x]<<"   和 "<<sum[x]<<endl;
        if(ch[x][0])shuchu(ch[x][0]);
        if(ch[x][1])shuchu(ch[x][1]);
    }

}spt;


int main() {
    int n , m;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++) scanf("%d",&spt.num[i]);
    spt.init();
    spt.ins(spt.num, n);
    for(int i=0; i<m; i++) {
        char k;
        int a,b,c;
        scanf("%c", &k);
        while(k!='C' && k!='Q') scanf("%c", &k);
        if(k=='C'){
            scanf("%d%d%d", &a, &b, &c);
            spt.update(a,b,c);
        }else {
            scanf("%d%d", &a, &b);
            spt.query(a,b);//
        }
    }
    return 0;
}


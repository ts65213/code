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

const int N = 363000;

int dir[4] = {-1, 3, 1, -3};  //方向
char Dir[4] = {'l', 'd', 'r', 'u'};
int facts[10] = {1};  //facts[i] = i的阶乘

int a[9];  //编码前的状态
int Hash[N];    //状态哈希

int state[N]; //当前状态
int pre[N];   //前一个状态
char path[N]; //移动到该状态的方向
int g[N];     //已移动的步数
int f[N];     //估计的总步数
int p;        //下标
int ans_p;    //到达目标状态的下标
struct cmp{
    bool operator()(int u, int v){
        return f[u]>f[v];
    }
};
priority_queue<int, vector<int>, cmp> q;

void shuchu(){
    for(int i=0; i<9; i++) {
        cout<<a[i]<<' ';
        if(i%3==2) cout<<endl;
    }
    cout<<endl;
}

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
//同时返回8所在的位置
int deCantor(int code, int a[], int n){//int => a[0~n-1]
    long long state = 0;
    int pos;
    for(int i = n-1; i >= 0; i--) {
        int k = code / facts[i] + 1;
        code = code % facts[i];
        int cnt = 0;
        for(int j=1; ; j++) {
            if(!(state & (1<<j))) cnt++;
            if(cnt==k) {
                a[n-1-i] = j-1;
                state |= (1<<j);
                if(j-1==8) pos = n-1-i;
                break;
            }
        }
    }
    return pos;
}

//从位置i移动到位置j所需要的最少步数
inline int cal(int i, int j){
    return abs(i/3-j/3)+abs(i%3-j%3);
}

//交换a[i]、a[j]增加的步数
inline int change(int i, int j){
    if(a[i]==8) swap(i,j);
    return cal(i, a[i]) - cal(j, a[i]);
}

void move(int u, int i, int d){//上一个节点下标 8所在位置 方向
    int t1 = i%3, t2 = i/3;
    if(d==0) {if(!t1) return;}
    else if(d==2) {if(t1==2) return;}
    else if(d==3) {if(t2==0) return;}
    else if(d==1) {if(t2==2) return;}

    int j = i+dir[d];
    swap(a[i], a[j]);
    int v = cantor(a, 9);
    if(Hash[v]!=2){
        Hash[v] = 1;
        state[p] = v;
        pre[p] = u;
        path[p] = Dir[d];
        g[p] = g[u]+1;
        f[p] = g[u]+change(i, j);
        if(v==0) ans_p=p;
        q.push(p++);
    }
    swap(a[i], a[j]);
}

void A_star(){
    while(!q.empty()) q.pop();
    int code = cantor(a, 9);

    int temp = 0;
    for(int i=0; i<9; i++) {
        if(a[i]==8) continue;
        temp+=cal(i,a[i]);
    }

    Hash[code] = 1;
    state[p]=code;
    pre[p] = -1;
    g[p]=0;
    f[p]=temp;
    if(code==0) {ans_p=0; return;}

    q.push(p++);
    while(!q.empty()) {
        int u = q.top();  q.pop();
        if(Hash[state[u]]==2) continue;
        Hash[state[u]] = 2;
        int i = deCantor(state[u], a, 9);
        for(int d=0; d<4; d++) {
            move(u, i, d);
        }
        if(ans_p>-1) break;
    }
}


void print_path(int i){
    if(pre[i]==-1)return;
    print_path(pre[i]);
    printf("%c", path[i]);
}

bool no_ans(){   //无解
    int s=0;
    for(int i=1; i<9; i++) {
        if(a[i]==8) continue;
        for(int j=0; j<i; j++) {
            if(a[i]>a[j]) s++;
        }
    }
    if(s&1) return true;
    return false;
}

int Read(){
    char ch;
    int i=0;
    while(i<9 && cin>>ch ){
        if(ch=='x') a[i++]=8;
        else a[i++]=ch-'1';
    }
    return i;
}

int main(){//hdu1043
#ifndef ONLINE_JUDGE
    // freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif

    for(int i=1; i<10; i++) {  //计算阶乘
        facts[i] = i*facts[i-1];
    }

    while(Read()) {
        if(no_ans()) {printf("unsolvable\n"); continue;}
        p=0;
        ans_p=-1;
        memset(Hash, 0, sizeof Hash);
        A_star();
        print_path(ans_p);
        printf("\n");
    }

    return 0;
}



















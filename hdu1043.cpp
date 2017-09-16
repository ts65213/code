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
int facts[10];  //facts[i] = i的阶乘

int a[9];  //编码前的状态
int Hash[N];    //状态哈希

int st[N][9]; //当前状态
int state[N]; //当前状态编码
int pos8[N];  //8所在位置
int pre[N];   //前一个状态
char path[N]; //移动到该状态的方向
int g[N];     //已移动的步数
int h[N];     //估价
int f[N];     //g+h
int p;        //下标
int ans_p;    //到达目标状态的下标
struct cmp{
    bool operator()(int u, int v){
        return f[u]>f[v];
    }
};
priority_queue<int, vector<int>, cmp> q;

void shuchu(int *p = a){
    for(int i=0; i<9; i++) {
        cout<<p[i]<<' ';
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

int canMove[9][4]; //canMove[i][d]表示a[i]可否向d方向移动
int minPath[9][9]; //minPath[i][j] 从位置i到位置j的最少步数
int hehe[9][9][9]; //hehe[i][j][k] 将k从位置i移动到位置j 估价h的增量

void move(int u, int d){//上一个节点下标 8所在位置 方向
    int i = pos8[u];
    int j = i+dir[d];
    memcpy(st[p], st[u], 9*4);
    swap(st[p][i], st[p][j]);
    int code = cantor(st[p], 9);
    if(Hash[code]==-2) return;
    if(Hash[code]>-1 && g[Hash[code]]<=g[u]+1) return;
    Hash[code] = p;
    state[p] = code;
    pre[p] = u;
    pos8[p] = j;
    path[p] = Dir[d];
    g[p] = g[u]+1;
    h[p] = h[u]+hehe[j][i][st[p][i]];
    f[p] = g[p]+h[p];
    if(code==0) ans_p=p;
    q.push(p++);
}

void A_star(){
    while(!q.empty()) q.pop();
    int code = cantor(a, 9);

    int temp = 0;
    for(int i=0; i<9; i++) {
        if(a[i]==8) {pos8[p]=i; continue;}
        temp+=minPath[i][a[i]];
    }

    Hash[code] = p;
    memcpy(st[p], a, 4*9);
    state[p]=code;
    pre[p] = -1;
    g[p]=0;
    h[p]=temp;
    f[p]=g[p]+h[p];
    if(code==0) {ans_p=0; return;}

    q.push(p++);
    while(!q.empty()) {
        int u = q.top();  q.pop();
        if(Hash[state[u]]==-2) continue;
        Hash[state[u]] = -2;
        // int i = deCantor(state[u], a, 9);
        for(int d=0; d<4; d++) {
            if(!canMove[pos8[u]][d]) continue;
            move(u, d);
        }
        if(ans_p>-1) break;
    }
}


void print_path(int i){
    if(pre[i]==-1)return;
    print_path(pre[i]);
    printf("%c", path[i]);
}

bool ok(){
    int s=0;
    for(int i=1; i<9; i++) {
        if(a[i]==8) continue;
        for(int j=0; j<i; j++) {
            if(a[j]==8) continue;
            if(a[j]>a[i]) s++;
        }
    }
    if(s&1) return false;
    return true;
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

void init() {
    facts[0]=1;
    for(int i=1; i<10; i++) {
        facts[i] = facts[i-1]*i;
    }
    for(int i=0; i<9; i++) {
        for(int d=0; d<4; d++) {
            int j = i+dir[d];
            if(j<0 || j>8) {canMove[i][d] = 0; continue;}
            if(!(d&1) && i/3!=j/3) {canMove[i][d] = 0; continue;}
            canMove[i][d] = 1;
        }
    }
    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {
            minPath[i][j] = abs(i/3-j/3) + abs(i%3-j%3);
        }
    }
    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {
            for(int k=0; k<9; k++) {
                hehe[i][j][k] = minPath[j][k] - minPath[i][k];
            }
        }
    }
}

int main(){//hdu1043
#ifndef ONLINE_JUDGE
    freopen("0_in.txt","r",stdin);
    // freopen("0_out.txt","w",stdout);
#endif

    init();
    while(Read()) {
        if(!ok()) {printf("unsolvable\n"); continue;}
        p=0;
        ans_p=-1;
        memset(Hash, -1, sizeof Hash);
        A_star();
        print_path(ans_p);
        printf("\n");
    }

    return 0;
}



















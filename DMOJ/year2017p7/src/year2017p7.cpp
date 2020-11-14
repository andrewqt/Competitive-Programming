#include <bits/stdc++.h>

using namespace std;

struct Node{
    int l, r, maxi, cnt;
};

Node seg[1600005];

int N, tim;
int blk[100005], l[100005], r[100005], et[200005], lvl[100005];
int par[100005][20];
long long dep[100005];
vector<pair<int,int>> graph[100005];

void dfs(int n){
    l[n] = ++tim;
    et[tim] = n;
    for(auto e : graph[n]){
        if(e.first != par[n][0]){
            dep[e.first] = dep[n] + e.second;
            lvl[e.first] = lvl[n] + 1;
            par[e.first][0] = n;
            dfs(e.first);
        }
    }
    r[n] = ++tim;
    et[tim] = n;
}

void build(int l, int r, int idx){
    seg[idx].l = l;
    seg[idx].r = r;
    seg[idx].cnt = 0;
    if(l == r){
        seg[2*idx].maxi = seg[idx].maxi = lvl[et[l]];
        return;
    }
    int mid = (l+r)/2;
    build(l, mid, 2*idx);
    build(mid+1, r, 2*idx+1);
    seg[idx].maxi = max(seg[2*idx].maxi, seg[2*idx+1].maxi);
}

void upd(int l, int r, int v, int idx){
    if(seg[idx].l == l && seg[idx].r == r){
        seg[idx].cnt += v;
        seg[idx].maxi = !seg[idx].cnt ? max(seg[2*idx].maxi, seg[2*idx+1].maxi) : 0;
        return;
    }
    int mid = (seg[idx].l + seg[idx].r)/2;
    if(r <= mid){
        upd(l, r, v, 2*idx);
    }
    else if(l > mid){
        upd(l, r, v, 2*idx+1);
    }
    else{
        upd(l, mid, v, 2*idx);
        upd(mid+1, r, v, 2*idx+1);
    }
    seg[idx].maxi = !seg[idx].cnt ? max(seg[2*idx].maxi, seg[2*idx+1].maxi) : 0;
}

int qu(int n, int v){
    for(int b = 17; b>=0; b--){
        if(dep[par[n][b]] >= v){
            n = par[n][b];
        }
    }
    return n;
}

int main(){
    scanf("%d", &N);
    for(int i = 1; i<=N; i++){
        scanf("%d", &blk[i]);
    }
    for(int i = 1; i<=N; i++){
        int n, v;
        scanf("%d %d", &n, &v);
        graph[n].push_back({i, v});
        graph[i].push_back({n, v});
    }
    dfs(0);
    build(0, 2*(N+1), 1);
    for(int i = 1; i<=17; i++){
        for(int j = 0; j<=N; j++){
            par[j][i] = par[par[j][i-1]][i-1];
        }
    }
    for(int i = 1; i<=N; i++){
        if(blk[i] <= dep[i]){
            int n = qu(i, blk[i]);
            upd(l[n], r[n], 1, 1);
        }
    }
    int Q;
    scanf("%d", &Q);
    while(Q--){
        int n, v;
        scanf("%d %d", &n, &v);
        if(blk[n] <= dep[n]){
            int x = qu(n, blk[n]);
            upd(l[x], r[x], -1, 1);
        }
        blk[n] = v;
        if(blk[n] <= dep[n]){
            int x = qu(n, blk[n]);
            upd(l[x], r[x], 1, 1);
        }
        printf("%d\n", seg[1].maxi);
    }
}

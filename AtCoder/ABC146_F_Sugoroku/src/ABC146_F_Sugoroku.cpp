#include <bits/stdc++.h>

using namespace std;

struct Node{
    int l, r, idx;
};

int N, M;
Node seg[400005];
int dp[100005], par[100005];

void build(int l, int r, int idx){
    seg[idx].l = l, seg[idx].r = r;
    if(l == r){
        seg[idx].idx = l;
        return;
    }
    int mid = l+r>>1;
    build(l, mid, 2*idx);
    build(mid+1, r, 2*idx+1);
    seg[idx].idx = seg[2*idx].idx;
}

void upd(int p, int idx){
    if(seg[idx].l == seg[idx].r){
        return;
    }
    int mid = seg[idx].l + seg[idx].r >> 1;
    if(p <= mid){
        upd(p, 2*idx);
    }
    else{
        upd(p, 2*idx+1);
    }
    if(dp[seg[2*idx].idx] <= dp[seg[2*idx+1].idx]){
        seg[idx].idx = seg[2*idx].idx;
    }
    else{
        seg[idx].idx = seg[2*idx+1].idx;
    }
}

int query(int l, int r, int idx){
    if(seg[idx].l == l && seg[idx].r == r){
        return seg[idx].idx;
    }
    int mid = seg[idx].l + seg[idx].r >> 1;
    if(r <= mid){
        return query(l, r, 2*idx);
    }
    else if(l > mid){
        return query(l, r, 2*idx+1);
    }
    else{
        int p = query(l, mid, 2*idx), q = query(mid+1, r, 2*idx+1);
        return (dp[p] <= dp[q] ? p : q);
    }
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    build(0, N, 1);
    char x;
    cin >> x;
    for(int i = 1; i<=N; i++){
        char c;
        cin >> c;
        if(c == '0'){
            int k = query(max(0, i-M), i-1, 1);
            dp[i] = dp[k] + 1;
            par[i] = k;
        }
        else{
            dp[i] = INT_MAX/2;
        }
        upd(i, 1);
    }
    if(dp[N] >= INT_MAX/2){
        cout << -1 << "\n";
        return 0;
    }
    stack<int> stk;
    int c = N;
    while(c){
        stk.push(c-par[c]);
        c = par[c];
    }
    while(stk.size()){
        cout << stk.top() << " ";
        stk.pop();
    }
}

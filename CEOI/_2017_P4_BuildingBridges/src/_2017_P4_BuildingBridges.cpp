#include <bits/stdc++.h>

using namespace std;

struct Node{
    int l, r;
    pair<long long, long long> k;
};

long long f(pair<long long, long long> l, long long n){
    return n*l.first+l.second;
}

int N, M = 1000000;
Node seg[4000005];
long long h[100005];
long long pre[100005];
long long dp[100005];

void build(int l, int r, int idx){
    seg[idx].l = l, seg[idx].r = r;
    seg[idx].k = {0, LLONG_MAX/10};
    if(l == r){
        return;
    }
    int mid = l+r>>1;
    build(l, mid, 2*idx);
    build(mid+1, r, 2*idx+1);
}

void upd(pair<long long, long long> n, int idx){
    if(seg[idx].l == seg[idx].r){
        if(f(n, seg[idx].l) < f(seg[idx].k, seg[idx].r)){
            seg[idx].k = n;
        }
        return;
    }
    int mid = seg[idx].l + seg[idx].r >> 1;
    bool lft = f(n, seg[idx].l) < f(seg[idx].k, seg[idx].l);
    bool m = f(n, mid+1) < f(seg[idx].k, mid+1);
    if(m){
        swap(n, seg[idx].k);
    }
    if(lft != m){
        upd(n, 2*idx);
    }
    else{
        upd(n, 2*idx+1);
    }
}

long long query(int n, int idx){
    if(seg[idx].l == seg[idx].r){
        return f(seg[idx].k, n);
    }
    int mid = seg[idx].l + seg[idx].r >> 1;
    if(n <= mid){
        return min(f(seg[idx].k, n), query(n, 2*idx));
    }
    else{
        return min(f(seg[idx].k, n), query(n, 2*idx+1));
    }
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    build(0, M, 1);
    for(int i =1 ; i<=N; i++){
        cin >> h[i];
    }
    for(int i = 1; i<=N; i++){
        cin >> pre[i];
        pre[i] += pre[i-1];
    }
    for(int i = 2; i<=N; i++){
        dp[i] = dp[1] + (h[i]-h[1])*(h[i]-h[1])+pre[i-1]-pre[1];
        dp[i] = min(dp[i], query(h[i], 1) + pre[i-1] + h[i]*h[i]);
        upd({-2*h[i], h[i]*h[i]-pre[i]+dp[i]}, 1);
        //cout << dp[i] << endl;
    }
    cout << dp[N] << endl;
}

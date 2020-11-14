#include <bits/stdc++.h>
#include "wiring.h"

using namespace std;

struct node{
    int l, r;
    long long mn, lzy;
};

int N;
long long pre[200005], arr[200005];
bool typ[200005];
node seg[800005];
long long dp[200005];

void pd(int idx){
    if(seg[idx].lzy){
        seg[2*idx].lzy += seg[idx].lzy;
        seg[2*idx+1].lzy += seg[idx].lzy;
        seg[2*idx].mn += seg[idx].lzy;
        seg[2*idx+1].mn += seg[idx].lzy;
        seg[idx].lzy = 0;
    }
}

void build(int l, int r, int idx){
    seg[idx].l = l, seg[idx].r = r;
    if(l == r){
        seg[idx].mn = LLONG_MAX/2;
        return;
    }
    int mid = l+r>>1;
    build(l, mid, 2*idx);
    build(mid+1, r, 2*idx+1);
    seg[idx].mn = LLONG_MAX/2;
}

void upd(int p, long long v, int idx){
    if(seg[idx].l == seg[idx].r){
        seg[idx].mn = v;
        return;
    }
    pd(idx);
    int mid = seg[idx].l + seg[idx].r >> 1;
    if(p <= mid){
        upd(p, v, 2*idx);
    }
    else{
        upd(p, v, 2*idx+1);
    }
    seg[idx].mn = min(seg[2*idx].mn, seg[2*idx+1].mn);
}

void add(int l, int r, long long v, int idx){
    if(seg[idx].l == l && seg[idx].r == r){
        seg[idx].mn += v;
        seg[idx].lzy += v;
        return;
    }
    pd(idx);
    int mid = seg[idx].l + seg[idx].r >> 1;
    if(r <= mid){
        add(l, r, v, 2*idx);
    }
    else if(l > mid){
        add(l, r, v, 2*idx+1);
    }
    else{
        add(l, mid, v, 2*idx);
        add(mid+1, r, v, 2*idx+1);
    }
    seg[idx].mn = min(seg[2*idx].mn, seg[2*idx+1].mn);
}

long long query(int l, int r, int idx){
    if(seg[idx].l == l && seg[idx].r == r){
        return seg[idx].mn;
    }
    pd(idx);
    int mid = seg[idx].l + seg[idx].r >> 1;
    if(r <= mid){
        return query(l, r, 2*idx);
    }
    else if(l > mid){
        return query(l, r, 2*idx+1);
    }
    else{
        return min(query(l, mid, 2*idx), query(mid+1, r, 2*idx+1));
    }
}

long long min_total_length(vector<int> red, vector<int> blu){
    N = red.size() + blu.size();
    int idx1 = 0, idx2 = 0;
    while(idx1 < red.size() || idx2 < blu.size()){
        if(idx2 == blu.size() || (idx1 < red.size() && red[idx1] < blu[idx2])){
            arr[idx2+idx1+1] = red[idx1];
            typ[idx2+idx1+1] = 1;
            idx1++;
        }
        else{
            arr[idx2+idx1+1] = blu[idx2];
            idx2++;
        }
    }
    partial_sum(arr, arr+N+1, pre);
    fill(dp+1, dp+1+N, LLONG_MAX/2);
    build(1, N, 1);
    int s = 2;
    while(typ[s] == typ[s-1]){
        s++;
    }
    int l, r;
    for(int i= s; i<=N; i++){
        if(typ[i]^typ[i-1]){
            l = r = i-1;
            upd(i-1, dp[i-2]-arr[r], 1);
            while(l > 1 && typ[l-1]^typ[i]){
                l--;
                upd(l, dp[l-1]-(pre[r]-pre[l-1])+(r-l)*arr[r+1], 1);
            }
        }
        dp[i] = dp[r] + pre[i] - pre[r] - arr[r]*(i-r);
        //cout << " " << arr[r]*(i-r) << " " << pre[i]-pre[r] << " " << dp[r] << endl;
        //cout << i << " " << query(3, 3, 1) << " " << pre[i]-pre[r] << " " << dp[i] << endl;
        dp[i] = min(dp[i], pre[i] - pre[r] + query(l, r, 1));
        int cut = r-(i-r-1);
        add(max(l, cut), r, -arr[r], 1);
        if(cut > l){
            add(l, cut-1, -arr[r+1], 1);
        }
        //cout << i << " " << dp[i] << endl;
    }
    return dp[N];
}

/*
int main(){
    cout << min_total_length({1, 2, 3, 7}, {0, 4, 5, 9, 10}) << endl;
}
*/

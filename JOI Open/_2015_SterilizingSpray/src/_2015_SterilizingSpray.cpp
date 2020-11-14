#include <bits/stdc++.h>

using namespace std;

struct node{
    int l, r;
    long long sum, mx;
};

int N, Q, K;
int arr[100005];
node seg[400005];

void pu(int idx){
    seg[idx].sum = seg[2*idx].sum + seg[2*idx+1].sum;
    seg[idx].mx = max(seg[2*idx].mx, seg[2*idx+1].mx);
}

void build(int l, int r, int idx){
    seg[idx].l = l, seg[idx].r = r;
    if(l == r){
        seg[idx].sum = seg[idx].mx = arr[l];
        return;
    }
    int mid = l+r>>1;
    build(l, mid, 2*idx);
    build(mid+1, r, 2*idx+1);
    pu(idx);
}

void upd(int p, int v, int idx){
    if(seg[idx].l == seg[idx].r){
        seg[idx].sum = seg[idx].mx = v;
        return;
    }
    int mid = seg[idx].l+seg[idx].r>>1;
    if(p <= mid){
        upd(p, v, 2*idx);
    }
    else{
        upd(p, v, 2*idx+1);
    }
    pu(idx);
}

void rng(int l, int r, int idx){
    if(seg[idx].mx == 0){
        return;
    }
    if(seg[idx].l == seg[idx].r){
        seg[idx].sum /= K;
        seg[idx].mx /= K;
        return;
    }
    int mid = seg[idx].l + seg[idx].r >> 1;
    if(r <= mid){
        rng(l, r, 2*idx);
    }
    else if(l > mid){
        rng(l, r, 2*idx+1);
    }
    else{
        rng(l, mid, 2*idx);
        rng(mid+1, r, 2*idx+1);
    }
    pu(idx);
}

long long query(int l, int r, int idx){
    if(seg[idx].l == l && seg[idx].r == r){
        return seg[idx].sum;
    }
    int mid = seg[idx].l + seg[idx].r >> 1;
    if(r <= mid){
        query(l, r, 2*idx);
    }
    else if(l > mid){
        query(l, r, 2*idx+1);
    }
    else{
        return query(l, mid, 2*idx) + query(mid+1, r, 2*idx+1);
    }
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> Q >> K;
    for(int i = 1; i<=N; i++){
        cin >> arr[i];
    }
    build(1, N, 1);
    while(Q--){
        int c, l, r;
        cin >> c >> l >> r;
        if(c == 1){
            upd(l, r, 1);
        }
        else if(c == 2){
            if(K > 1){
                rng(l, r, 1);
            }
        }
        else {
            cout << query(l, r, 1) << "\n";
        }
    }
}

#include <bits/stdc++.h>

using namespace std;

struct Node{
    int l, r;
    int mini, maxi;
};

Node seg[10000005];

void build(int l, int r, int idx){
    seg[idx].l = l, seg[idx].r = r;
    if(l == r){
        return;
    }
    int mid = l+r>>1;
    build(l, mid, 2*idx);
    build(mid+1, r, 2*idx+1);
}

void pd(int idx){
    for(int i = 2*idx; i<=2*idx+1; i++){
        seg[i].mini = min(seg[i].mini, seg[idx].mini);
        seg[i].maxi = min(seg[i].maxi, seg[idx].mini);
        seg[i].mini = max(seg[i].mini, seg[idx].maxi);
        seg[i].maxi = max(seg[i].maxi, seg[idx].maxi);
    }
    seg[idx].mini = INT_MAX, seg[idx].maxi = 0;
}

void add(int l, int r, int v, int idx){
    if(seg[idx].l == l && seg[idx].r == r){
        seg[idx].maxi = max(seg[idx].maxi, v);
        seg[idx].mini = max(seg[idx].mini, v);
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
}

void rem(int l, int r, int v, int idx){
    if(seg[idx].l == l && seg[idx].r == r){
        seg[idx].maxi = min(seg[idx].maxi, v);
        seg[idx].mini = min(seg[idx].mini, v);
        return;
    }
    pd(idx);
    int mid = seg[idx].l + seg[idx].r >> 1;
    if(r <= mid){
        rem(l, r, v, 2*idx);
    }
    else if(l > mid){
        rem(l, r, v, 2*idx+1);
    }
    else{
        rem(l, mid, v, 2*idx);
        rem(mid+1, r, v, 2*idx+1);
    }
}

int query(int p, int idx){
    if(seg[idx].l == seg[idx].r){
        return seg[idx].mini;
    }
    pd(idx);
    if(p <= seg[idx].l + seg[idx].r >> 1){
        return query(p, 2*idx);
    }
    else{
        return query(p, 2*idx+1);
    }
}

void buildWall(int N, int K, int t[], int l[], int r[], int h[], int ans[]){
    build(0, N-1, 1);
    for(int k = 0; k<K; k++){
        if(t[k]-1){
            rem(l[k], r[k], h[k], 1);
        }
        else{
            add(l[k], r[k], h[k], 1);
        }
    }
    for(int i = 0; i<N; i++){
        ans[i] = query(i, 1);
    }
}

int main(){

}

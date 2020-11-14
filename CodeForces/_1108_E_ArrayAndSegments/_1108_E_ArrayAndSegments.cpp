#include <bits/stdc++.h>

using namespace std;

struct Node{
    int l, r, lazy, mini;
};

Node seg[400005];

void build(int l, int r, int idx){
    seg[idx].l = l;
    seg[idx].r = r;
    if(l == r){
        return;
    }
    build(l, (l+r)/2, 2*idx);
    build((l+r)/2+1, r, 2*idx+1);
};

void pd(int idx){
    seg[2*idx].mini += seg[idx].lazy;
    seg[2*idx+1].mini += seg[idx].lazy;
    seg[2*idx].lazy += seg[idx].lazy;
    seg[2*idx+1].lazy += seg[idx].lazy;
    seg[idx].lazy = 0;
}

void upd(int l, int r, int v, int idx){
    if(seg[idx].l == l && seg[idx].r == r){
        seg[idx].mini += v;
        seg[idx].lazy += v;
        return;
    }
    pd(idx);
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
};

int qu(int l, int r, int idx){
    if(seg[idx].l == l && seg[idx].r == r){
        return seg[idx].mini;
    }
    pd(idx);
    int mid = (seg[idx].l + seg[idx].r)/2;
    if(r <= mid){
        return qu(l, r, 2*idx);
    }
    else if(l > mid){
        return qu(l, r, 2*idx+1);
    }
    else{
        return min(qu(l, mid, 2*idx), qu(mid+1, r, 2*idx+1)));
    }
}

int main(){

}

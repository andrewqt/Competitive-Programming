#include <bits/stdc++.h>

using namespace std;

struct Node{
    int l, r;
    long long sum, lazys, lazyd;
};

Node seg[4000005];

void build(int l, int r, int idx){
    seg[idx].l =l;
    seg[idx].r = r;
    if(l == r){
        return;
    }
    int mid = (l+r)/2;
    build(l , mid, 2*idx);
    build(mid+1, r, 2*idx+1);
    seg[idx].sum = seg[2*idx].sum + seg[2*idx+1].sum;
}

void pd(int idx){
    long long rngrht = seg[2*idx+1].r - seg[2*idx+1].l + 1;
    long long rnglft = seg[2*idx].r - seg[2*idx].l + 1;
    seg[2*idx].lazys += seg[idx].lazys;
    seg[2*idx].lazyd += seg[idx].lazyd;
    seg[2*idx+1].lazyd += seg[2*idx+1].lazyd;
    seg[2*idx+1].lazys += seg[idx].lazyd*(rnglft) + seg[idx].lazys;
    seg[2*idx].sum += seg[idx].lazys*rnglft;
    seg[2*idx].sum += seg[idx].lazyd*(rnglft)*(rnglft+1)/2;
    seg[2*idx+1].sum += seg[idx].lazys*rngrht*(rngrht+1)/2;
    seg[2*idx+1].sum += seg[idx].lazyd*(rnglft) + seg[idx].lazys;
    seg[idx].lazys = seg[idx].lazyd = 0;
}

void upd(int l, int r, long long s, long long d, int idx){
    if(seg[idx].l == l && seg[idx].r == r){
        long long rng = r-l+1;
        seg[idx].sum += rng*(rng+1)/2 * d;
        seg[idx].sum += rng*s;
        seg[idx].lazys += s;
        seg[idx].lazyd += d;
        return;
    }
    int mid = (seg[idx].l + seg[idx].r)/2;
    if(seg[idx].lazyd != 0){
        pd(idx);
    }
    if(r <= mid){
        upd(l, r, s, d, 2*idx);
    }
    else if(l > mid){
        upd(l, r, s, d, 2*idx+1);
    }
    else{
        upd(l, mid, s, d, 2*idx);
        upd(mid+1, r, (seg[2*idx].r-l+1)*d+s, d, 2*idx+1);
    }
    seg[idx].sum = seg[2*idx].sum + seg[2*idx+1].sum;
}

long long query(int l, int r, int idx){
    if(seg[idx].l == l && seg[idx].r == r){
        return seg[idx].sum;
    }
    int mid = (seg[idx].l + seg[idx].r)/2;
    if(seg[idx].lazyd != 0){
        pd(idx);
    }
    if(r <= mid){
        return query(l, r, 2*idx);
    }
    else if(l > mid){
        return query(l, r, 2*idx+1);
    }
    else{
        return query(l, mid, 2*idx) + query(mid+1, r, 2*idx+1);
    }
}

int N, K;

int main(){
    scanf("%d %d", &N, &K);
    build(1, N, 1);
    while(K--){
        int l, r, t;
        scanf("%d %d %d", &t, &l, &r);
        if(t == 1){
            int a;
            scanf("%d", &a);
            upd(l, r, 0, a, 1);
        }
        else{
            printf("%d\n", query(l, r, 1));
        }
    }
}

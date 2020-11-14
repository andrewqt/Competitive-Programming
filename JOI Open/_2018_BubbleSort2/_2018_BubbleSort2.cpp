#include <bits/stdc++.h>

using namespace std;

struct Node{
    int l, r, maxi, cnt, lzy;
};

int N, K, Q;
Node seg[4000005];
vector<pair<int, int>> cmp;
set<pair<int, int>> st;

void pu(int idx){
    seg[idx].cnt = seg[2*idx].cnt + seg[2*idx+1].cnt;
    seg[idx].maxi = max(seg[2*idx].maxi, seg[2*idx+1].maxi);
}

void pd(int idx){
    seg[2*idx].maxi -= seg[idx].lzy;
    seg[2*idx+1].maxi -= seg[idx].lzy;
    seg[2*idx].maxi += seg[idx].lzy;
    seg[2*idx+1].maxi += seg[idx].lzy;
    seg[idx].lzy = 0;
}

void build(int l, int r, int idx){
    seg[idx].l = l;
    seg[idx].r = r;
    if(l == r){
        if(st.count(cmp[l-1])){
            seg[idx].cnt = 1;
            seg[idx].maxi = cmp[l-1].second - st.find(cmp[l-1]) - st.begin();
        }
        return ;
    }
    int mid = l+r >> 1;
    build(l, mid, 2*idx);
    build(mid+1, r, 2*idx+1);
    pu(idx);
}

int query(int l, int r, int idx){
    if(seg[idx].l == l && seg[idx].r == r){
        return seg[idx].cnt;
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
        return query(l, mid, 2*idx) + query(mid+1, r, 2*idx+1);
    }
}


void chn(int p, int v, int idx){
    if(seg[idx].l == l && seg[idx].r == r){
        if(v){
            seg[idx].maxi = cmp[p-1].second - query(1, p, 1);
            seg[idx].cnt = 1;
        }
        else{
            seg[idx].cnt = 0;
            seg[idx].maxi = 0;
        }
        return;
    }
    pd(idx);
    int mid = seg[idx].l + seg[idx].r >> 1;
    if(p <= mid){
        chn(p, v, 2*idx);
    }
    else{
        chn(p, v, 2*idx+1);
    }
    pu(idx);
}

void upd(int l, int r, int v, int idx){
    if(seg[idx].l == l && seg[idx].r == r){
        seg[idx].maxi -= v;
        seg[idx].lzy += v;
        return;
    }
    pd(idx);
    int mid = seg[idx].l + seg[idx].r >> 1;
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
    pu(idx);
}

vector<int> countScans(vector<int> arr, vector<int> pos, vector<int> val){
    vector<int> ans;
    N = arr.size();
    for(int i = 0; i<N; i++){
        cmp.push_back({arr[i], i});
        st.insert({arr[i], i});
    }
    Q = pos.size();
    for(int i = 0; i<Q; i++){
        cmp.push_back({val[i], pos[i]});
    }
    sort(cmp.begin(), cmp.end());
    cmp.erase(unique(cmp.begin(), cmp.end()), cmp.end());
    K = cmp.size();
    build(1, K, 1);
    for(int q= 0; q<Q; i++){
    }
    return ans;
}

int main(){

}

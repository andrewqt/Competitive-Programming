#include <bits/stdc++.h>

using namespace std;

struct Node{
    int l, r, lzy, v;
    vector<int> nxt;
    vector<int> another;
};

int N, K, Q;
Node seg[1000000];
int arr[1000000];

void pd(int idx){
    swap(seg[2*idx].nxt, seg[2*idx].another);
    swap(seg[2*idx+1].nxt, seg[2*idx+1].another);
    seg[2*idx].lzy ^= 1;
    seg[2*idx+1].lzy ^= 1;
    seg[2*idx].v ^= 1;
    seg[2*idx+1].v ^= 1;
    seg[idx].lzy = 0;
}

void pu(int idx){
    cout << "open" << endl;
    seg[idx].nxt.clear(), seg[idx].another.clear();
    for(int k = 0; k<=K; k++){
        seg[idx].nxt.push_back(seg[2*idx].nxt[min(seg[2*idx+1].nxt[k], K)]);
        seg[idx].another.push_back(seg[2*idx].another[min(seg[2*idx+1].another[k], K)]);
    }
    cout << "closed" << endl;
}

void build(int l, int r, int idx){
    seg[idx].l =l , seg[idx].r = r;
    if(l == r){
        for(int k = 0; k<=K; k++){
            if(arr[r] == 1){
                if(k == K){
                    seg[idx].nxt.push_back(0);
                }
                else{
                    seg[idx].nxt.push_back(k+1);
                }
            }
            else{
                seg[idx].nxt.push_back(k+1);
            }
        }
        seg[idx].v = arr[r];
        for(int k = 0; k<=K; k++){
            if(arr[r] == 0){
                if(k == K){
                    seg[idx].another.push_back(0);
                }
                else{
                    seg[idx].another.push_back(k+1);
                }
            }
            else{
                seg[idx].another.push_back(k+1);
            }
        }
        return ;
    }
    int mid = l + r >> 1;
    build(l, mid, 2*idx);
    build(mid+1, r, 2*idx+1);
    pu(idx);
}

void upd(int l, int r, int idx){
    if(seg[idx].l == l && seg[idx].r == r){
        swap(seg[idx].another, seg[idx].nxt);
        seg[idx].lzy ^= 1;
        seg[idx].v ^= 1;
        return;
    }
    if(seg[idx].lzy){
        pd(idx);
    }
    int mid = seg[idx].l + seg[idx].r >> 1;
    if(r <= mid){
        upd(l, r, 2*idx);
    }
    else if(l > mid){
        upd(l,r, 2*idx+1);
    }
    else{
        upd(l, mid, 2*idx);
        upd(mid+1, r, 2*idx+1);
    }
    pu(idx);
}

int getidx(int p, int idx){
    if(seg[idx].l == seg[idx].r){
        return seg[idx].v;
    }
    if(seg[idx].lzy){
        pd(idx);
    }
    int mid = seg[idx].l + seg[idx].r >> 1;
    if(p <= mid){
        return getidx(p, 2*idx);
    }
    else{
        return getidx(p, 2*idx+1);
    }
}

int query(int l, int r, int lst0, int idx){
    if(seg[idx].l == l && seg[idx].r == r){
        return seg[idx].nxt[lst0];
    }
    if(seg[idx].lzy){
        pd(idx);
    }
    int mid = seg[idx].l + seg[idx].r >> 1;
    if(r <= mid){
        return query(l, r, lst0, 2*idx);
    }
    else if(l > mid){
        return query(l, r, lst0, 2*idx+1);
    }
    else{
        return query(l, mid, query(mid+1, r, lst0, 2*idx+1), 2*idx);
    }
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> K >> Q;
    for(int i =1; i<=N; i++){
        cin >> arr[i];
        arr[i] &= 1;
        arr[i] ^= 1;
    }
    build(1, N, 1);
    while(Q--){
        int c, l, r;
        cin >> c >> l >> r;
        if(c == 1){
            int d;
            cin >> d;
            d &= 1;
            if(d){
                upd(l, r, 1);
            }
        }
        else{
            int idx = getidx(r, 1);
            if(l == r){
                if(idx){
                    cout << 1 << "\n";
                }
                else{
                    cout << 2 << "\n";
                }
            }
            else{
                if(query(l, r, idx, 1)){
                    cout << 1 << "\n";
                }
                else{
                    cout << 2 << "\n";
                }
            }
        }
    }
}

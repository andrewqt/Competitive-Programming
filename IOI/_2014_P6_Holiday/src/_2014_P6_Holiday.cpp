#include <bits/stdc++.h>

using namespace std;

struct Node{
    int l, r;
    int cnt;
    long long sum;
    int lft, rht;
    Node cop(){
        Node x;
        x.l = l, x.r = r;
        x.cnt = cnt, x.sum = sum;
        x.lft = lft, x.rht = rht;
        return x;
    }
};

Node seg[5000000];
int c;
vector<pair<int, int>> cmp;
long long best[500000][4];
int rt[500000];

int getIdx(int v, int idx){
    return lower_bound(cmp.begin(), cmp.end(), make_pair(-v, idx)) - cmp.begin() + 1;
}

int build(int l, int r){
    int idx = ++c;
    seg[idx].l =l, seg[idx].r = r;
    if(l == r){
        return idx;
    }
    int mid = l +r >> 1;
    seg[idx].lft = build(l, mid);
    seg[idx].rht = build(mid+1, r);
    return idx;
}

int upd(int p, int v, int n){
    //cout << seg[n].l << " " << seg[n].r << endl;
    int idx = ++c;
    seg[idx] = seg[n].cop();
    if(seg[idx].l == seg[idx].r){
        seg[idx].sum = v;
        seg[idx].cnt = 1;
        return idx;
    }
    int mid = seg[idx].l + seg[idx].r >> 1;
    if(p <= mid){
        seg[idx].lft = upd(p, v, seg[idx].lft);
    }
    else{
        seg[idx].rht = upd(p, v, seg[idx].rht);
    }
    seg[idx].sum = seg[seg[idx].lft].sum + seg[seg[idx].rht].sum;
    seg[idx].cnt = seg[seg[idx].lft].cnt + seg[seg[idx].rht].cnt;
    //cout << seg[idx].sum << endl;
    return idx;
}

long long clmb(int k, int idx){
    if(seg[idx].l == seg[idx].r){
        return seg[idx].sum;
    }
    if(seg[seg[idx].lft].cnt >= k){
        return clmb(k, seg[idx].lft);
    }
    else{
        return clmb(k-seg[seg[idx].lft].cnt, seg[idx].rht) + seg[seg[idx].lft].sum;
    }
}

void solve(int l, int r, int x, int y, int k, int t){
    if(l > r){
        return;
    }
    int m = l+r>>1;
    int idx = 0;
    for(int i = x; i<=y; i++){
        if(m-k*i <= 0){
            break;
        }
        long long v = clmb(max(0, m-k*i), rt[i]);
        //cout << max(0, m-k*i) << " " << v << endl;
        if(best[m][t] < v){
            idx = i;
            best[m][t] = v;
        }
    }
    solve(l, m-1, x, idx, k, t);
    solve(m+1, r, idx, y, k, t);
}

long long int findMaxAttraction(int N, int S, int K, int v[]){
    cmp.push_back({0, 0});
    for(int i = 0; i<N; i++){
        cmp.push_back({-v[i], i});
    }
    sort(cmp.begin(), cmp.end());
    rt[0] = build(1, N+5);
    vector<int> c;
    for(int i = 0; i<S; i++){
        c.push_back(v[i]);
    }
    reverse(c.begin(), c.end());
    for(int i = 1; i<=S; i++){
        //cout << "here" << endl;
        rt[i] = upd(getIdx(c[i-1], S-i), c[i-1], rt[i-1]);
    }
    solve(1, K, 1, S, 1, 0);
    solve(1, K, 1, S, 2, 1);
    //cout << "here" << endl;
    rt[0] = upd(getIdx(v[S], S), v[S], rt[0]);
    for(int i = S+1; i<N; i++){
        //cout << "here" << endl;
        rt[i-S] = upd(getIdx(v[i], i), v[i], rt[i-S-1]);
    }
    S = N-S-1;
    solve(1, K, 0, S, 1, 2);
    solve(1, K, 0, S, 2, 3);
    long long ret = 0;
    for(int k = 0; k<=K; k++){
        ret = max(ret, best[k][0] + best[K-k][3]);
        ret = max(ret, best[k][1] + best[K-k][2]);
        //cout << best[k][0] << " " << best[k][1] << " " << best[k][2] << " " << best[k][3] << endl;
    }
    return ret;
}

int in[13] = {457940913, 135212905, 391998879, 842039087, 94655553, 759877881, 342814101, 601803978, 287201661, 211930397, 641915086, 864584874, 184542658};

int main(){
    cout << findMaxAttraction(13, 9, 7, in) << endl;
}



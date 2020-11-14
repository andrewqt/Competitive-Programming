#include <bits/stdc++.h>

using namespace std;

int N, M;
long long dplft[500005], dprht[500005], cst[100005];
int lft[100005], rht[100005], drp[100005];
vector<int> cmp;

struct Node{
    int l, r;
    long long mini;
};

Node seg[2][2000005];

void build(int l, int r, int idx){
    seg[0][idx].l = seg[1][idx].l = l;
    seg[0][idx].r = seg[1][idx].r = r;
    seg[0][idx].mini = seg[1][idx].mini = LLONG_MAX;
    if(l == r){
        return;
    }
    int mid = (l+r)/2;
    build(l, mid, 2*idx);
    build(mid+1, r, 2*idx+1);
}

void upd(int p, long long v, int idx, int tree){
//    cout << p << " " << seg[tree][idx].l << " " << seg[tree][idx].r << endl;
    if(seg[tree][idx].l == seg[tree][idx].r){
        seg[tree][idx].mini = v;
        return;
    }
    int mid = (seg[tree][idx].l + seg[tree][idx].r)/2;
    if(p <= mid){
        upd(p, v, 2*idx, tree);
    }
    else{
        upd(p, v, 2*idx+1, tree);
    }
    seg[tree][idx].mini = min(seg[tree][2*idx].mini, seg[tree][2*idx+1].mini);
}

long long query(int l, int r, int idx, int tree){
//    cout << l << " " << r << " " << idx << " " << tree << " " << seg[tree][idx].l << " " << seg[tree][idx].r << endl;
    if(seg[tree][idx].l == l && seg[tree][idx].r == r){
        return seg[tree][idx].mini;
    }
    int mid = (seg[tree][idx].l + seg[tree][idx].r)/2;
    if(r <= mid){
        return query(l, r, 2*idx, tree);
    }
    else if(l > mid){
        return query(l, r, 2*idx+1, tree);
    }
    else{
        return min(query(l, mid, 2*idx, tree), query(mid+1, r, 2*idx+1, tree));
    }
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i = 1; i<=N; i++){
        scanf("%d %d %d %lld", &lft[i], &rht[i], &drp[i], &cst[i]);
        cmp.push_back(lft[i]);
        cmp.push_back(rht[i]);
        cmp.push_back(drp[i]);
    }
    cmp.push_back(1);
    cmp.push_back(M);
    sort(cmp.begin(), cmp.end());
    cmp.erase(unique(cmp.begin(), cmp.end()), cmp.end());
    int lrng = 1, rrng = cmp.end() - cmp.begin();
    fill(dplft, dplft+rrng+1, LLONG_MAX);
    fill(dprht, dprht+rrng+1, LLONG_MAX);
    build(lrng, rrng, 1);
    upd(lrng, 0, 1, 0);
    upd(rrng, 0, 1, 1);
    dplft[lrng] = 0;
    dprht[rrng] = 0;
    long long ans = LLONG_MAX;
    for(int i = 1; i<=N; i++){
        int drpidx = lower_bound(cmp.begin(), cmp.end(), drp[i]) - cmp.begin() + 1;
        int lbidx = lower_bound(cmp.begin(), cmp.end(), lft[i]) - cmp.begin() + 1;
        int ubidx = lower_bound(cmp.begin(), cmp.end(), rht[i]) - cmp.begin() + 1;
//        cout << drpidx << " " << lbidx << " " << ubidx << endl;
//        cout << dplft[drpidx] << " " << dprht[drpidx] << endl;
        long long lftval = query(lbidx, ubidx, 1, 0);
        long long rhtval = query(lbidx, ubidx, 1, 1);
        if(lftval != LLONG_MAX && rhtval != LLONG_MAX){
            ans = min(lftval + rhtval + cst[i], ans);
        }
        if(lftval != LLONG_MAX){
            dplft[drpidx] = min(dplft[drpidx], lftval + cst[i]);
        }
        upd(drpidx, dplft[drpidx], 1, 0);
        if(rhtval != LLONG_MAX){
            dprht[drpidx] = min(dprht[drpidx], rhtval + cst[i]);
        }
        upd(drpidx, dprht[drpidx], 1, 1);
//        cout << dplft[drpidx] << " " << dprht[drpidx] << endl;
//        cout << ans << endl;
    }
    if(ans == LLONG_MAX){
        ans = -1;
    }
    printf("%lld\n", ans);
}

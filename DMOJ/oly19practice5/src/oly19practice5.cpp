#include <bits/stdc++.h>

using namespace std;

int N, Q;
long long segsum[800005], seglazysum[800005];
int segl[800005], segr[800005];
bool seglazymult[800005];
bool typ[200005];
int lft[200005], rht[200005];
int lstupd[800005], cnt = 0;
long long val[200005];
int ans[200005];
vector<int> arr;

inline void build(int l, int r, int idx){
    segl[idx] = l;
    segr[idx] = r;
    seglazymult[idx] = 1;
    if(l == r){
        return;
    }
    int mid = (l+r)/2;
    build(l, mid, idx<<1);
    build(mid+1, r, (idx<<1)|1);
}

inline void pushdown(int idx){
    int lft = idx<<1, rht = lft|1;
    if(!seglazymult[idx]){
        segsum[lft] = seglazysum[lft] = seglazymult[lft] = 0;
        segsum[rht] = seglazysum[rht] = seglazymult[rht] = 0;
        seglazymult[idx] = 1;
    }
    if(seglazysum[idx]){
        segsum[lft] += seglazysum[idx]*(segr[lft]-segl[lft]+1);
        segsum[rht] += seglazysum[idx]*(segr[rht]-segl[rht]+1);
        seglazysum[lft] += seglazysum[idx];
        seglazysum[rht] += seglazysum[idx];
        seglazysum[idx] = 0;
    }
}

inline void upd(int l, int r, int idx){
    if(segl[idx] == l && segr[idx] == r){
        segsum[idx] += segr[idx]-segl[idx]+1;
        seglazysum[idx]++;
        return;
    }
    pushdown(idx);
    int mid = (segl[idx]+segr[idx])>>1;
    if(r <= mid){
        upd(l, r, idx<<1);
    }
    else if(l > mid){
        upd(l, r, (idx<<1)|1);
    }
    else{
        upd(l, mid, idx<<1);
        upd(mid+1, r, (idx<<1)|1);
    }
    segsum[idx] = segsum[idx<<1] + segsum[(idx<<1)|1];
}

inline long long sum(int l, int r, int idx){
    if(segl[idx] == l && segr[idx] == r){
        return segsum[idx];
    }
    pushdown(idx);
    int mid = (segl[idx]+segr[idx])>>1;
    if(r <= mid){
        return sum(l, r, idx<<1);
    }
    else if(l > mid){
        return sum(l, r, (idx<<1)|1);
    }
    else{
        return sum(l, mid, idx<<1) + sum(mid+1, r, (idx<<1)|1);
    }
}

//upd is 0, qur is 1

inline void rec(vector<int> query, int l, int r){
    if(l > r || query.empty()){
        return;
    }
    cnt++;
    int mid = (l+r)>>1;
//    cout << l << " " << r << " " << mid << endl;
    vector<int> left, right;
    for(int i : query){
        if(typ[i]){
            long long s = sum(lft[i], rht[i], 1);
//            cout << "query: " << i << " " << lft[i] << " " << rht[i] << " " << val[i] << " " << s << endl;
            if(s >= val[i]){
                ans[i] = mid;
                right.push_back(i);
            }
            else{
                val[i] -= s;
                left.push_back(i);
            }
        }
        else{
//            cout << "upd: " << i << " " << lft[i] << " " << rht[i] << " " << val[i] << endl;
            if(val[i] >= mid){
                upd(lft[i], rht[i], 1);
                if(val[i] > mid){
                    right.push_back(i);
                }
            }
            else{
                left.push_back(i);
            }
        }
    }
    segsum[1] = seglazysum[1] = seglazymult[1] = 0;
    rec(left, l, mid-1);
    rec(right, mid+1, r);
}

int main(){
    scanf("%d %d", &N, &Q);
    build(1, N, 1);
    for(int i= 1; i<=Q; i++){
        int t;
        scanf("%d", &t);
        typ[i] = t-1;
        scanf("%d %d %lld", &lft[i], &rht[i], &val[i]);
        arr.push_back(i);
    }
    rec(arr, 1, N);
    for(int i = 1; i<=Q; i++){
        if(ans[i]){
            printf("%d\n", ans[i]);
        }
    }
}

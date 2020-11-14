#include <bits/stdc++.h>

using namespace std;

struct sling{
    int f, t, d;
    bool operator < (sling s) const{
        return f < s.f;
    }
    bool operator == (sling s){
        //cout << (f == s.f) << " " << (t == s.t) << " " << (d == s.d) << endl;
        //cout << f << " " << s.f << " " << t << " " << s.t << " " << d << " " << s.d << endl;
        return f == s.f && t == s.t && d == s.d;
    }
};

struct query{
    int f, t, idx;
    bool operator < (query q) const{
        return f < q.f;
    }
};

struct node{
    int l, r;
    long long mn[4];
};

int N, Q;
sling arr[100005], srt[100005];
query qu[100005];
node seg[400050];
int ans[100005];

bool comp(sling f, sling s){
    if(f.f == s.f && f.t == s.t){
        return f.d < s.d;
    }
    else if(f.t == s.t){
        return f.f < s.f;
    }
    else{
        return f.t < s.t;
    }
}

void build(int l, int r, int idx){
    seg[idx].l = l, seg[idx].r = r;
    seg[idx].mn[0] = seg[idx].mn[1] = LLONG_MAX/2;
    seg[idx].mn[2] = seg[idx].mn[3] = LLONG_MAX/2;
    if(l == r){
        return;
    }
    int mid = l+r>>1;
    build(l, mid, 2*idx);
    build(mid+1, r, 2*idx+1);
}

void upd(int p, int t, long long v, int idx){
    if(seg[idx].l == seg[idx].r){
        seg[idx].mn[t] = v;
        return;
    }
    int mid = seg[idx].l + seg[idx].r >> 1;
    if(p <= mid){
        upd(p, t, v, 2*idx);
    }
    else{
        upd(p, t, v, 2*idx+1);
    }
    seg[idx].mn[t] = min(seg[2*idx].mn[t], seg[2*idx+1].mn[t]);
}

long long query(int l, int r, int t, int idx){
    if(seg[idx].l == l && seg[idx].r == r){
        return seg[idx].mn[t];
    }
    int mid = seg[idx].l + seg[idx].r >> 1;
    if(r <= mid){
        return query(l, r, t, 2*idx);
    }
    else if(l > mid){
        return query(l, r, t, 2*idx+1);
    }
    else{
        return min(query(l, mid, t, 2*idx), query(mid+1, r, t, 2*idx+1));
    }
}

int bs(sling s){
    int l = 1, r = N;
    while(l <= r){
        int mid = l+r>>1;
        if(srt[mid] == s){
            return mid;
        }
        else if(comp(s, srt[mid])){
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    assert(0);
}

int bs(int t){
    int l = 1, r = N, ret = 0;
    while(l <= r){
        int mid = l+r>>1;
        if(srt[mid].t <= t){
            ret = mid;
            l = mid + 1;
        }
        else{
            r = mid - 1;
        }
    }
    return ret;
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    if(fopen("slingshot.in", "r")){
        freopen("slingshot.in", "r", stdin);
        freopen("slingshot.out", "w", stdout);
    }
    cin >> N >> Q;
    for(int i = 1; i<=N; i++){
        cin >> arr[i].f >> arr[i].t >> arr[i].d;
        srt[i] = arr[i];
    }
    for(int q = 1; q<=Q; q++){
        cin >> qu[q].f >> qu[q].t;
        qu[q].idx = q;
    }
    sort(qu+1, qu+1+Q);
    sort(arr+1, arr+1+N);
    sort(srt+1, srt+1+N, comp);
    build(0, N+1, 1);
    for(int i = 1; i<=N; i++){
        upd(i, 0, srt[i].f+srt[i].t+srt[i].d, 1);
        upd(i, 3, srt[i].f-srt[i].t+srt[i].d, 1);
    }
    int idx = 1;
    for(int q = 1; q<=Q; q++){
        while(idx <= N && arr[idx].f <= qu[q].f){
            int n = bs(arr[idx]);
            //cout << "ding " << n << endl;
            upd(n, 0, LLONG_MAX>>1, 1);
            upd(n, 3, LLONG_MAX>>1, 1);
            upd(n, 1, -arr[idx].f+arr[idx].t+arr[idx].d, 1);
            upd(n, 2, -arr[idx].f-arr[idx].t+arr[idx].d, 1);
            idx++;
        }
        long long out = abs(qu[q].f-qu[q].t);
        int spt = bs(qu[q].t);
        //cout << "query: " << q << " " << spt << endl;
        out = min(out, query(spt+1, N+1, 0, 1)-qu[q].f-qu[q].t);
        //cout << query(spt+1, N+1, 0, 1) << " " << query(spt+1, N+1, 0, 1)-qu[q].f-qu[q].t << endl;
        out = min(out, query(spt+1, N+1, 1, 1)+qu[q].f-qu[q].t);
        //cout << query(spt+1, N+1, 1, 1)+qu[q].f-qu[q].t << endl;
        out = min(out, query(0, spt, 2, 1)+qu[q].f+qu[q].t);
        //cout << query(0, spt, 2, 1)+qu[q].f+qu[q].t << endl;
        out = min(out, query(0, spt, 3, 1)-qu[q].f+qu[q].t);
        //cout << query(0, spt, 3, 1)-qu[q].f+qu[q].t << endl;
        ans[qu[q].idx] = out;
    }
    for(int q = 1; q<=Q; q++){
        cout << ans[q] << "\n";
    }
}

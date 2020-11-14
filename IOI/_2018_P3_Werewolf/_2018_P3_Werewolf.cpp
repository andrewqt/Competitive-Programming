#include <bits/stdc++.h>

using namespace std;

//graph1, prefix, R
//graph2, suffix, L

struct Query{
    int n, id;
};

int lseg[6400005], rseg[6400005], sseg[6400005];
vector<int> graph[200005][3];
int lft[200005][2], rht[200005][2], ETtm = 0;
int par[200005];
int anc[200005][18][2];
int ET[400005];
vector<Query> qu[400005];

inline void build(int l, int r, int idx){
    lseg[idx] = l;
    rseg[idx] = r;
    if(l == r){
        return;
    }
    int mid = (l+r)>>1;
    build(l, mid, 2*idx);
    build(mid+1, r, 2*idx+1);
}

inline void upd(int p, int idx){
    sseg[idx]++;
    if(lseg[idx] == rseg[idx]){
        return;
    }
    int mid = (lseg[idx] + rseg[idx])>>1;
    if(p <= mid){
        upd(p, 2*idx);
    }
    else{
        upd(p, 2*idx+1);
    }
}

inline int sum(int l, int r, int idx){
    if(lseg[idx] == l && rseg[idx] == r){
        return sseg[idx];
    }
    int mid = (lseg[idx] + rseg[idx])>>1;
    if(r <= mid){
        return sum(l, r, 2*idx);
    }
    else if(l > mid){
        return sum(l, r, 2*idx+1);
    }
    else{
        return sum(l, mid, 2*idx) + sum(mid+1, r, 2*idx+1);
    }
}

inline int getrt(int n){
    return par[n] = (par[n] == n ? n : getrt(par[n]));
}

inline void dfs(int n, int t){
    lft[n][t] = ++ETtm;
    ET[ETtm] = n;
    for(int e : graph[n][t]){
        anc[e][0][t] = n;
        dfs(e, t);
    }
    rht[n][t] = ++ETtm;
    ET[ETtm] = -n;
}

inline void buildtbl(int t, int N){
    for(int d = 1; d<=17; d++){
        for(int n = 1; n<=N; n++){
            anc[n][d][t] = anc[anc[n][d-1][t]][d-1][t];
            if(anc[n][d][t] == 0 && t == 1){
                anc[n][d][t] = N+1;
            }
        }
    }
}

inline int binlift(int n, int t, int lim){
    int co = (t==1) ? 1 : -1;
    for(int d = 17; d>=0; d--){
        if(co*anc[n][d][t] <= lim*co){
            n = anc[n][d][t];
        }
    }
    return n;
}

vector<int> check_validity(int N, vector<int> X, vector<int> Y,
                           vector<int> S, vector<int> E, vector<int> L, vector<int> R){
    int Q = S.size();
    vector<int> ans(Q);
    for(int e = 0; e<X.size(); e++){
        graph[++X[e]][0].push_back(++Y[e]);
        graph[Y[e]][0].push_back(X[e]);
    }
    for(int i = 1; i<=N; i++){
        par[i] = i;
    }
    for(int n = 1; n<=N; n++){
        for(int e : graph[n][0]){
            if(n > e){
                if(n != getrt(e)){
                    int rt = getrt(e);
                    par[rt] = n;
                    graph[n][1].push_back(rt);
                }
            }
        }
    }
    for(int i = 1; i<=N; i++){
        par[i] = i;
    }
    for(int n = N; n>0; n--){
        for(int e : graph[n][0]){
            if(n < e){
                if(n != getrt(e)){
                    int rt = getrt(e);
                    par[rt] = n;
                    graph[n][2].push_back(rt);
                }
            }
        }
    }
    for(int i = 1; i<=N; i++){
        swap(graph[i][0], graph[i][2]);
    }
    dfs(1, 0);
    ETtm = 0;
    dfs(N, 1);
    anc[N][0][1] = N + 1;
    buildtbl(1, N);
    buildtbl(0, N);
    build(1, 8*N, 1);
    for(int q = 0; q<Q; q++){
        int n = binlift(++E[q], 1, ++R[q]);
        int m = binlift(++S[q], 0, ++L[q]);
//        cout << n << " " << m << endl;
        qu[lft[n][1]].push_back({m, q});
        qu[rht[n][1]].push_back({m, q});
    }
    for(int i = 1; i<=2*N; i++){
        int n = ET[i];
//        cout << " " << n << endl;
        if(n > 0){
            for(Query q: qu[i]){
                ans[q.id] = sum(lft[q.n][0], rht[q.n][0], 1);
//                cout << ans[q.id] << endl;
            }
        }
        upd(lft[abs(n)][0], 1);
        if(n < 0){
            for(Query q: qu[i]){
                if(ans[q.id] < sum(lft[q.n][0], rht[q.n][0], 1)){
                    ans[q.id] = 1;
                }
                else{
                    ans[q.id] = 0;
                }
            }
        }
    }
    return ans;
}

int main(){

}

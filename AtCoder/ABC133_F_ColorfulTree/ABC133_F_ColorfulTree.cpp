#include <bits/stdc++.h>

using namespace std;

struct query{
    int c, x, u, v, id;
    bool operator < (query q) const{
        return c < q.c;
    }
};

struct edge{
    int e, c, v;
};

int N, Q, B = 315;
vector<edge> graph[100005];
vector<edge> typ[100005];
vector<query> qu;
int dist[100005], clr[100005], wt[100005], dep[100005];
int clrv[100005], clrc[100005];
int par[100005][18];
int ans[100005];

void dfs1(int n){
    for(auto e : graph[n]){
        if(e.e != par[n][0]){
            par[e.e][0] = n;
            dist[e.e] = dist[n] + e.v;
            clr[e.e] = e.c;
            wt[e.e] = e.v;
            dep[e.e] = dep[n] + 1;
            typ[e.c].push_back(e);
            dfs1(e.e);
        }
    }
}

void dfs2(int n, int c){
    if(clr[n] == c){
        clrv[n] += wt[n];
        clrc[n]++;
    }
    for(auto e : graph[n]){
        if(e.e != par[n][0]){
            clrv[e.e] = clrv[n];
            clrc[e.e] = clrc[n];
            dfs2(e.e, c);
        }
    }
}

void build(){
    for(int d = 1; d<17; d++){
        for(int n = 1; n<=N; n++){
            par[n][d] = par[par[n][d-1]][d-1];
        }
    }
}

int lca(int u, int v){
    if(dep[u] < dep[v]){
        swap(u, v);
    }
    for(int d = 16; d>=0; d--){
        if(dep[par[u][d]] >= dep[v]){
            u = par[u][d];
        }
    }
    if(u == v){
        return u;
    }
    for(int d = 16; d>=0; d--){
        if(par[u][d] != par[v][d]){
            u = par[u][d];
            v = par[v][d];
        }
    }
    return par[u][0];
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> Q;
    for(int i = 1; i<N; i++){
        int a, b, c, v;
        cin >> a >> b >> c >> v;
        graph[a].push_back({b, c, v});
        graph[b].push_back({a, c, v});
    }
    dep[1] = 1;
    dfs1(1);
    build();
    for(int q = 1; q<=Q; q++){
        int c, x, u, v;
        cin >> c >> x >> u >> v;
        qu.push_back({c, x, u, v, q});
    }
    sort(qu.begin(), qu.end());
    int crntc = 0;
    for(auto q : qu){
        int top = lca(q.u, q.v);
        ans[q.id] = dist[q.u] + dist[q.v] - 2*dist[top];
        if(typ[q.c].size() <= B){
            for(auto e : typ[q.c]){
                if(dep[e.e] > dep[top] && (lca(e.e, q.u) == e.e || lca(e.e, q.v) == e.e)){
                    ans[q.id] -= wt[e.e];
                    ans[q.id] += q.x;
                }
            }
            continue;
        }
        if(q.c != crntc){
            crntc = q.c;
            dfs2(1, q.c);
        }
        ans[q.id] -= clrv[q.u] + clrv[q.v] - 2*clrv[top];
        ans[q.id] += q.x*(clrc[q.u] + clrc[q.v] - 2*clrc[top]);
    }
    for(int q = 1; q<=Q; q++){
        cout << ans[q] << "\n";
    }
}

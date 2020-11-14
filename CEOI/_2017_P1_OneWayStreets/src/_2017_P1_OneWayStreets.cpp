#include <bits/stdc++.h>

using namespace std;

int N, M, Q;
vector<pair<int, int>> graph[100005], cgraph[100005];
bool bri[100005];
int low[100005], dfn[100005], t;
int par[100005]; //edge
int typ[100005];
int tbl[100005][20];
int dep[100005];
int ans[100005];
pair<int, int> dp[100005];

int sign(int n){
    if(n < 0){
        return -1;
    }
    else if(n > 0){
        return 1;
    }
    else{
        return 0;
    }
}

void dfs1(int n){
    low[n] = dfn[n] = ++t;
    for(auto e : graph[n]){
        if(!dfn[e.first]){
            par[e.first] = abs(e.second);
            dfs1(e.first);
            low[n] = min(low[n], low[e.first]);
        }
        else if(abs(e.second) != par[n]){
            low[n] = min(low[n], dfn[e.first]);
        }
    }
//    cout << "   " << n << " " << low[n] << " " << dfn[n] << endl;
    if(low[n] == dfn[n]){
        bri[par[n]] = 1;
    }
}

void dfs2(int n, int c){
//    cout << " " << n << " " << c << endl;
    typ[n] = c;
    for(auto e : graph[n]){
        if(!typ[e.first] && !bri[abs(e.second)]){
            dfs2(e.first, c);
        }
    }
}

void dfs3(int n){
    //cout << n << endl;
    for(auto e : cgraph[n]){
        if(e.first != tbl[n][0]){
            tbl[e.first][0] = n;
            par[e.first] = -e.second;
            dep[e.first] = dep[n] + 1;
            dfs3(e.first);
        }
    }
}

void build(){
    for(int d = 1; d<20; d++){
        for(int n = 1; n<=N; n++){
            tbl[n][d] = tbl[tbl[n][d-1]][d-1];
        }
    }
}

void upd(int u, int v){
    //cout << "upd: " << u << " " << v << endl;
    dp[u].first++, dp[v].second++;
    if(dep[u] < dep[v]){
        swap(u, v);
    }
    for(int k = 19; k>=0; k--){
        if(dep[tbl[u][k]] >= dep[v]){
            u = tbl[u][k];
        }
    }
    //cout << u << " " << v << endl;
    if(u == v){
        dp[u].first--, dp[u].second--;
        return;
    }
    for(int k = 19; k>=0; k--){
        if(tbl[u][k] != tbl[v][k]){
            u = tbl[u][k];
            v = tbl[v][k];
        }
    }
    int p = tbl[u][0];
    //cout << " " << u << " " << v << " " << p << endl;
    dp[p].first--, dp[p].second--;
}

pair<int, int> dfs4(int n){
    for(auto e : cgraph[n]){
        if(abs(e.second) != abs(par[n])){
            auto p = dfs4(e.first);
            dp[n].first += p.first, dp[n].second += p.second;
        }
    }
    if(dp[n].first){
        ans[abs(par[n])] = sign(par[n]);
    }
    else if(dp[n].second){
        ans[abs(par[n])] = -sign(par[n]);
    }
//    cout << n << " " << dp[n].first << " " << dp[n].second << endl;
    return dp[n];
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> M;
    for(int i = 1; i<=M; i++){
        int a, b;
        cin >> a >> b;
        graph[a].push_back({b, i});
        graph[b].push_back({a, -i});
    }
    for(int n = 1; n<=N; n++){
        if(!dfn[n]){
            dfs1(n);
        }
    }
    //cout << "here" << endl;
    int c = 0;
    for(int n = 1; n<=N; n++){
        if(!typ[n]){
            dfs2(n, ++c);
        }
    }
    //cout << "here" << endl;
    for(int n = 1; n<=N; n++){
        for(auto e : graph[n]){
            if(bri[abs(e.second)]){
                cgraph[typ[n]].push_back({typ[e.first], e.second});
            }
        }
    }
    //cout << "here" << endl;
    N = c;
    fill(par+1, par+1+N, 0);
    for(int n = 1; n<=N; n++){
        if(!par[n]){
            dep[n] = 1;
            dfs3(n);
        }
    }
    //cout << "here" << endl;
    build();
    //cout << "here" << endl;
    cin >> Q;
    while(Q--){
        int a, b;
        cin >> a >> b;
        upd(typ[a], typ[b]);
    }
    //cout << "here" << endl;
    for(int n = 1; n<=N; n++){
        if(!par[n]){
            dfs4(n);
        }
    }
    //cout << "here" << endl;
    for(int e = 1; e<=M; e++){
        if(!ans[e]){
            cout << "B";
        }
        else if(ans[e] == 1){
            cout << "R";
        }
        else{
            cout << "L";
        }
    }
    cout << endl;
}

/*
6 5
1 2
1 3
3 4
3 5
3 6
3
4 2
6 5
6 1
*/

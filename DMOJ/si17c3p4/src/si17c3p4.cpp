#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<pair<int, int>> graph[20005];
bool tree[100005];
int par[100005];
bool vis[100005];
int clr[100005];
int dep[100005];
vector<int> sz;

void dfs(int n){
    vis[n] = 1;
    for(auto p : graph[n]){
        if(!vis[n]){
            par[p.first] = n;
            tree[p.second] = 1;
            dfs(p.first);

        }
    }
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for(int i = 1; i<=M; i++){
        int a, b;
        cin >> a >> b;
        graph[a].push_back({b, i});
        graph[b].push_back({a, i});
    }
    dfs(1);
    for(int i = 1; i<=M; i++){

    }
}

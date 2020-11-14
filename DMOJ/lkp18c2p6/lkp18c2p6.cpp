#include <bits/stdc++.h>

using namespace std;

struct Node{
    int l, r, v;
};

int N, K, Q;
vector<pair<int, int>> graph[100005];
int par[100005], dep[100005], top[100005], nid[100005], hvy[100005], sz[100005], wt[100005];
int eid[100005], ewt[100005];
int cnt = 0;

void dfs(int n){
    sz[n] = 1;
    for(auto e : graph[n]){
        if(e.first != par[n]){
            dep[e.first] = dep[n] + 1;
            par[e.first] = n;
            dfs(e.first);
            sz[n] += sz[e.first];
            hvy[n] = sz[hvy[n]] > sz[e.first] ? hvy[n] : e.first;
        }
    }
}

void hld(int n, int t){
    top[n] = t;
    id[n] = ++cnt;
    if(hvy[n]){
        hld(hvy[n], t);
    }
    for(auto e : graph[n]){
        if(e.first != par[n] && e.first != hvy[n]){
            hld(e.first, e.first);
        }
        if(e.first != par[n]){
            wt[id[e.first]] = e.second;
        }
    }
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> K >> Q;

}

#include <bits/stdc++.h>

using namespace std;

int N;
vector<pair<int, int>> graph[100005];
int sz[100005], par[100005];
bool vis[100005];
int dep[100005], dis[100005];
int tot[200005], cnt[200005], offset = 100000;
long long ans = 0;

void dfs1(int n){
    sz[n] = 1;
    for(auto e : graph[n]){
        if(!vis[e.first] && e.first != par[n]){
            par[e.first] = n;
            dfs1(e.first);
            sz[n] += sz[e.first];
        }
    }
}

int dfs2(int n, int mn, int mx, int c = 0){
    int ret = dep[n];
    ans += tot[offset-dis[n]];
    if(dis[n] < mn || dis[n] > mx){
        ans -= cnt[offset-dis[n]];
    }
    if(!dis[n] && c >= 1){
        ans++;
    }
    c += !dis[n];
    for(auto e : graph[n]){
        if(!vis[e.first] && e.first != par[n]){
            par[e.first] = n;
            dis[e.first] = dis[n] + e.second;
            dep[e.first] = dep[n] + 1;
            ret = max(ret, dfs2(e.first, min(mn, dis[n]), max(mx, dis[n]), c));
        }
    }
    return ret;
}

void dfs3(int n, int mn, int mx){
    tot[offset+dis[n]]++;
    if(dis[n] < mn || dis[n] > mx){
        cnt[offset+dis[n]]++;
    }
    for(auto e : graph[n]){
        if(!vis[e.first] && e.first != par[n]){
            dfs3(e.first, min(dis[n], mn), max(dis[n], mx));
        }
    }
}

void solve(int n){
    par[n] = 0;
    dfs1(n);
    int s = sz[n];
    while(true){
        int hvy = 0;
        for(auto e : graph[n]){
            if(e.first != par[n] && !vis[e.first]){
                hvy = sz[hvy] > sz[e.first] ? hvy : e.first;
            }
        }
        if(sz[hvy]*2 <= s){
            break;
        }
        n = hvy;
    }
    tot[offset] = cnt[offset] = 0;
    vis[n] = 1;
    int len = 0;
    for(auto e : graph[n]){
        if(!vis[e.first]){
            par[e.first] = n;
            dep[e.first] = 1;
            dis[e.first] = e.second;
            len = max(dfs2(e.first, 0, 0), len);
            dfs3(e.first, 0, 0);
        }
    }
    for(int k = offset-s; k<=offset+s; k++){
        tot[k] = cnt[k] = 0;
    }
    for(auto e : graph[n]){
        if(!vis[e.first]){
            solve(e.first);
        }
    }
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    if(fopen("yinyang.in", "r")){
        freopen("yinyang.in", "r", stdin);
        freopen("yinyang.out", "w", stdout);
    }
    cin >> N;
    for(int i = 1; i<N; i++){
        int a, b, c;
        cin >> a >> b >> c;
        c *= 2, c--;
        graph[a].push_back({b, c});
        graph[b].push_back({a, c});
    }
    solve(1);
    cout << ans << endl;
}

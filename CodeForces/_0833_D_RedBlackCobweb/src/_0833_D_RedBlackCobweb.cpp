#include <bits/stdc++.h>

using namespace std;

struct Edge{
    int e;
    long long len;
    int typ;
};

int N, MOD = 1000000007;
vector<Edge> graph[100005];
int sz[100005], par[100005], hvy[100005];
bool vis[100005];
long long val[400005], cnt[400005];
long long ans = 1;
int clrdis[100005];
long long dis[100005];
vector<int> v;

long long mult(long long a, long long b){
    return ((a%MOD)*(b%MOD))%MOD;
}

long long qikpow(long long b, long long e){
    if(!e){
        return 1;
    }
    long long res = qikpow(b, e>>1);
    res = mult(res, res);
    if(e&1){
        res = mult(res, b);
    }
    return res;
}

void dfs1(int n){
    sz[n] = 1;
    hvy[n] = 0;
    for(auto e : graph[n]){
        if(e.e != par[n] && !vis[e.e]){
            par[e.e] = n;
            dfs1(e.e);
            sz[n] += sz[e.e];
            hvy[n] = (sz[e.e] > sz[hvy[n]] ? e.e : hvy[n]);
        }
    }
}

int getcent(int n){
    int crnt = n;
    while(true){
        if(2*sz[hvy[crnt]] > sz[n]){
            crnt = hvy[crnt];
        }
        else{
            break;
        }
    }
    return crnt;
}

void dfs2(int n){
    v.push_back(n);
    for(auto e : graph[n]){
        if(!vis[e.e] && e.e != par[n]){
            par[e.e] = n;
            dis[e.e] = mult(dis[n], e.len);
            clrdis[e.e] = clrdis[n] + e.typ;
            dfs2(e.e);
        }
    }
}

void solve(int n){
    dfs1(n);
    n = getcent(n);
    vis[n] = 1;
    cout << "centroid: " << n << endl;
    int mini = 200000, maxi = 200000;
    cnt[200000] = 1;
    for(auto sub : graph[n]){
        if(!vis[sub.e]){
            clrdis[sub.e] = sub.typ;
            dis[sub.e] = sub.len;
            par[sub.e] = n;
            dfs2(sub.e);
            for(int e : v){
                int l = -2-clrdis[e]+200000, r = 2-clrdis[e]+200000;
                while(l <= r){
                    ans = mult(ans, mult(val[l], qikpow(dis[e], cnt[l])));
                    l++;
                }
            }
            for(int e : v){
                int idx = clrdis[e] + 200000;
                cnt[idx]++;
                mini = min(idx, mini);
                maxi = max(idx, maxi);
                val[idx] = mult(val[idx], dis[e]);
            }
            v.clear();
        }
    }
    for(int i = mini; i<=maxi; i++){
        cnt[i] = 0;
        val[i] = 1;
    }
    for(auto e : graph[n]){
        if(!vis[e.e]){
            solve(e.e);
        }
    }
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for(int i =1; i<N; i++){
        int a, b, w, t;
        cin >> a >> b >> w >> t;
        t = 2*t-1;
        graph[a].push_back({b, w, t});
        graph[b].push_back({a, w, t});
    }
    fill(val, val+400000, 1);
    solve(1);
    cout << ans << endl;
}

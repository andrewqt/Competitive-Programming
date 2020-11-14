#pragma GCC optimize("Ofast","unroll-loops","omit-frame-pointer","inline")
#pragma GCC option("arch=native","tune=native","no-zero-upper")
#pragma GCC target("avx2")
// Problem : APIO '13 P2 - Toll
// Contest : DMOJ
// URL : https://dmoj.ca/problem/apio13p2
// Memory Limit : 32 MB
// Time Limit : 1200 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

struct edge{
	int u, v, w;
	bool operator < (const edge e) const{
		return w < e.w;
	}
};

int N, M, K;
edge lst[300005], sp[25], good[100005];
bool st[100005], vis[100005], used[25];
int dsu[100005], par[100005], dep[100005], val[100005], who[100005], wt[100005];
vector<pair<int, int>> graph[100005];
vector<edge> cedge, splst;
long long cwt[25], dp[25];

inline int getrt(int n){
	return dsu[n] = (dsu[n] == n ? n : getrt(dsu[n]));
}

inline void dfs1(int n){
	for(auto e : graph[n]){
		if(e.first != par[n]){
			par[e.first] = n;
			dep[e.first] = dep[n] + 1;
			val[e.first] = e.second;
			dfs1(e.first);
		}
	}
}

inline void dfs2(int n){
	vis[n] = 1;
	cwt[who[n]] += wt[n];
	for(auto e : graph[n]){
		if(e.first != par[n]){
			par[e.first] = n;
			who[e.first] = who[n];
			dfs2(e.first);
		}
	}
}

inline void dfs3(int n){
	dp[n] = cwt[n];
	for(auto e : graph[n]){
		if(e.first != par[n]){
			par[e.first] = n;
			dep[e.first] = dep[n] + 1;
			val[e.first] = e.second;
			dfs3(e.first);
			dp[n] += dp[e.first];
		}
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M >> K;
	for(int i = 1; i<=M; i++){
		int a, b, c;
		cin >> a >> b >> c;
		lst[i] = {a, b, c};
	}
	for(int i = 0; i<K; i++){
		int a, b;
		cin >> a >> b;
		sp[i] = {a, b, -1};
	}
	for(int i = 1; i<=N; i++){
		cin >> wt[i];
		dsu[i] = i;
	}
	sort(lst+1, lst+1+M);
	int idx = 0;
	for(int i = 1; i<=M; i++){
		if(getrt(lst[i].u) != getrt(lst[i].v)){
			dsu[getrt(lst[i].u)] = getrt(lst[i].v);
			good[++idx] = lst[i];
		}
	}
	for(int k = 0; k<K; k++){
		for(int i = 1; i<=N; i++){
			dsu[i] = i;
			par[i] = 0;
			graph[i].clear();
		}
		for(int i = 1; i<N; i++){
			if(!st[i]){
				graph[good[i].u].emplace_back(good[i].v, good[i].w);
				graph[good[i].v].emplace_back(good[i].u, good[i].w);
			}
		}
		for(auto e : splst){
			graph[e.u].emplace_back(e.v, -1);
			graph[e.v].emplace_back(e.u, -1);
			dsu[getrt(e.u)] = getrt(e.v);
		}
		if(getrt(sp[k].u) == getrt(sp[k].v)){
			continue;
		}
		dep[1] = 1;
		dfs1(1);
		int x = sp[k].u, y = sp[k].v, value = 0;
		while(x != y){
			if(dep[x] < dep[y]){
				swap(x, y);
			}
			value = max(value, val[x]);
			x = par[x];
		}
		for(int i = 1; i<N; i++){
			if(good[i].w == value){
				st[i] = 1;
			}
		}
		splst.emplace_back(sp[k]);
	}
	for(int i = 1; i<=N; i++){
		graph[i].clear();
		par[i] = 0;
	}
	for(int i = 1; i<N; i++){
		if(!st[i]){
			graph[good[i].u].emplace_back(good[i].v, good[i].w);
			graph[good[i].v].emplace_back(good[i].u, good[i].w);
		}
		else{
			cedge.emplace_back(good[i]);
		}
	}
	int C = 0;
	for(int i = 1; i<=N; i++){
		if(!vis[i]){
			who[i] = ++C;
			dfs2(i);
		}
	}
	N = C;
	K = splst.size();
	sort(cedge.begin(), cedge.end());
	assert(who[1] == 1);
	for(auto &e : splst){
		e.v = who[e.v];
		e.u = who[e.u];
		assert(e.v != e.u);
	}
	for(auto &e : cedge){
		e.v = who[e.v];
		e.u = who[e.u];
		assert(e.v != e.u);
	}
	long long ans = 0;
	for(int mask = 1; mask<1<<K; mask++){
		for(int i = 1; i<=N; i++){
			dsu[i] = i;
			graph[i].clear();
			used[i-1] = 0;
		}
		for(int k = 0; k<K; k++){
			if(mask>>k&1){
				dsu[getrt(splst[k].u)] = getrt(splst[k].v);
				graph[splst[k].u].emplace_back(splst[k].v, -1);
				graph[splst[k].v].emplace_back(splst[k].u, -1);				
			}
		}
		for(int i = 0; i<cedge.size(); i++){
			edge e = cedge[i];
			if(getrt(e.u) != getrt(e.v)){
				dsu[getrt(e.u)] = getrt(e.v);
				graph[e.u].emplace_back(e.v, e.w);
				graph[e.v].emplace_back(e.u, e.w);
				used[i] = 1;
			}
		}
		dfs3(1);
		for(int i = 0; i<cedge.size(); i++){
			if(!used[i]){
				int x = cedge[i].u, y = cedge[i].v;
				while(x != y){
					if(dep[x] < dep[y]){
						swap(x, y);
					}
					if(val[x] == -1){
						val[x] = cedge[i].w;
					}
					x = par[x];
				}
			}
		}
		long long tot = 0;
		for(int k = 0; k<K; k++){
			if(mask>>k&1){
				if(dep[splst[k].u] < dep[splst[k].v]){
					swap(splst[k].u, splst[k].v);
				}
				//assert(val[splst[k].u] != -1);
				tot += dp[splst[k].u] * val[splst[k].u];
			}
		}
		ans = max(ans, tot);
	}
	cout << ans << "\n";
}
#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#pragma GCC optimize ("no-stack-protector")

#include <bits/stdc++.h>

using namespace std;

int N, K;
vector<pair<int, int>> graph[200005];
bool vis[200005];
long long dep[200005];
int par[200005];
int sz[200005];
int hvy[200005];
long long ans[200005];
int dif[200005];
long long dist[200005];
vector<int> vec, sub;
long long fin = 0;

void dfs1(int n){
	sz[n] = 1;
	dif[n] = hvy[n] = 0;
	for(auto e : graph[n]){
		if(!vis[e.first] && e.first != par[n]){
			par[e.first] = n;
			dfs1(e.first);
			sz[n] += sz[e.first];
			hvy[n] = (sz[hvy[n]] > sz[e.first] ? hvy[n] : e.first);
		}
	}
}

void dfs2(int n){
	sub.emplace_back(n);
	for(auto e : graph[n]){
		if(!vis[e.first] && e.first != par[n]){
			par[e.first] = n;
			dist[e.first] = dist[n] + e.second;
			dfs2(e.first);
		}
	}
}

void dfs3(int n){
	for(auto e : graph[n]){
		if(!vis[e.first] && e.first != par[n]){
			dfs3(e.first);
			dif[n] += dif[e.first];
		}
	}
}

void solve(int n){
	dfs1(n);
	int S = sz[n];
	while(2*sz[hvy[n]] > S){
		n = hvy[n];
	}
	//cout << "cent: " << n << "\n";
	vis[n] = 1;
	vec.push_back(n);
	par[n] = 0;
	dist[n] = 0;
	map<long long, int> tot;
	tot[0] = 1;
	for(auto e : graph[n]){
		if(!vis[e.first]){
			par[e.first] = n;
			dist[e.first] = e.second;
			dfs2(e.first);
			map<long long, int> mp;
			for(int k : sub){
				mp[dist[k]]++;
				tot[dist[k]]++;
			}			
			while(sub.size()){
				int k = sub.back();
				sub.pop_back();
				dif[k] = -mp[K-dist[k]];
				fin -= mp[K-dist[k]];
				vec.push_back(k);
			}		
		}
	}
	for(int k : vec){
		fin += tot[K-dist[k]];
		dif[k] += tot[K-dist[k]];
	}
	/*
	cout << "bef" << "\n";
	for(int k= 1; k<=N; k++){
		cout << dif[k] << "\n";
	}
	*/
	dfs3(n);
	/*
	cout << "aft" << "\n";
	for(int k = 1; k<=N; k++){
		cout << dif[k] << "\n";
	}
	*/
	dif[n] /= 2;
	for(int k : vec){
		ans[k] += dif[k];
	}
	vec.clear();
	for(auto e : graph[n]){
		if(!vis[e.first]){
			solve(e.first);
		}
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> K;
	for(int i = 1; i<N; i++){
		int a, b, c;
		cin >> a >> b >> c;
		graph[a].emplace_back(b, c);
		graph[b].emplace_back(a, c);
	}
	solve(1);
	fin /= 2;
	if(!fin){
		for(int i = 1; i<=N; i++){
			cout << "0 / 1" << "\n";
		}
		return 0;
	}
	for(int i =1 ; i<=N; i++){
		long long G = __gcd(fin, ans[i]);
		cout << ans[i]/G << " / " << fin/G << "\n";
	}	
}
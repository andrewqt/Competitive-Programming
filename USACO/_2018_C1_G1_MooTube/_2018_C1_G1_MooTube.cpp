
// Problem : USACO 2018 January Contest Gold P1 - MooTube
// Contest : DMOJ
// URL : https://dmoj.ca/problem/usaco18jangold1
// Memory Limit : 512.000000 MB 
// Time Limit : 2000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int N, Q;
vector<pair<int, int>> vec;
int u[100005], v[100005];
int ans[100005];
int par[100005];
int nd[100005];
int sz[100005];

int getrt(int n){
	return par[n] = (par[n] == n ? n : getrt(par[n]));
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> Q;
	for(int i = 1; i<N; i++){
		int w;
		cin >> u[i] >> v[i] >> w;
		vec.push_back({w, i});
	}
	for(int i = 1; i<=N; i++){
		par[i] = i;
		sz[i] = 1;
	}
	for(int i = 1; i<=Q; i++){
		int k;
		cin >> k >> nd[i];
		vec.push_back({k, -i});
	}
	sort(vec.begin(), vec.end(), greater<pair<int, int>>());
	for(auto p : vec){
		int idx = abs(p.second);
		if(p.second < 0){
			ans[idx] = sz[getrt(nd[idx])];
		}
		else{
			sz[getrt(v[idx])] += sz[getrt(u[idx])];
			par[getrt(u[idx])] = getrt(v[idx]);
		}
	}
	for(int q = 1; q<=Q; q++){
		cout << ans[q]-1 << "\n";
	}
}
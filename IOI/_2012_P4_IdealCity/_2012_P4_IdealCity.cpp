#include <bits/stdc++.h>

using namespace std;

int N, C;
vector<int> graph[100005];
int sz[100005];
set<pair<int, int>> st;
int par[100005];
vector<pair<int, int>> coords;
int who[100005];

int getrt(int n){
	return par[n] = (par[n] == n ? n : getrt(par[n]));
}

int getidx(pair<int, int> p){
	return lower_bound(coords.begin(), coords.end(), p) - coords.begin();
}

void dfs(int n, int p){
	for(int e : graph[n]){
		if(e != p){
			dfs(e, n);
			sz[n] += sz[e];
		}
	}
}

void build(){
	for(int i = 0; i<N; i++){
		auto p = coords[i];
		par[i] = i;
		if(st.count({p.first-1, p.second})){
			par[getrt(getidx({p.first-1, p.second}))] = i;
		}
		if(st.count({p.first+1, p.second})){
			par[getrt(getidx({p.first-1, p.second}))] = i;
		}
		st.insert(p);
	}
	C = 0;
	for(int i = 0; i<N; i++){
		if(par[i] == i){
			who[i] = ++C;
			sz[C] = 0;		
		}
	}
	for(int i = 0; i<N; i++){
		sz[who[getrt(i)]]++;
	}
	for(int i = 0; i<N; i++){
		auto p = coords[i];
		int n = who[getrt(i)];
		if(st.count({p.first, p.second-1})){
			auto a = who[getrt(getidx({p.first, p.second-1}))];
			graph[a].push_back(n);
		}
		if(st.count({p.first, p.second+1})){
			auto a = who[getrt(getidx({p.first, p.second+1}))];
			graph[a].push_back(n);
		}
	}
	for(int i = 1; i<=C; i++){
		sort(graph[i].begin(), graph[i].end());
		graph[i].erase(unique(graph[i].begin(), graph[i].end()), graph[i].end());
	}
}

long long calc(int *X, int *Y){
	for(int i = 0; i<N; i++){
		coords.push_back({X[i], Y[i]});
	}
	sort(coords.begin(), coords.end());
	build();
	dfs(1, 0);
	long long ans = 0;
	for(int i = 1; i<=C; i++){
		ans += 1LL*sz[i]*(N-sz[i]);
		ans %= 1000000000;
		graph[i].clear();
	}
	coords.clear();
	st.clear();
	fill(who, who+N, -1);
	fill(par, par+N, -1);
	return ans;
}

int DistanceSum(int NN, int *X, int *Y){
	N = NN;
	long long ret = calc(X, Y);
	ret += calc(Y, X);
	return ret%1000000000;
}
/*
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int NNN;
	cin >> NNN;
	int X[NNN], Y[NNN];
	for(int i = 0; i<NNN; i++){
		cin >> X[i] >> Y[i];
	}	
	cout << DistanceSum(NNN, X, Y) << endl;
}
*/
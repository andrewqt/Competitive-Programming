
// Problem : Path Finder
// Contest : DMOJ
// URL : https://dmoj.ca/problem/pathfind
// Memory Limit : 512 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

map<pair<int, int>, pair<int, int>> dsu;
set<pair<int, int>> st;

pair<int, int> getrt(pair<int, int> p){
	return dsu[p] = (dsu[p] == p ? p : getrt(dsu[p]));
}

void unite(pair<int, int> p, pair<int, int> q){
	if(getrt(p) != getrt(q)){
		dsu[p] = q;
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int N, M, K;
	cin >> N >> M >> K;
	dsu[{0, M+1}] = {0, M+1};
	dsu[{N+1, 0}] = {N+1, 0};
	while(K--){
		int n, m;
		cin >> n >> m;
		dsu[{n, m}] = {n, m};
		if(n == 1 || m == M){
			cout << "hi\n";
			unite({n, m}, {0, M+1});
		}
		if(n == N || m == 1){
			cout << "hey\n";
			unite({n, m}, {N+1, 0});
		}
		for(int i = n-1; i<=n+1; i++){
			for(int j = m-1; j<=m+1; j++){
				cout << i << " " << j << "\n";
				if(st.count({i, j})){
					unite({n, m}, {i, j});
				}
			}
		}
		st.insert({n, m});
	}
	//cout << getrt({0, M+1}).first << " " << getrt({N+1, 0}).first << "\n";
	if(getrt({0, M+1}) != getrt({N+1, 0})){
		cout << "YES\n";
	}
	else{
		cout << "NO\n";
	}
}	
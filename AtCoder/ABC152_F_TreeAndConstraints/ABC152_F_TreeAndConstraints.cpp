
// Problem : F - Tree and Constraints
// Contest : AtCoder Beginner Contest 152
// URL : https://atcoder.jp/contests/abc152/tasks/abc152_f
// Memory Limit : 1024.000000 MB 
// Time Limit : 4000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int N, M;
int u[55], v[55];
vector<int> graph[55];
int msk[55];
long long dp[55][1<<20];
int lft[55], rht[55], t;
int dep[55], par[55];

void dfs(int n){
	lft[n] = ++t;
	for(auto e : graph[n]){
		if(e != par[n]){
			par[e] = n;
			dep[e] += dep[n] + 1;
			dfs(e);
		}
	}
	rht[n] = ++t;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 1; i<N; i++){
		cin >> u[i] >> v[i];
		graph[u[i]].push_back(v[i]);
		graph[v[i]].push_back(u[i]);
	}
	dfs(1);
	cin >> M;
	for(int j = 0; j<M; j++){
		int a, b;
		cin >> a >> b;
		for(int i = 1; i<N; i++){
			int c = 0;
			if(par[u[i]] == v[i]){
				swap(u[i], v[i]);
			}
			c += (lft[v[i]] <= lft[a] && rht[a] <= rht[v[i]]);
			c += (lft[v[i]] <= lft[b] && rht[b] <= rht[v[i]]);
			if(c == 1){
				msk[i] |= (1<<j);
			}
		}
	}
	dp[0][0] = 1;
	for(int i = 0; i<N-1; i++){
		for(int m = 0; m<1<<M; m++){
			dp[i+1][m] += dp[i][m];
			dp[i+1][m|msk[i+1]] += dp[i][m];
		}
	}
	cout << dp[N-1][(1<<M)-1] << "\n";
}

// Problem : D. Berland Federalization
// Contest : Testing Round #10
// URL : https://codeforces.com/contest/440/problem/D
// Memory Limit : 256.000000 MB 
// Time Limit : 1000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int N, K;
vector<int> graph[405];
int dp[405][405];
int sz[405];
int par[405];
vector<int> edge[405][405];
int temp[405];

void dfs(int n){
	sz[n] = 1;
	for(int k = 1; k<=K; k++){
		dp[n][k] = N;
	}
	dp[n][k] = 0;
	for(int e : graph[n]){
		if(e != par[n]){
			par[e] = n;
			dfs(e);
			
		}
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> K;
	for(int i = 1; i<N; i++){
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
}
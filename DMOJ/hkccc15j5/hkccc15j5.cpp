#include <bits/stdc++.h>
 
using namespace std;
 
int N, M, K, B;
int cnt[3];
vector<int> graph[5005];
int ans[5005];
int clr[5005];
bool dp[5005][5005];
int par[5005][5005];
bool vis[5005];
int sz[2][5005];
bool used[5005];
int comp[5005];
int rt[5005];
 
void dfs1(int n){
	vis[n] = 1;
	comp[n] = K;
	sz[clr[n]][n]++;
	for(int e : graph[n]){
		if(!vis[e]){
			clr[e] = clr[n] ^ 1;
			dfs1(e);
			sz[0][n] += sz[0][e];
			sz[1][n] += sz[1][e];
		}
		else if(clr[e] == clr[n]){
			cout << -1;
			exit(0);
		}
	}
}
 
bool solve(int k, int n){
	if(k == K+1 && (n == B || n == N-B)){
		return 1;
	}
	else if(k == K+1){
		return 0;
	}
	if(dp[k][n]){
		return 0;
	}
	dp[k][n] = 1;
	if(solve(k+1, n+sz[0][rt[k]])){
		used[k] = 1;
		return 1;
	}
	if(solve(k+1, n+sz[1][rt[k]])){
		used[k] = 0;
		return 1;
	}
	return 0;
}
 
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	for(int i = 1; i<=M; i++){
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	dp[0][0] = 1;
	for(int i = 1; i<=N; i++){
		if(!vis[i]){
			K++;
			dfs1(i);
			rt[K] = i;
			for(int m = 0; m<=N/2; m++){
				if(m >= sz[0][i] && dp[K-1][m-sz[0][i]]){
					dp[K][m] = 1;
					par[K][m] = sz[0][i];
				}
				else if(m >= sz[1][i] && dp[K-1][m-sz[1][i]]){
					dp[K][m] = 1;
					par[K][m] = sz[1][i];
				}
			}
		}
	}
	for(int m = 0; m<=N/2; m++){
		if(dp[K][m]){
			B = m;
		}
	}
	memset(dp, 0, sizeof dp);
	assert(solve(1, 0));
	for(int i = 1; i<=N; i++){
		if(used[comp[i]]){
			if(clr[i] == 0){
				cout << 1;
			}
			else{
				cout << 2;
			}
		}
		else{
			if(clr[i] == 0){
				cout << 2;
			}
			else{
				cout << 1;
			}
		}
	}
}
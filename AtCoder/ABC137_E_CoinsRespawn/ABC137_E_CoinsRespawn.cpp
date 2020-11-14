
// Problem : E - Coins Respawn
// Contest : AtCoder - AtCoder Beginner Contest 137
// URL : https://atcoder.jp/contests/abc137/tasks/abc137_e
// Memory Limit : 1024 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N, M, K;
vector<pair<int, int>> graph[2505], rgraph[2505];
long long dist[2505];
long long temp[2505];
bool vis[2505];

void bellmanford(){
	for(int n = 1; n<=N; n++){
		if(!vis[n] || dist[n] == LLONG_MIN/2){
			continue;
		}
		for(auto e : graph[n]){
			if(dist[e.first] < dist[n] + e.second){
				dist[e.first] = dist[n] + e.second;
				vis[e.first] = 1;
			}
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
		c -= K;
		graph[a].push_back({b, c});
	}
	vis[1] = 1;
	fill(dist+2, dist+2+N, LLONG_MIN/2);
	for(int it = N; it; it--){
		bellmanford();
	}
	long long k = dist[N];
	if(!vis[N]){
		cout << -1 << "\n";
		return 0;
	}
	for(int it = N; it; it--){
		bellmanford();
	}
	if(k != dist[N]){
		cout << -1 << "\n";
		return 0;
	}
	cout << max(0LL, dist[N]) << "\n";
}
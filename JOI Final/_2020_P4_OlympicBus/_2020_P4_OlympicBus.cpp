#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> graph[205]; 
vector<int> rgraph[205];
int u[50005], v[50005], p[2][50005];
bool used[50005];
long long dist[2][205], cst[50005], rev[50005], rdist[2][205];
bool vis[50005];
long long ans = LLONG_MAX>>4;
queue<int> qu;

void dijkstra(int s, int t){
	for(int i = 0; i<=N; i++){
		dist[t][i] = ans;
		vis[i] = 0;
	}
	dist[t][s] = 0;
	for(int k = 0; k<N; k++){
		int n = 0;
		for(int i = 1; i<=N; i++){
			if(!vis[i] && dist[t][i] < dist[t][n]){
				n = i;
			}
		}
		vis[n] = 1;
		if(!n){
			break;
		}
		for(int e : graph[n]){
			if(u[e] == n && dist[t][v[e]] > dist[t][u[e]] + cst[e]){
				dist[t][v[e]] = dist[t][u[e]] + cst[e];
				p[t][v[e]] = e;
				qu.push(v[e]);
			}
		}
	}
}

void rdijkstra(int s, int t){
	for(int i = 1; i<=N; i++){
		rdist[t][i] = ans;
	}
	rdist[t][s] = 0;
	qu.push(s);
	while(qu.size()){
		int n = qu.front();
		qu.pop();
		for(int e : rgraph[n]){
			if(rdist[t][u[e]] > rdist[t][v[e]] + cst[e]){
				rdist[t][u[e]] = rdist[t][v[e]] + cst[e];
				//p[t][u[e]] = u[e];
				qu.push(u[e]);
			}
		}
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	for(int i = 1; i<=M; i++){
		cin >> u[i] >> v[i] >> cst[i] >> rev[i];
		graph[u[i]].push_back(i);
		rgraph[v[i]].push_back(i);
	}
	dijkstra(1, 0);
	dijkstra(N, 1);
	rdijkstra(1, 0);
	rdijkstra(N, 1);
	ans = dist[0][N] + dist[1][1];
	int crnt = N;
	while(p[0][crnt] && crnt != 1){
		used[p[0][crnt]] = 1;
		crnt = u[p[0][crnt]];
	}
	crnt = 1;
	while(p[1][crnt] && crnt != N){
		used[p[1][crnt]] = 1;
		crnt = u[p[1][crnt]];
	}
	for(int e = 1; e<=M; e++){
		if(!used[e]){
			ans = min(ans, dist[0][N] + dist[1][v[e]] + rdist[0][u[e]] + cst[e] + rev[e]);
			ans = min(ans, dist[1][1] + dist[0][v[e]] + rdist[1][u[e]] + cst[e] + rev[e]);
			ans = min(ans, dist[0][v[e]] + dist[1][v[e]] + rdist[0][u[e]] + rdist[1][u[e]] + rev[e] + 2*cst[e]);		
		}
	}
	for(int e = 1; e<=M; e++){
		if(used[e]){
			swap(u[e], v[e]);
			graph[u[e]].push_back(e);
			dijkstra(1, 0);
			dijkstra(N, 1);
			graph[u[e]].pop_back();
			swap(u[e], v[e]);
			ans = min(ans, dist[0][N] + dist[1][1] + rev[e]);
		}
	}
	if(ans >= LLONG_MAX>>4){
		ans = -1;
	}
	cout << ans;
}
#include <bits/stdc++.h>

using namespace std;

int N, M, S, T, U, V;
vector<pair<int, int>> graph[100005];
long long dist1[2][100005];
long long dist2[3][100005];
priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq1;
priority_queue<pair<long long, pair<int, int>>, vector<pair<long long, pair<int, int>>>, greater<pair<long long, pair<int, int>>>> pq2;

void dijkstra1(int n, int t){
	pq1.push({0, n});
	fill(dist1[t], dist1[t]+1+N, LLONG_MAX/2);
	dist1[t][n] = 0;
	while(pq1.size()){
		auto p = pq1.top();
		pq1.pop();
		int n = p.second;
		if(dist1[t][n] < p.first){
			continue;
		}
		for(auto e : graph[n]){
			if(dist1[t][e.first] > dist1[t][n] + e.second){
				dist1[t][e.first] = dist1[t][n] + e.second;
				pq1.push({dist1[t][e.first], e.first});
			}
		}
	}
}

void dijkstra2(int n){
	for(int t = 0; t<3; t++){
		fill(dist2[t], dist2[t]+1+N, LLONG_MAX/2);
	}
	dist2[0][n] = 0;
	pq2.push({0, {0, n}});
	while(pq2.size()){
		auto p  = pq2.top();
		pq2.pop();
		if(dist2[p.second.first][p.second.second] < p.first){
			continue;
		}
		int t = p.second.first, n = p.second.second;		
		//cout << t << " " << n << " " << dist2[t][n] << endl;
		if(t != 2){
			if(dist2[t+1][n] > dist2[t][n]){
				dist2[t+1][n] = dist2[t][n];
				pq2.push({dist2[t+1][n], {t+1, n}});
			}
		}
		for(auto e : graph[n]){
			if((t != 1 || dist1[0][n] + e.second + dist1[1][e.first] == dist1[0][T]) && dist2[t][e.first] > dist2[t][n] + e.second){
				dist2[t][e.first] = dist2[t][n] + (t == 1 ? 0 : e.second);
				pq2.push({dist2[t][e.first], {t, e.first}});
			}
		}
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	cin >> S >> T >> U >> V;
	for(int i = 1; i<=M; i++){
		int a, b, c;
		cin >> a >> b >> c;
		graph[a].push_back({b, c});
		graph[b].push_back({a, c});
	}
	dijkstra1(S, 0);
	dijkstra1(T, 1);
	dijkstra2(U);
	long long ans = dist2[2][V];
	dijkstra2(V);
	ans = min(dist2[2][U], ans);
	cout << ans << "\n";
}
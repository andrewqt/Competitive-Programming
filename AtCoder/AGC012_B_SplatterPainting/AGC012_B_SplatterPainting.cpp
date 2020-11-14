
// Problem : 
// 			B - Splatter Painting
// 			Editorial
// 		
// Contest : AtCoder - AtCoder Grand Contest 012
// URL : https://atcoder.jp/contests/agc012/tasks/agc012_b
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N, M, Q;
vector<int> graph[100005];
int vis[20][100005];
int nd[100005], d[100005], clr[100005];

void dfs(int n, int d, int c){
	if(vis[d][n]){
		return;
	}
	vis[d][n] = c;
	if(!d){
		return;
	}
	for(int e : graph[n]){
		dfs(e, d-1, c);
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	for(int i = 1; i<=M; i++){
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	cin >> Q;
	for(int i = 1; i<=Q; i++){
		cin >> nd[i] >> d[i] >> clr[i];
	}
	for(int q = Q; q; q--){
		dfs(nd[q], d[q], q);
	}
	for(int i = 1; i<=N; i++){
		int mx = 0;
		for(int k = 0; k<=10; k++){
			mx = max(vis[k][i], mx);
		}
		cout << clr[mx] << "\n";
	}
}
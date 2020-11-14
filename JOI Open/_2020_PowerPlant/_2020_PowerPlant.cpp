#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> graph[200005];
int dp[200005];
string s;
int ans = 0;

void dfs(int n, int p){
	int mx = 0;
	for(int e : graph[n]){
		if(e != p){
			dfs(e, n);
			dp[n] += dp[e];
			mx = max(mx, dp[e]);
		}
	}
	if(s[n-1] == '1'){
		dp[n] = max(1, dp[n] - 1);
		ans = max(ans, mx + 1);
	}
	ans = max(ans, dp[n]);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 1; i<N; i++){
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	cin >> s;
	dfs(1, 0);
	cout << max(ans, *max_element(dp+1, dp+1+N)) << "\n";
}
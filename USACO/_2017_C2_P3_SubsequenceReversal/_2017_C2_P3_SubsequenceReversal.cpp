
// Problem : Problem 3. Subsequence Reversal
// Contest : USACO 2017 January Contest, Platinum
// URL : http://www.usaco.org/index.php?page=viewproblem2&cpid=698
// Memory Limit : 256.000000 MB 
// Time Limit : 4000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int N;
bool vis[55][55][55][55];
int dp[55][55][55][55];
int arr[55];

int solve(int l, int r, int lv, int rv){
	if(l <= 0 && r > N){
		return 0;
	}
	if(vis[l][r][lv][rv]){
		return dp[l][r][lv][rv];
	}
	vis[l][r][lv][rv] = 1;
	if(l){
		dp[l][r][lv][rv] = max(solve(l-1, r, lv, rv), dp[l][r][lv][rv]);
	}
	if(r <= N) {
		dp[l][r][lv][rv] = max(solve(l, r+1, lv, rv), dp[l][r][lv][rv]);
	}
	if(l && arr[l] <= lv && l != r){
		dp[l][r][lv][rv] = max(solve(l-1, r, arr[l], rv) + 1, dp[l][r][lv][rv]);
	}
	if(r <= N && arr[r] >= rv && l != r){
		dp[l][r][lv][rv] = max(solve(l, r+1, lv, arr[r]) + 1, dp[l][r][lv][rv]);
	}
	if(l && r <= N && arr[r] <= lv){
		dp[l][r][lv][rv] = max(solve(l-1, r+1, arr[r], rv) + 1, dp[l][r][lv][rv]);
	}
	if(l && r <= N && arr[l] >= rv){
		dp[l][r][lv][rv] = max(solve(l-1, r+1, lv, arr[l]) + 1, dp[l][r][lv][rv]);		
	}
	if(l && r <= N && arr[l] >= rv && arr[r] <= lv && l != r){
		dp[l][r][lv][rv] = max(solve(l-1, r+1, arr[r], arr[l]) + 2, dp[l][r][lv][rv]);
	}
	return dp[l][r][lv][rv];
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("subrev.in", "r")){
		freopen("subrev.in", "r", stdin);
		freopen("subrev.out", "w", stdout);
	}
	cin >> N;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
	}
	int ans = 0;
	for(int i = 1; i<=N; i++){
		for(int v = 1; v<=50; v++){
			ans = max(ans, solve(i, i, v, v));
		}
	}
	//cout << solve(1, 1, 1, 1) << endl;
	cout << ans << endl;
}
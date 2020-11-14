
// Problem : Problem 3. Circular Barn
// Contest : USACO 2016 February Contest, Platinum
// URL : http://www.usaco.org/index.php?page=viewproblem2&cpid=626
// Memory Limit : 256.000000 MB 
// Time Limit : 4000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int N, K;
int arr[1005];
long long dp[10][1005];
long long cnt[1005], pre[1005];

void solve(int lidx, int ridx, int ldp, int rdp, int lvl){
	if(lidx > ridx){
		return;
	}
	int idx = lidx+ridx>>1;
	dp[lvl][idx] = LLONG_MAX;
	int opt = 0;
	for(int n = ldp; n<=min(idx, rdp); n++){
		dp[lvl][idx] = min(dp[lvl][idx], dp[lvl-1][n-1] + (cnt[idx]-cnt[n-1])*idx - pre[idx] + pre[n-1]);
		//cout << idx << " " << n << " " << dp[lvl-1][n-1] + (cnt[idx]-cnt[n-1])*idx - pre[idx] + pre[n-1] << endl;
		//cout << " " << dp[lvl-1][n-1] << " " << cnt[idx]-cnt[n-1] << " " << pre[idx]-pre[n-1] << endl;
		if(dp[lvl][idx] == dp[lvl-1][n-1] + (cnt[idx]-cnt[n-1])*idx - pre[idx] + pre[n-1]){
			opt = n;
		}
	}
	//cout << " " << lvl << " " << idx << " " << opt << " " << dp[lvl][idx] << endl;
	solve(lidx, idx-1, ldp, opt, lvl);
	solve(idx+1, ridx, opt, rdp, lvl);
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("cbarn.in", "r")){
		freopen("cbarn.in", "r", stdin);
		freopen("cbarn.out", "w", stdout);
	}
	cin >> N >> K;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
	}
	reverse(arr+1, arr+1+N);
	long long ans = LLONG_MAX;
	for(int n = 1; n<=N; n++){
		int t = arr[1];
		for(int i = 1; i<N; i++){
			arr[i] = arr[i+1];
		}
		arr[N] = t;
		for(int i = 1; i<=N; i++){
			pre[i] = 1LL*arr[i]*i;
			cnt[i] = arr[i];
			cnt[i] += cnt[i-1];
			pre[i] += pre[i-1];
		}
		solve(1, N, 1, 1, 1);
		for(int k = 2; k<=K; k++){
			solve(1, N, 1, N, k);
		}
		ans = min(dp[K][N], ans);
		//cout << "bling: " << ans << endl;
	}
	cout << ans << endl;
}
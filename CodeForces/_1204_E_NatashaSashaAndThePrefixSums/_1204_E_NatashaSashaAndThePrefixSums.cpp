
// Problem : E. Natasha, Sasha and the Prefix Sums
// Contest : Codeforces - Codeforces Round #581 (Div. 2)
// URL : https://codeforces.com/contest/1204/problem/E
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N, M;
long long dp1[2005][2005], dp2[2005][2005];
long long pas[4005][4005];
const long long MOD = 998244853;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	dp1[0][0] = dp2[0][0] = 1;
	for(int i = 1; i<=M; i++){
		for(int j = 0; j<=i; j++){
			dp1[i][j] = dp1[i-1][j];
			if(j){
				dp1[i][j] += dp1[i][j-1];
				dp1[i][j] %= MOD;
			}
		}
	}
	for(int i = 1; i<=M; i++){
		for(int j = 0; j<i; j++){
			dp2[i][j] = dp2[i-1][j];
			if(j){
				dp2[i][j] += dp2[i][j-1];
				dp2[i][j] %= MOD;
			}
		}
	}
	for(int r = 0; r<=N+M; r++){
		pas[r][0] = 1;
		for(int c = 1; c<=r; c++){
			pas[r][c] = (pas[r-1][c-1] + pas[r-1][c])%MOD;
		}
	}
	long long ans = 0;
	for(int l = 1; l<=N+M; l++){
		for(int p = (l%2 ? 1 : 2); p<=min(l, N); p+=2){
			long long c = pas[l-1][p-1] * dp1[(l-p)/2][(l-p)/2] % MOD;
			int a = N - p - (l-p)/2;
			int b = M - (l-p)/2;
			if(a >= 0 && b >= 0){
				c *= dp2[b][a];
				c %= MOD;
				cout << l << " " << p << " " << c << " " << dp1[(l-p)/2][(l-p)/2] << " " << dp2[b][a] << "\n";
				c *= p;
				ans += c;
				ans %= MOD;
			}
		}
	}
	cout << ans;
}
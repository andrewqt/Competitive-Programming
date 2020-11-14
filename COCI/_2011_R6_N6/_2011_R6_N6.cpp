
// Problem : COCI '11 Contest 6 #6 KOŠARE
// Contest : DMOJ
// URL : https://dmoj.ca/problem/coci11c6p5
// Memory Limit : 256 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N, M;
long long dp[1<<20];
long long pows[1000005];
const long long MOD = 1e9+7;

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	pows[0] = 1;
	for(int i = 1; i<=N; i++){
		int mask = 0;
		pows[i] = pows[i-1] * 2;
		pows[i] %= MOD;
		int K;
		cin >> K;
		while(K--){
			int n;
			cin >> n;
			n--;
			mask |= (1<<n);
		}
		dp[mask]++;
	}
	for(int b = 0; b<M; b++){
		for(int m = 1; m<1<<M; m++){
			if(m>>b&1){
				dp[m] += dp[m^(1<<b)];
				dp[m] %= MOD;
			}
		}
	}
	long long ans = 0;
	for(int m = 0; m<1<<M; m++){
		//cout << dp[m] << "\n";
		if((M-__builtin_popcount(m))%2 == 0){
			ans += pows[dp[m]];
		}
		else{
			ans -= pows[dp[m]];
		}
		ans %= MOD;
		if(ans < 0){
			ans += MOD;
		}
	}
	cout << ans << "\n";
}
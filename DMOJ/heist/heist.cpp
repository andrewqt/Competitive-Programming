
// Problem : The Heist
// Contest : DMOJ
// URL : https://dmoj.ca/problem/heist
// Memory Limit : 256 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int T, N, K;
long long dp[55][100005];
int arr[100005];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while(T--){
		cin >> N >> K;
		for(int i = 0; i<N; i++){
			cin >> arr[i];
		}
		if(N == K){
			long long ans = 0;
			for(int i = 0; i<N; i++){
				ans += (arr[i] > 0)*arr[i];
			}
			cout << ans << "\n";
			continue;
		}
		K++;
		long long ans = 0;
		for(int s = 0; s<=K; s++){
			for(int i = 1; i<N; i++){
				for(int k = 0; k<K; k++){
					dp[k+1][i+1] = max(dp[k+1][i+1], dp[k][i] + arr[(s+i)%N]);
					dp[0][i+1] = max(dp[0][i+1], dp[k][i]);
				}
			}
			for(int k = 0; k<K; k++){
				ans = max(ans, dp[k][N]);
			}
			for(int i = 0; i<=N; i++){
				for(int k = 0; k<=K; k++){
					dp[k][i] = 0;
				}
			}
		}
		cout << ans << "\n";
	}
}
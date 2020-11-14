#include <bits/stdc++.h>

using namespace std;

int N;
int arr[10005];
int dp[10005];
int mx[10005];
const int MOD = 1000007;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
		mx[i] = max(mx[i-1], arr[i]);
		dp[i] = 1;
	}
	long long ans = 0;
	for(int i = N; i; i--){
		ans += 1LL*min(arr[i]-1, mx[i-1]) * dp[mx[i-1]];
		for(int j = 1; j<N; j++){
			dp[j] = (1LL * j * dp[j] + dp[j+1])%MOD;
		}
		ans %= MOD;
	}
	cout << (ans+1)%MOD;
}
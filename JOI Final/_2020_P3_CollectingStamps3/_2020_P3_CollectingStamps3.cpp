#include <bits/stdc++.h>

using namespace std;

int N, L;
long long dp[2][205][205][205];
//bool vis[2][205][205][205];
long long arr[205], brr[205];

void relax(int cw,int ccw, int k){
	long long d = dp[0][cw][ccw][k]+arr[cw+1]-arr[cw];
	bool kk = (d <= brr[cw+1]);
	assert(d >= 0);
	dp[0][cw+1][ccw][k+kk] = min(dp[0][cw+1][ccw][k+kk], d);
	d = dp[1][cw][ccw][k] + L-arr[ccw] + arr[cw+1];
	kk = (d <= brr[cw+1]);
	assert(d >= 0);
	dp[0][cw+1][ccw][k+kk] = min(dp[0][cw+1][ccw][k+kk], d);
	d = dp[0][cw][ccw][k] + arr[cw] + L-arr[ccw-1];
	kk = (d <= brr[ccw-1]);
	assert(d >= 0);
	dp[1][cw][ccw-1][k+kk] = min(dp[1][cw][ccw-1][k+kk], d);
	d = dp[1][cw][ccw][k] + arr[ccw] - arr[ccw-1];
	kk = (d <= brr[ccw-1]);
	assert(d >= 0);
	dp[1][cw][ccw-1][k+kk] = min(dp[1][cw][ccw-1][k+kk], d);
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> L;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
	}
	for(int i = 1; i<=N; i++){
		cin >> brr[i];
	}
	for(int cw = 0; cw<=N; cw++){
		for(int ccw = N+1; ccw>cw; ccw--){
			for(int k = 0; k<=N; k++){
				dp[0][cw][ccw][k] = dp[1][cw][ccw][k] = LLONG_MAX/4;
			}
		}
	}
	dp[0][0][N+1][0] = 0; //sd = 0 means cw
	arr[N+1] = L;
	for(int cw = 0; cw<=N; cw++){
		for(int ccw = N+1; ccw>cw+1; ccw--){
			for(int k = 0; k<=N; k++){
				relax(cw, ccw, k);
			}
		}
	}
	int ans = 0;
	for(int k = 0; k<=N; k++){
		for(int cw = 0; cw<=N; cw++){
			for(int ccw = N+1; ccw>cw; ccw--){
				if(dp[0][cw][ccw][k] != LLONG_MAX/4){
					ans = max(ans, k);
				}
				if(dp[1][cw][ccw][k] != LLONG_MAX/4){
					ans = max(ans, k);
				}
			}
		}
	}
	cout << ans;
}
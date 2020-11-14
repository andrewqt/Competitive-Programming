
// Problem : USACO 2018 February Contest Gold P3 - Taming the Herd
// Contest : DMOJ
// URL : https://dmoj.ca/problem/usaco18febgold3
// Memory Limit : 512.000000 MB 
// Time Limit : 1000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int arr[105];
int dp[105][105][105];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int N;
	cin >> N;
	for(int i= 1; i<=N; i++){
		cin >> arr[i];
	}
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=N; j++){
			for(int k = 0; k<=N; k++){
				dp[i][j][k] = 200;
			}
		}
	}
	dp[1][1][0] = (arr[1] != 0);
	for(int i = 1; i<N; i++){
		for(int k = 1; k<=N; k++){
			for(int j = 0; j<=N; j++){
				dp[i+1][k][j+1] = min(dp[i+1][k][j+1], dp[i][k][j] + !(arr[i+1] == j+1));
				dp[i+1][k+1][0] = min(dp[i+1][k+1][0], dp[i][k][j] + !!(arr[i+1]));
			}
		}
	}
	for(int k = 1; k<=N; k++){
		int ans = 200;
		for(int j = 0; j<=N; j++){
			ans = min(ans, dp[N][k][j]);
		}
		cout << ans << "\n";
	}
}
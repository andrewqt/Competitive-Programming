
// Problem : COCI '10 Contest 1 #5 Tabovi
// Contest : DMOJ
// URL : https://dmoj.ca/problem/coci10c1p5
// Memory Limit : 32 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N;
int arr[1005];
int dp[85][85][1005];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
	}
	for(int i = 1; i<=N; i++){
		int n;
		cin >> n;
		arr[i] = n - arr[i];
	}
	memset(dp, 63, sizeof dp);
	dp[1][0][0] = 0;
	
}
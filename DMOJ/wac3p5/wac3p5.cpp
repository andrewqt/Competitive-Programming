
// Problem : Wesley's Anger Contest 3 Problem 5
// Contest : DMOJ
// URL : https://dmoj.ca/problem/wac3p5
// Memory Limit : 512.000000 MB 
// Time Limit : 1000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int N;
pair<int, long long> arr[5005];
long long dp[5005][5005];
long long mx[5005];
int ptr[5005];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	long long tot = 0;
	for(int i = 1; i<=N; i++){
		cin >> arr[i].first >> arr[i].second;
		tot += arr[i].second;
	}
	if(N <= 2){
		cout << 0 << "\n";
		return 0;
	}
	sort(arr+1, arr+1+N);
	long long ans = 0;
	for(int i= 1; i<=N; i++){
		for(int j = 1; j<i; j++){
			dp[i][j] = arr[j].second;
			while(ptr[j] < N && arr[j].first + arr[ptr[j]+1].first <= arr[i].first){
				ptr[j]++;
				//cout << i << " " << j << "\n";
				mx[j] = max(mx[j], dp[j][ptr[j]]);
			}
			dp[i][j] = max(mx[j], dp[i][j]) + arr[i].second;
			ans = max(ans, dp[i][j]);
			//cout << dp[i][j] << " " << i << " " << j << "\n";
		}
	}
	cout << tot - ans << "\n";
}
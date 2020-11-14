
// Problem : F - Knapsack for All Subsets
// Contest : AtCoder - AtCoder Beginner Contest 169
// URL : https://atcoder.jp/contests/abc169/tasks/abc169_f
// Memory Limit : 1024 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N, X;
long long dp[3005];
const long long MOD = 998244353;

long long add(long long a, long long b){
	return (a+b)%MOD;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> X;
	dp[0] = 1;
	for(int i = 1; i<=N; i++){
		int n;
		cin >> n;
		for(int k = X; k>=0; k--){
			dp[k] = add(dp[k], dp[k]);
			if(k >= n){
				dp[k] = add(dp[k], dp[k-n]);
			}
		}
	}
	cout << dp[X] << "\n";
}
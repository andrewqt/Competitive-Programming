
// Problem : A - Pay to Win
// Contest : AtCoder - AtCoder Grand Contest 044
// URL : https://atcoder.jp/contests/agc044/tasks/agc044_a
// Memory Limit : 1024 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int T;
long long N, A, B, C, D;
map<long long, long long> dp;

long long solve(long long n){
	//cout << n << endl;
	if(!n){
		return 0;
	}
	if(n == 1){
		return D;
	}
	if(dp.count(n)){
		return dp[n];
	}
	long long res = n*D;
	if(1000000000000000000LL/D < n){
		res = LLONG_MAX;
	}
	res = min(res, solve(n/2)+A+(n%2)*D);
	res = min(res, solve((n+1)/2)+A+(n%2)*D);
	res = min(res, solve(n/3)+B+(n%3)*D);
	res = min(res, solve((n+2)/3)+B+(3-n%3)*D);
	res = min(res, solve(n/5)+C+(n%5)*D);
	res = min(res, solve((n+4)/5)+C+(5-n%5)*D);
	return dp[n] = res;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while(T--){
		cin >> N >> A >> B >> C >> D;
		cout << solve(N) << endl;
		dp.clear();
	}
}
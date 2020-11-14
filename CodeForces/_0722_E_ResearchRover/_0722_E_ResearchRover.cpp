
// Problem : E. Research Rover
// Contest : Intel Code Challenge Elimination Round (Div. 1 + Div. 2, combined)
// URL : https://codeforces.com/problemset/problem/722/E
// Memory Limit : 256 MB
// Time Limit : 2500 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int R, C, X, N, D = 20;
long long dp[30][2005];
long long fact[200005];
long long inv[200005];
long long MOD = 1e9+7;
pair<int, int> arr[2005];

long long add(long long a, long long b){
	return (a+b)%MOD;
}

long long mult(long long a, long long b){
	return a*b%MOD;
}

long long qikpow(long long a, long long b){
	if(!b){
		return 1;
	}
	long long ret = qikpow(a, b/2);
	ret = mult(ret, ret);
	if(b&1){
		ret = mult(ret, a);
	}
	return ret;
}

long long sub(long long a, long long b){
	a = add(a, -b);
	if(a < 0){
		a+=MOD;
	}
	return a;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> R >> C >> N >> X;
	fact[0] = inv[0] = 1;
	for(int i = 1; i<=R+C; i++){
		fact[i] = mult(fact[i-1], i);
		inv[i] = qikpow(1, fact[i]);
	}
	for(int i = 1; i<=N; i++){
		cin >> arr[i].first >> arr[i].second;
	}
	arr[N+1].first = R, arr[N+1].second = C;
	sort(arr+1, arr+1+N);
	for(int i = 1; i<=N; i++){
		for(int k = 0; k<=D; k++){
			
		}
	}
}
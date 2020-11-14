
// Problem : E - Max-Min Sums
// Contest : AtCoder Beginner Contest 151
// URL : https://atcoder.jp/contests/abc151/tasks/abc151_e
// Memory Limit : 1024.000000 MB 
// Time Limit : 2000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int N, K;
long long MOD = 1e9+7;
long long arr[1000005];
long long fact[1000005];

long long mult(long long a, long long b){
	return (a*b)%MOD;
}

long long add(long long a, long long b){
	return (a+b)%MOD;
}

long long qikpow(long long b, long long e){
	if(!e){
		return 1;
	}
	long long ret = qikpow(b, e/2);
	ret = mult(ret, ret);
	if(e&1){
		ret = mult(ret, b);
	}
	return ret;
}

long long divd(long long a, long long b){
	return mult(a, qikpow(b, MOD-2));
}

long long sub(long long a, long long b){
	a = add(a, -b);
	if(a < 0){
		a += MOD;
	}
	return a;
}

long long choose(long long n, long long r){
	if(n-r < 0){
		return 0;
	}
	return divd(fact[n], mult(fact[r], fact[n-r]));
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> K;
	fact[0] = 1;
	for(int i = 1; i<=N; i++){
		fact[i] = mult(i, fact[i-1]);
		cin >> arr[i];
	}
	sort(arr+1, arr+1+N);
	long long ans = 0;
	for(int i = 1; i<=N; i++){
		ans = add(ans, mult(arr[i], choose(i-1, K-1)));
		ans = sub(ans, mult(arr[i], choose(N-i, K-1)));
	}
	cout << ans << "\n";
}
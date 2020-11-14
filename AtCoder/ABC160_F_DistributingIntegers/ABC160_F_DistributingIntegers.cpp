
// Problem : F - Distributing Integers
// Contest : AtCoder Beginner Contest 160
// URL : https://atcoder.jp/contests/abc160/tasks/abc160_f
// Memory Limit : 1024 MB
// Time Limit : 3000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> graph[200005];
long long fact[200005];
long long dp[200005];
long long sz[200005];
long long ans[200005];
const long long MOD = 1e9+7;

long long mult(long long a, long long b){
	return (a*b)%MOD;
}

long long qikpow(long long b, long long e){
	if(!e){
		return 1;
	}
	long long ret = qikpow(b, e>>1);
	if(e&1){
		return mult(mult(ret, ret), b);
	}
	return mult(ret, ret);
}

long long divd(long long a, long long b){
	return mult(a, qikpow(b, MOD-2));
}

void dfs1(int n, int p){
	sz[n] = 1;
	dp[n] = 1;
	for(int e : graph[n]){
		if(e != p){
			dfs1(e, n);
			dp[n] = mult(dp[e], dp[n]);
			dp[n] = divd(dp[n], fact[sz[e]]);
			sz[n] += sz[e];
		}
	}
	//cout << n << " " << dp[n] << "\n";
	dp[n] = mult(dp[n], fact[sz[n]-1]);
}

void dfs2(int n, int p){
	dp[n] = fact[N-1];
	for(int e : graph[n]){
		if(e == p){
			dp[n] = mult(dp[e], dp[n]);
			dp[n] = divd(dp[n], fact[N-sz[n]]);
		}
		else{
			dp[n] = mult(dp[e], dp[n]);
			dp[n] = divd(dp[n], fact[sz[e]]);
		}
	}
	ans[n] = dp[n];
	for(int e : graph[n]){
		if(e != p){
			long long olde = dp[e];
			dp[n] = divd(dp[n], fact[N-1]);
			dp[n] = mult(dp[n], fact[N-sz[e]-1]);
			dp[n] = divd(dp[n], dp[e]);
			dp[n] = mult(dp[n], fact[sz[e]]);
			//cout << e << " " << p << " extra: " << dp[n] << "\n";
			dfs2(e, n);
			dp[n] = ans[n];
			dp[e] = olde;
		}
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 1; i<N; i++){
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	fact[0] = 1;
	for(int i = 1; i<=N; i++){
		fact[i] = mult(fact[i-1], i);
	}
	dfs1(1, 0);
	//cout << dp[1] << "\n";
	dfs2(1, 0);
	for(int i = 1; i<=N; i++){
		cout << ans[i] << "\n";
	}
}
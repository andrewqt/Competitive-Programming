#include <bits/stdc++.h>

using namespace std;

long long N, K;
long long MOD;
long long dp[305][50000];
long long poly[200000];
long long temp[200000];
long long offset = 100000;

long long add(long long a, long long b){
	return (a+b)%MOD;
}

long long sub(long long a, long long b){
	a = add(a, -b);
	if(a < 0){
		a += MOD;
	}
	return a;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("treedepth.in", "r")){
		freopen("treedepth.in", "r", stdin);
		freopen("treedepth.out", "w", stdout);
	}
	cin >> N >> K >> MOD;
	dp[0][0] = 1;
	for(int i = 1; i<=N; i++){
		for(int j = 0; j<=i*(i-1)/2; j++){
			for(int k = j; k>j-i && k>=0; k--){
				dp[i][j] = add(dp[i-1][k], dp[i][j]);
			}
		}
	}
	for(int k = 0; k<=N*(N-1)/2; k++){
		poly[offset+k] = dp[N][k];
	}	
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=N; j++){
			if(i < j){
				for(int k = )
			}
		}
	}
}
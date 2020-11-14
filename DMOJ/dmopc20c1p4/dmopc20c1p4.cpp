
// Problem : DMOPC '20 Contest 1 P4
// Contest : DMOJ
// URL : https://dmoj.ca/problem/dmopc20c1p4
// Memory Limit : 64 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1e9+7;

struct Matrix{
	vector<vector<long long>> mat;
	int r, c;
	
	Matrix(){
		r = c = 0;
	}
	
	Matrix(long long _r, long long _c){
		r = _r, c = _c;
		mat.resize(_r);
		for(int i = 0; i<_r; i++){
			mat[i].resize(_c, 0);
		}
	}
	
	Matrix operator * (const Matrix & m){
		Matrix ret(r, m.c);
		for(int i = 0; i<r; i++){
			for(int j = 0; j<m.c; j++){
				for(int k = 0; k<c; k++){
					ret.mat[i][j] += mat[i][k] * m.mat[k][j] % MOD;
					ret.mat[i][j] %= MOD;
				}
				assert(ret.mat[i][j] >= 0);
				ret.mat[i][j] %= MOD;
			}
		}
		return ret;
	}
};

long long N, C, K, T;
Matrix M;

Matrix qikpow(long long e){
	if(!e){
		Matrix X = Matrix(T, T);
		for(int i = 0; i<T; i++){
			X.mat[i][i] = 1;
		}
		return X;
	}
	Matrix R = qikpow(e/2);
	R = R * R;
	if(e&1){
		R = M * R;
	}
	return R;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> K >> T >> C;
	if(N == 1){
		cout << 2*C%MOD << "\n";
		return 0;
	}
	N--;
	T++;
	M = Matrix(T, T);
	for(int i = 1; i<T; i++){
		M.mat[i-1][i] = 1;
	}
	M.mat[T-1][0] = K;
	M.mat[T-1][T-1] = 1;
	auto R = qikpow(N);
	Matrix I = Matrix(T, 1);
	I.mat[T-1][0] = C;
	R = R * I;
	long long ans = 2 * R.mat[R.r-1][0] % MOD;
	for(int k = 0; k<R.r-1; k++){
		ans += K * R.mat[k][0] % MOD;
		ans %= MOD;
	}
	cout << ans << "\n";
	/*
	dp[0] = C;
	for(int i = 1; i<=N; i++){
		dp[i] = dp[i-1];
		if(i >= T){
			dp[i] += dp[i-T]*K;
			dp[i] %= MOD;
		}
	}
	long long ans = 2*dp[N];
	for(int i = 1; i<min(T, N+1); i++){
		ans += K*dp[N-i];
		ans %= MOD;
	}
	cout << ans << "\n";
	*/
	/*
	if(N+1 > 1e6){
		cout << N+1 << " " << K << " " << T-1 << " " << C << endl;
	}
	*/
}
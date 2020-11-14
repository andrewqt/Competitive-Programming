
// Problem : APIO '09 P1 - Digging for Oil
// Contest : DMOJ
// URL : https://dmoj.ca/problem/apio09p1
// Memory Limit : 128 MB
// Time Limit : 750 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N, M, K;
int arr[1505][1505];
int tmp[1505][1505];
int psa[1505][1505];
int pre[1505], suf[1505];
int ans;

int sum(int r2, int c2, int r1, int c1){
	r1--, c1--;
	return psa[r2][c2] - psa[r1][c2] - psa[r2][c1] + psa[r1][c1];
}

void solve1(int N, int M){
	for(int j = 0; j<=M+1; j++){
		pre[j] = suf[j] = 0;
	}
	for(int i = K; i<=N-K; i++){
		for(int j= K; j<=M; j++){
			pre[j] = max(pre[j], sum(i, j, i-K+1, j-K+1));
			suf[j] = max(suf[j], sum(i, j, i-K+1, j-K+1));
			pre[j] = max(pre[j], pre[j-1]);
		}
		for(int j = M; j>=K; j--){
			suf[j] = max(suf[j], suf[j+1]);
		}
		int mx = 0;
		for(int j = K; j<=M-K; j++){
			mx = max(mx, pre[j] + suf[j+K]);
		}
		for(int j = K; j<=M; j++){
			ans = max(ans, mx + sum(i+K, j, i+1, j-K+1));
		}
	}
}

void solve2(int N, int M){
	for(int j= 0; j<=M+1; j++){
		pre[j] = suf[j] = 0;
	}
	for(int i = K; i<=N; i++){
		for(int j = K; j<=M; j++){
			pre[j] = max(pre[j], sum(i, j, i-K+1, j-K+1));
			suf[j] = max(suf[j], sum(i, j, i-K+1, j-K+1));
		}
	}
	for(int j = K; j<=M; j++){
		pre[j] = max(pre[j], pre[j-1]);
	}
	for(int j = M; j>=K; j--){
		suf[j] = max(suf[j], suf[j+1]);
	}
	for(int i = K; i<=N; i++){
		for(int j = K; j<=M-K; j++){
			ans = max(ans, sum(i, j, i-K+1, j-K+1) + pre[j-K] + suf[j+K]);
		}
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M >> K;
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=M; j++){
			cin >> arr[i][j];
		}
	}
	for(int m = 0; m<4; m++){
		for(int i = 1; i<=N; i++){
			for(int j = 1; j<=M; j++){
				tmp[M-j+1][i] = arr[i][j];
			}
		}
		swap(N, M);
		for(int i = 1; i<=N; i++){
			for(int j = 1; j<=M; j++){
				arr[i][j] = tmp[i][j];
			}
		}
		for(int i = 1; i<=N; i++){
			for(int j = 1; j<=M; j++){
				psa[i][j] = arr[i][j] + psa[i-1][j] + psa[i][j-1] - psa[i-1][j-1];
			}
		}
		solve1(N, M);
		solve2(N, M);
	}
	cout << ans << "\n";
}
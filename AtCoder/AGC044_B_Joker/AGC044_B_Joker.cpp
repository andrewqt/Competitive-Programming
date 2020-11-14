
// Problem : B - Joker
// Contest : AtCoder - AtCoder Grand Contest 044
// URL : https://atcoder.jp/contests/agc044/tasks/agc044_b
// Memory Limit : 1024 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N;
int dp[505][505];
int arr[505][505];
int x[505*505], y[505*505];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
pair<int, int> qu[505*505];
int l, r;

bool chk(int xx, int yy, int t){
	return dx[t]+xx <= N && dx[t]+xx && dy[t]+yy <= N && dy[t]+yy;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=N; j++){
			int n;
			cin >> n;
			n--;
			x[(i-1)*N+j] = n/N+1;
			y[(i-1)*N+j] = n%N+1;
			dp[i][j] = min({i-1, j-1, N-i, N-j});
		}
	}
	for(int i= 1; i<=N*N; i++){
		arr[x[i]][y[i]] = i;
	}
	/*
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=N; j++){
			cout << arr[i][j] << " ";
		}
		cout << "\n";
	}
	*/
	int ans = 0;
	for(int i = 1; i<=N*N; i++){
		ans += dp[x[i]][y[i]];
		for(int m = 0; m<4; m++){
			if(chk(x[i], y[i], m)){
				dp[x[i]][y[i]] = min(dp[x[i]+dx[m]][y[i]+dy[m]]+ (arr[x[i]+dx[m]][y[i]+dy[m]] > i), dp[x[i]][y[i]]);
			}
		}
		l = r = 1;
		qu[1] = make_pair(x[i], y[i]);
		while(l <= r){
			auto n = qu[l++];
			int a = n.first;
			int b = n.second;
			for(int m = 0 ; m<4; m++){
				if(chk(a,b, m) && dp[a+dx[m]][b+dy[m]] > dp[a][b] + (arr[a][b] > i)){
					dp[a+dx[m]][b+dy[m]] = dp[a][b] + (arr[a][b] > i);
					qu[++r] = make_pair(a+dx[m], b+dy[m]);
				}
			}
		}
		/*
		cout << i << " " << ans << "\n";
		for(int i = 1; i<=N; i++){
			for(int j = 1; j<=N; j++){
				cout << dp[i][j] << " ";
			}
			cout << "\n";
		}
		*/
	}
	cout << ans << "\n";
}
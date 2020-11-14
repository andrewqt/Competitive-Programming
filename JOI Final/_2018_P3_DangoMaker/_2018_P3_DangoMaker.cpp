#include <bits/stdc++.h>

using namespace std;

int N, M;
char arr[3005][3005];
int dp[3][3005][3005]; //0 ntg, 1 hor, 2 ver

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;	
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=M; j++){
			cin >> arr[i][j];
		}
	}
	int lst = 0, pre = 0;
	for(int d = 2; d<=N+M; d++){
		for(int r = 1; r<=N; r++){
			int c = d-r;
			if(c <= 0 || c > M){
				continue;
			}
			dp[0][r][c] = max({lst, dp[0][r-1][c+1], dp[1][r-1][c+1], dp[2][r-1][c+1]});
			if(arr[r][c] == 'G' && arr[r][c-1] == 'R' && arr[r][c+1] == 'W'){
				dp[1][r][c] = max({dp[0][r-1][c+1], dp[1][r-1][c+1], pre}) + 1;
			}
			if(arr[r][c] == 'G' && arr[r-1][c] == 'R' && arr[r+1][c] == 'W'){
				dp[2][r][c] = max({dp[0][r-1][c+1], dp[2][r-1][c+1], pre}) + 1;
			}
			lst = max({dp[0][r][c], dp[1][r][c], dp[2][r][c]});
		}
		pre = lst;
	}
	cout << pre << "\n";
}
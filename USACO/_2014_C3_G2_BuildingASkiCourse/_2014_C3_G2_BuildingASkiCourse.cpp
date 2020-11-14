#include <bits/stdc++.h>

using namespace std;

int N, M;
int dp[2][1005][1005];
int arr[1005][1005];
int pre[2][1005][1005];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("skicourse.in", "r")){
		freopen("skicourse.in", "r", stdin);
		freopen("skicourse.out", "w", stdout);
	}
	cin >> N >> M;
	for(int i = 1; i<=N; i++){
		string s;
		cin >> s;
		for(int j = 1; j<=M; j++){
			arr[i][j] = s[j-1] == 'R';
		}
	}
	int T = N*M, ans = N;
	while(T--){
		int idx = 0, mxx = 0, mxy = 0;
		for(int i = 1; i<=N; i++){
			for(int j = 1; j<=M; j++){
				dp[0][i][j] = dp[1][i][j] = 0;	
				pre[0][i][j] = pre[0][i-1][j] + pre[0][i][j-1] - pre[0][i-1][j-1];
				pre[1][i][j] = pre[1][i-1][j] + pre[1][i][j-1] - pre[1][i-1][j-1];
				if(arr[i][j] == 1){
					pre[1][i][j]++;
				}
				if(arr[i][j] == 0){
					pre[0][i][j]++;
				}
				if(arr[i][j] == 1 || arr[i][j] == 2){
					dp[1][i][j] = min(dp[1][i-1][j], min(dp[1][i-1][j-1], dp[1][i][j-1])) + 1;
				}	
				if(arr[i][j] == 0 || arr[i][j] == 2){
					dp[0][i][j] = min(dp[0][i-1][j], min(dp[0][i][j-1], dp[0][i-1][j-1])) + 1;
				}
				//cout << i << " " << j << " " << dp[0][i][j] << " " << dp[1][i][j] << endl;
				int l = dp[0][i][j];
				if(dp[idx][mxx][mxy] < dp[0][i][j] && pre[0][i][j] - pre[0][i-l][j] - pre[0][i][j-l] + pre[0][i-l][j-l]){
					idx = 0;
					mxx = i;
					mxy = j;
				}
				l = dp[1][i][j];
				if(dp[idx][mxx][mxy] < dp[1][i][j] && pre[1][i][j] - pre[1][i-l][j] - pre[1][i][j-l] + pre[1][i-l][j-l]){
					idx = 1;
					mxx = i;
					mxy = j;
				}
			}
		}
		if(!mxx){
			break;
		}
		const int l = dp[idx][mxx][mxy];
		ans = min(ans, l);
		for(int i = mxx; i>mxx-l; i--){
			for(int j = mxy; j>mxy-l; j--){
				arr[i][j] = 2;
			}
		}
	}
	cout << ans << endl;
}
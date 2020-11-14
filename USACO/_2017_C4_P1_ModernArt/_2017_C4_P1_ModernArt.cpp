
// Problem : USACO 2017 March Contest Platinum P1 - Modern Art
// Contest : DMOJ
// URL : https://dmoj.ca/problem/usaco17marplat1
// Memory Limit : 512.000000 MB 
// Time Limit : 2000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int N;
int mnx[1000005], mxx[1000005], mxy[1000005], mny[1000005];
bool ans[1000005];
int arr[1005][1005];
int canvas[1005][1005];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("art.in", "r")){
		freopen("art.in", "r", stdin);
		freopen("art.out", "w", stdout);
	}
	cin >> N;
	int tot = 0;
	fill(mnx+1, mnx+N*N+1, N+1);
	fill(mny+1, mny+N*N+1, N+1);
	fill(ans+1, ans+1+N*N, 1);
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=N; j++){
			int n;
			cin >> n;
			canvas[i][j] = n;
			mnx[n] = min(mnx[n], i);
			mxx[n] = max(mxx[n], i);
			mny[n] = min(mny[n], j);
			mxy[n] = max(mxy[n], j);
		}
	}
	for(int n = 1; n<=N*N; n++){
		if(mxx[n]){
			tot++;
			arr[mxx[n]+1][mxy[n]+1]++;
			arr[mnx[n]][mxy[n]+1]--;
			arr[mxx[n]+1][mny[n]]--;
			arr[mnx[n]][mny[n]]++;
		}
	}
	if(tot == 1){
		cout << N*N-1 << "\n";
		return 0;
	}
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=N; j++){
			arr[i][j] += arr[i-1][j] + arr[i][j-1] - arr[i-1][j-1];
			//cout << i << " " << j << " " << arr[i][j] << "\n";
			if(arr[i][j] > 1){
				ans[canvas[i][j]] = 0;
			}
		}
	}
	int cnt = 0;
	for(int i = 1; i<=N*N; i++){
		cnt += ans[i];
	}
	cout << cnt << endl;
}
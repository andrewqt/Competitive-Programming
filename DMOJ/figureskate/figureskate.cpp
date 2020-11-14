
// Problem : Figure Skating
// Contest : DMOJ
// URL : https://dmoj.ca/problem/figureskate
// Memory Limit : 256 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N;
pair<int, int> arr[3005];
long long dp[3005][3005];
int mnn[3005][3005], mxx[3005][3005];
long long f[3005][3005];
int pos[3005][3005];
bool b[3005][3005];
//pair<int, int> rng[3005][3005];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 1; i<=N; i++){
		cin >> arr[i].first >> arr[i].second;
	}
	sort(arr+1, arr+1+N);
	for(int l = 1; l<=N; l++){
		int mx = arr[l].second, mn = mx;
		int mxidx = l, mnidx = l;
		b[l][l] = 1;
		mnn[l][l] = mn;
		mxx[l][l] = mx;
		for(int r = l+1; r<=N; r++){
			if(mx < arr[r].second){
				mxidx = r;
				mx = arr[r].second;
			}
			if(mn > arr[r].second){
				mnidx = r;
				mn = arr[r].second;
			}
			f[l][r] = 2LL*(arr[r].first-arr[l].first+mx-mn);
			b[l][r] = 1;
			if(arr[r].second > arr[l].second && mxidx < mnidx){
				b[l][r] = 0;
			}
			if(arr[r].second < arr[l].second && mnidx < mxidx){
				b[l][r] = 0;
			}
			//rng[l][r] = {min(mnidx, mxidx), max(mnidx, mxidx)};
			mxx[l][r] = mx;
			mnn[l][r] = mn;
		}
	}
	for(int len = 1; len<=N; len++){
		for(int l = 1; l<=N-len; l++){
			int r = l+len;
			if(b[l][r]){
				b[l][r] = 0;
				dp[l][r] = LLONG_MAX/2;
				for(int k = l; k<r; k++){
					if(b[l][k] && b[k+1][r] && (mnn[l][k] > mxx[k+1][r] || mxx[l][k] < mnn[k+1][r])){
						dp[l][r] = min(dp[l][r], dp[l][k] + dp[k+1][r]);
						b[l][r] = 1;
					}
				}
				dp[l][r] += f[l][r];
			}
		}
	}
	if(b[1][N]){
		cout << dp[1][N] << "\n";
	}
	else{
		cout << -1 << "\n";
	}
}
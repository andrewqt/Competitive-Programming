// Problem : Terra Mater
// Contest : DMOJ
// URL : https://dmoj.ca/problem/terramater
// Memory Limit : 64 MB
// Time Limit : 600 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N, K;
int arr[3005];
int dp[3005][3005];
deque<pair<int, int>> dq;

int solve(int lim){
	for(int i = 1; i<=N; i++){
		int ptr = 0;
		for(int h = 1; h<=3000; h++){
			while(ptr < 3000 && ptr < h+lim){
				ptr++;
				while(dq.size() && dq.back().first >= dp[i-1][ptr]){
					dq.pop_back();
				}
				dq.push_back(make_pair(dp[i-1][ptr], ptr));
			}
			if(dq.size() && dq.front().second < h - lim){
				dq.pop_front();
			}
			dp[i][h] = dq.front().first + (h != arr[i]);
		}
		dq.clear();
	}
	int ret = 10000;
	for(int h = 1; h<=3000; h++){
		ret = min(ret, dp[N][h]);
	}
	return ret;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> K;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
	}
	int l = 1, r = 3000;
	int ans = 0;
	while(l <= r){
		int mid = l+r>>1;
		if(solve(mid) <= K){
			r = mid - 1;
			ans = mid;
		}
		else{
			l =mid +1;
		}
	}
	cout << ans << "\n";
}
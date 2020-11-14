
// Problem : CCC '20 S5 - Josh's Double Bacon Deluxe
// Contest : DMOJ
// URL : https://dmoj.ca/problem/ccc20s5
// Memory Limit : 512 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N, M;
int arr[1000005];
int lst[1000005];
int cnt[1000005];
long double dp[1000005];
long double pre[1000005];
bool stop[1000005];
vector<int> v[1000005];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
		cnt[arr[i]]++;
		lst[arr[i]] = i;
		v[arr[i]].push_back(i);
		M = max(M,arr[i]);
	}
	for(int i = 1; i<=M; i++){
		stop[lst[i]] = 1;
	}
	if(arr[1] == arr[N]){
		cout << 1 << "\n";
		return 0;
	}
	dp[1] = 1;
	pre[1] = 1.0/N;
	for(int i = 2; i<=N; i++){
		if(stop[i] && arr[i] != arr[1]){
			reverse(v[arr[i]].begin(), v[arr[i]].end());
			for(int j = 1; j<v[arr[i]].size(); j++){
				//cout << v[arr[i]][j-1] << " " <<v[arr[i]][j] << "\n";
				//cout << pre[v[arr[i]][j-1]-1] << " " << pre[v[arr[i]][j]-1] << "\n";
				//cout << (pre[v[arr[i]][j-1]-1] - pre[v[arr[i]][j]-1]) << "\n";
				dp[i] += (pre[v[arr[i]][j-1]-1] - pre[v[arr[i]][j]-1])*j;
			}
			dp[i] += (pre[v[arr[i]].back()-1]) * (v[arr[i]].size());
			pre[i] = dp[i] / (N - i + 1);
		}
		pre[i] += pre[i-1];
		//cout << "pre " << i << ": " << pre[i] << "\n";
	}
	cout << setprecision(12) << 1 - dp[N] << "\n";
}
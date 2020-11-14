
// Problem : DMOPC '20 Contest 1 P3
// Contest : DMOJ
// URL : https://dmoj.ca/problem/dmopc20c1p3
// Memory Limit : 256 MB
// Time Limit : 600 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

//int N;
//long long arr[500005];

int solve(int N, vector<int> arr){
	int idx = max_element(arr.begin(), arr.end()) - arr.begin();
	int mx = 0, ans = 0;
	for(int i = 1; i<idx; i++){
		mx = max(mx, arr[i]);
		ans += mx - arr[i];
	}
	mx = 0;
	for(int i = N; i>idx; i--){
		mx = max(mx, arr[i]);
		ans += mx - arr[i];
	}
	return ans;	
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
	}
	long long idx = max_element(arr+1, arr+1+N) - arr;
	long long mx = LLONG_MIN, ans = 0;
	for(int i = 1; i<idx; i++){
		mx = max(mx, arr[i]);
		ans += mx - arr[i];
	}
	mx = LLONG_MIN;
	for(int i = N; i>idx; i--){
		mx = max(mx, arr[i]);
		ans += mx - arr[i];
	}
	cout << ans << "\n";
}
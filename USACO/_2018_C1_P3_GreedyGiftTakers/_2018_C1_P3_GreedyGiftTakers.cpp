
// Problem : USACO 2017 December Contest Platinum P3 - Greedy Gift Takers
// Contest : DMOJ
// URL : https://dmoj.ca/problem/usaco17decplat3
// Memory Limit : 512.000000 MB 
// Time Limit : 2000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int arr[100005];
int cnt[100005];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int N;
	cin >> N;
	for(int i= 1; i<=N; i++){
		cin >> arr[i];
		arr[i] = N-arr[i];
	}
	int l = 1, r = N, ans = 0;
	while(l <= r){
		int mid = l+r>>1;
		fill(cnt+1, cnt+1+N, 0);
		for(int i = 1; i<=mid; i++){
			cnt[arr[i]]++;
		}
		bool b = 0;
		for(int i = 1; i<=mid; i++){
			cnt[i] += cnt[i-1];
			if(cnt[i] >= i){
				b = 1;
			}
		}
		if(b){
			r = mid - 1;
			ans = N - mid;
		}
		else{
			l = mid + 1;
		}
	}
	cout << ans << endl;
}
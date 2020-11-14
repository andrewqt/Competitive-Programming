
// Problem : USACO 2017 February Contest Platinum P1 - Why Did the Cow Cross the Road
// Contest : DMOJ
// URL : https://dmoj.ca/problem/usaco17febplat1
// Memory Limit : 512.000000 MB 
// Time Limit : 2000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int N;
long long bit[100005];
int pos[100005];
int arr[100005];
int brr[100005];
int crr[100005];

void upd(int p){
	while(p <= N){
		bit[p]++;
		p += p&-p;
	}
}

long long query(int p){
	long long ret = 0;
	while(p){
		ret += bit[p];
		p -= p&-p;
	}
	return ret;
}

long long solve(){
	fill(bit+1, bit+1+N, 0);
	for(int i = 1; i<=N; i++){
		pos[brr[i]] = i;
	}
	long long ans = 0;
	for(int i = 1; i<=N; i++){
		crr[i] = pos[arr[i]];
		ans += i-1 - query(crr[i]);
		upd(crr[i]);
	}
	long long crnt = ans;
	for(int i= 1; i<=N; i++){
		crnt -= crr[i]-1;
		crnt += N-crr[i];
		ans = min(ans, crnt);
	}
	return ans;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
	}
	for(int i= 1; i<=N; i++){
		cin >> brr[i];
	}
	long long ans = solve();
	swap(arr, brr);
	ans = min(ans, solve());
	cout << ans << "\n";
}

// Problem : Problem 1. Out of Sorts
// Contest : USACO 2018 US Open Contest, Platinum
// URL : http://www.usaco.org/index.php?page=viewproblem2&cpid=840
// Memory Limit : 256.000000 MB 
// Time Limit : 4000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int N;
int pos[100005];
int arr[100005];
pair<int, int> srt[100005];
int t[100005];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("sort.in", "r")){
		freopen("sort.in", "r", stdin);
		freopen("sort.out", "w", stdout);
	}
	cin >> N;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
		srt[i] = {arr[i], i};
	}
	sort(srt+1, srt+1+N);
	for(int i = 1; i<=N; i++){
		pos[i] = srt[i].second;
	}
	long long ans = 0;
	int mx = 0;
	for(int i = 1; i<N; i++){
		mx = max(pos[i], mx);
		t[i] = max(1, mx-i);
	}
	for(int i = 1; i<=N; i++){
		ans += max(t[i], t[i-1]);
	}
	cout << ans << endl;
}
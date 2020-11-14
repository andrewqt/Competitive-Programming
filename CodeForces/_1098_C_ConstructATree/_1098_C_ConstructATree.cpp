
// Problem : C. Construct a tree
// Contest : Codeforces - Codeforces Round #530 (Div. 1)
// URL : https://codeforces.com/problemset/problem/1098/C
// Memory Limit : 256 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N;
long long S;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> S;
	if(1LL*N*(N+1) < S*2){
		cout << "No\n";
		return 0;
	}
	long long l = 1, r = N, ans = 0;
	while(l <= r){
		long long mid = l+r>>1;
		long long tot = 0;
		long long dep = 1, amt = 1, add = 1;
		for(int i = 1; i<=N; i++){
			tot += dep;
			if(amt == i){
				add *= K;
				dep++;
				amt += add;
			}
		}
		if(tot <= S){
			ans = mid;
			r = mid - 1;
		}
		else{
			l = mid + 1;
		}
	}
	if(!ans){
		cout << "No\n";
		return 0;
	}
	long long tot = 0;
	long long dep = 1, amt = 1, add = 1;
	for(int i = 1; i<=N; i++){
		tot += dep;
		if(amt == i){
			add *= K;
			dep++;
			amt += add;
		}
	}	
}
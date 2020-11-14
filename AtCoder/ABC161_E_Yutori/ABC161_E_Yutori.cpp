
// Problem : E - Yutori
// Contest : AtCoder Beginner Contest 161
// URL : https://atcoder.jp/contests/abc161/tasks/abc161_e
// Memory Limit : 1024 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N, K, C;

string s;
long long dp[200005];
long long mx[200005];
bool good[200005];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> K >> C >> s;
	for(int i = 1; i<=N; i++){
		if(s[i-1] == 'o'){
			dp[i] = 1;
			if(i >= C+1){
				dp[i] = mx[i-C-1] + 1;
			}
		}
		mx[i] = max(mx[i-1], dp[i]);
	}
	if(mx[N] == K){
		int n = N;
		while(n > 0){
			while(n > 0 && s[n-1] == 'x'){
				n--;	
			}
			if(n > 0){
				good[n] = 1;
			}
			n -= C+1;
		}
		bool b = 0;
		for(int i = N; i; i--){
			if(mx[i] != mx[i+1]){
				b = 0;
			}
			if(good[i]){
				b = 1;
			}
			good[i] = b;
		}
		int crnt = 1, cnt = 0, x = 0;
		for(int i = 1; i<=N; i++){
			if(dp[i] && dp[i] == crnt && good[i]){
				cnt++;
				x = i;
			}
			else if(dp[i] && dp[i] != crnt && good[i]){
				if(cnt == 1){
					cout << x << "\n";
				}
				crnt = dp[i];
				cnt = 1;
				x = i;
			}
		}
		if(cnt == 1){
			cout << x << "\n";
		}
	}
}
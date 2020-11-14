
// Problem : E. Dreamoon and Strings
// Contest : Codeforces - Codeforces Round #272 (Div. 2)
// URL : https://codeforces.com/contest/476/problem/E
// Memory Limit : 256 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N, M;
string s, t;
pair<int, int> dp[2005][2005];
int lps[505];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> s >> t;
	N = s.size(), M = t.size();
	for(int i = 1, j = 0; i<M; ){
		if(t[i] == t[j]){
			lps[i++] = ++j;
		}
		else if(j == 0){
			i++;
		}
		else{
			j = lps[j-1];
		}
	}
	for(int i = 0; i<N; i++){
		for(int j = 0; j<N; j++){
			if(j > i){
				break;
			}
			if(dp[i][j].second == M){
				dp[i][j].first++;
				dp[i][j].second = 0;
			}
			dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j]);
			int nidx = dp[i][j].second;
			while(1){
				if(t[nidx] == s[i]){
					break;
				}
				else if(!nidx){
					nidx = -1;
					break;
				}
				else{
					nidx = lps[nidx-1];
				}
			}
			pair<int, int> temp = {dp[i][j].first, nidx+1};
			dp[i+1][j] = max(dp[i+1][j], temp);
		}
	}
	for(int j = 0; j<=N; j++){
		if(dp[N][j].second == M){
			dp[N][j].first++;
		}
		cout << dp[N][j].first << " ";
	}
}
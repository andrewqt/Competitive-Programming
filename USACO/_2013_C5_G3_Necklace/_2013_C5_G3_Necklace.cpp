#include <bits/stdc++.h>

using namespace std;

string s, t;
int lps[1005]; //represents the next character 1-indexed
int nxt[1005][30];
int dp[10005][1005];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("necklace.in", "r")){
		freopen("necklace.in", "r", stdin);
		freopen("necklace.out", "w", stdout);
	}
	cin >> s >> t;
	lps[1] = 1;
	for(int i = 2, j = 1; i<=t.size(); ){
		if(t[i-1] == t[j-1]){
			lps[i++] = ++j; 
		}
		else if(j == 1){
			lps[i++] = 1;
		}
		else{
			j = lps[j-1];
		}
	}
	for(int i = 1; i<=t.size(); i++){
		for(int c = 0; c<26;c++){
			nxt[i][c] = nxt[lps[i-1]][c];
		}
		nxt[i][t[i-1]-'a'] = i; 
	}
	for(int i = 0; i<=s.size(); i++){
		for(int j = 0; j<=t.size(); j++){
			dp[i][j] = 100000;
		}
	}
	dp[0][0] = 0;
	for(int i = 0; i<s.size(); i++){
		for(int j = 0; j<t.size(); j++){
			//cout << i << " " << j << " " << dp[i][j] << endl;
			int k = nxt[j+1][s[i]-'a'];
			//cout << i << " " << j << " " << dp[i][j] << " " << k << endl;
			dp[i+1][k] = min(dp[i+1][k], dp[i][j]);
			dp[i+1][j] = min(dp[i+1][j], dp[i][j] + 1);
		}
	}
	int ans = 100000;
	for(int j = 0; j<t.size(); j++){
		//cout << dp[s.size()][j] << " " << j << endl;
		ans = min(dp[s.size()][j], ans);
	}
	cout << ans << endl;
}
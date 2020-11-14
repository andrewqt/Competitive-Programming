#include <bits/stdc++.h>

using namespace std;

int dp[1005][1005];
int nxt[1005][1005];
bool done[1005][1005];
queue<pair<int, int>> qu;
int MOD = 2012;

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("bbreeds.in", "r")){
		freopen("bbreeds.in", "r", stdin);
		freopen("bbreeds.out", "w", stdout);
	}
	string s;
	cin >> s;
	qu.push({0, 0});
	dp[0][0] = 1;
	while(qu.size()){
		auto p = qu.front();
		qu.pop();
		dp[p.first][p.second] %= MOD;
		if(done[p.first][p.second] || p.first == s.size()){
			continue;
		}
		//cout << p.first << " " << p.second << " " << dp[p.first][p.second] << endl;		
		done[p.first][p.second] = 1;
		if(s[p.first] == '('){
			dp[p.first+1][p.second+1] += dp[p.first][p.second];
			dp[p.first+1][p.second] += dp[p.first][p.second];
			nxt[p.first+1][p.second+1] = nxt[p.first][p.second];
			nxt[p.first+1][p.second] = nxt[p.first][p.second] + 1;
			qu.push({p.first+1, p.second+1});
			qu.push({p.first+1, p.second});
		}
		else{
			if(nxt[p.first][p.second]){
				dp[p.first+1][p.second] += dp[p.first][p.second];
				nxt[p.first+1][p.second] = nxt[p.first][p.second]-1;
				qu.push({p.first+1, p.second});
			}
			if(p.second){
				dp[p.first+1][p.second-1] += dp[p.first][p.second];
				nxt[p.first+1][p.second-1] = nxt[p.first][p.second];
				qu.push({p.first+1, p.second-1});
			}
		}
	}
	cout << dp[s.size()][0] << endl;
}
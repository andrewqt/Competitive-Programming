#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> pos[3];
int pre[3][405];
int dp[3][405][405][405];
int sz[3];

int cst(int p, int t, int x1, int x2, int x3){
	int sum = 0;
	sum += max(0, pre[0][pos[t][p]] - pre[0][pos[0][x1]]);
	sum += max(0, pre[1][pos[t][p]] - pre[1][pos[1][x2]]);
	sum += max(0, pre[2][pos[t][p]] - pre[2][pos[2][x3]]);
	//cout << sum << "\n";
	return sum;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	pos[0].emplace_back(0), pos[1].emplace_back(0), pos[2].emplace_back(0);
	for(int i = 1; i<=N; i++){
		char c;
		cin >> c;
		if(c == 'R'){
			sz[0]++;
			pos[0].emplace_back(i);
		}
		else if(c == 'G'){
			sz[1]++;
			pos[1].emplace_back(i);
		}
		else{
			sz[2]++;
			pos[2].emplace_back(i);
		}
	}
	if(max({sz[0], sz[1], sz[2]}) > (N+1)/2){
		cout << -1 << "\n";
		return 0;
	}
	for(int c = 0; c<3; c++){
		for(int n : pos[c]){
			pre[c][n]++;
		}
		partial_sum(pre[c], pre[c]+N+1, pre[c]);
	}
	for(int r = 0; r<=sz[0]; r++){
		for(int g = 0; g<=sz[1]; g++){
			for(int y = 0; y<=sz[2]; y++){
				dp[0][r][g][y] = dp[1][r][g][y] = dp[2][r][g][y] = 1000000;
			}
		}
	}
	dp[0][0][0][0] = dp[1][0][0][0] = dp[2][0][0][0] = 0;
	for(int r = 0; r<=sz[0]; r++){
		for(int g = 0; g<=sz[1]; g++){
			for(int y = 0; y<=sz[2]; y++){
				if(r){
					dp[0][r][g][y] = min(dp[1][r-1][g][y], dp[2][r-1][g][y]) + cst(r, 0, r, g, y);
				}
				if(g){
					dp[1][r][g][y] = min(dp[0][r][g-1][y], dp[2][r][g-1][y]) + cst(g, 1, r, g, y);					
				}
				if(y){
					dp[2][r][g][y] = min(dp[0][r][g][y-1], dp[1][r][g][y-1]) + cst(y, 2, r, g, y);					
				}
				//cout << dp[0][r][g][y] << " " << dp[1][r][g][y] << " " << dp[2][r][g][y] << "\n";
			}
		}
	}
	cout << min({dp[0][sz[0]][sz[1]][sz[2]], dp[1][sz[0]][sz[1]][sz[2]], dp[2][sz[0]][sz[1]][sz[2]]});
}
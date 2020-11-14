
// Problem : E. Bear and Destroying Subtrees
// Contest : Codeforces - Codeforces Round #351 (VK Cup 2016 Round 3, Div. 1 Edition)
// URL : https://codeforces.com/contest/674/problem/E
// Memory Limit : 0 MB
// Time Limit : 0 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int Q, N;
const int K = 100;
int par[500005];
int dgr[500005];
long double dp[500005][105];
bool touch[500005][105];
long double pows[500005];
stack<int> stk;

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> Q;
	N = 1;
	pows[0] = 1;
	for(int d = 1; d<=500000; d++){
		pows[d] = pows[d-1] * 0.5;
		dp[d][0] = 1;
	}
	while(Q--){
		int t, n;
		cin >> t >> n;
		if(t == 1){
			N++;
			par[N] = n;
			dgr[N]++;
			//int lst = N;
			stk.push(N);
			for(int d = 1; n && d<=K; d++){
				stk.push(n);
				n = par[n];
			}
			while(1){
				n = stk.top();
				stk.pop();
				if(stk.empty()){
					break;
				}
				int s = stk.size();
				if(!touch[stk.top()][s-1]){
					dp[n][s] = 1;
					touch[n][s] = 1;
				}
				else{
					dp[n][s] /= 0.5*(1+dp[stk.top()][s-1]);
				}
			}
			for(int d = 1; par[n] && d<=K; d++){
				dp[par[n]][d] *= 0.5*(1+dp[n][d-1]);
				n = par[n];
			}
		}
		else{
			long double ret = 0;
			for(int d = 1; d<=K; d++){
				ret += (dp[n][d]-pows[dgr[n]])*d;
			}
			cout << ret << "\n";
		}
	}
}
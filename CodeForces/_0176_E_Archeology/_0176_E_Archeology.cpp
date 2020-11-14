
// Problem : E. Archaeology
// Contest : Codeforces - Croc Champ 2012 - Round 2
// URL : https://codeforces.com/problemset/problem/176/E
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N, Q;
const int B = 450;
vector<pair<int, int>> graph[100005];
vector<int> hvy;
int par[100005], wt[100005];
bool ison[100005], ishvy[100005];
long long sum[100005];

void dfs(int n){
	//sum[n] = wt[n];
	for(auto e : graph[n]){
		if(e.first != par[n]){
			par[e.first] = n;
			wt[e.first] = e.second;
			dfs(e.first);
			//sum[n] += e.second;
		}
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 1; i<N; i++){
		int a, b, v;
		cin >> a >> b >> v;
		graph[a].emplace_back(b, v);
		graph[b].emplace_back(a, v);
	}
	for(int i = 1; i<=N; i++){
		if(graph[i].size() > B){
			hvy.push_back(i);
			ishvy[i] = 1;
		}
	}
	dfs(1);
	for(int i = 1; i<=N; i++){
		if(ishvy[i]){
			vector<pair<int, int>> v;
			for(auto e : graph[i]){
				if(ishvy[e.first]){
					v.push_back(e);
				}
			}
			swap(graph[i], v);
		}
	}
	cin >> Q;
	long long tot = 0;
	while(Q--){
		char c;
		cin >> c;
		if(c == '+'){
			int n;
			cin >> n;
			ison[n] = 1;
			if(ishvy[n]){
				tot += sum[n];
				for(auto e : graph[n]){
					sum[e.first] += e.second;
				}
			}
			else{
				for(auto e : graph[n]){
					//cout << e.first << "\n";
					if(ishvy[e.first]){
						sum[e.first] += e.second;
					}
					if(ison[e.first]){
						tot += e.second;
					}
				}
			}
		}
		else if(c == '-'){
			int n;
			cin >> n;
			ison[n] = 0;
			if(ishvy[n]){
				tot -= sum[n];
				for(auto e : graph[n]){
					sum[e.first] -= e.second;
				}
			}
			else{
				for(auto e : graph[n]){
					if(ishvy[e.first]){
						sum[e.first] -= e.second;
					}
					if(ison[e.first]){
						tot -= e.second;
					}
				}
			}
		}
		else{
			cout << tot << "\n";
		}
	}
}
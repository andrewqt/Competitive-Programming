// Problem : The Order of the Fox
// Contest : DMOJ
// URL : https://dmoj.ca/problem/year2019p7
// Memory Limit : 256.000000 MB 
// Time Limit : 7000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> graph[300005];
long long dgr[300005];
long long MOD = 1e9+7;

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	for(int i = 1; i<=M; i++){
		int a, b;
		cin >> a >> b;
		graph[a].emplace_back(b);
		graph[b].emplace_back(a);
		dgr[a]++, dgr[b]++;
	}
	for(int i= 1; i<=N;i ++){
		sort(graph[i].begin(), graph[i].end());
	}
	long long ans = 0;
	for(int n = 1; n<=N; n++){
		for(const int e : graph[n]){
			if(n < e){
				continue;
			}
			long long cnt = (dgr[n]-1) * (dgr[e] - 1);
			long long tot = 0;
			if(dgr[e] < dgr[n]){
				auto ptr = graph[n].begin();
				for(int k : graph[e]){
					if(k == n){
						continue;
					}
					ptr = lower_bound(ptr, graph[n].end(), k);
					if(ptr == graph[n].end()){
						break;
					}
					int l = (*ptr == k);
					cnt -= l;
					tot += l;
				}
			}
			else{
				auto ptr = graph[e].begin();
				for(int k : graph[n]){
					if(k == e){
						continue;
					}
					ptr = lower_bound(ptr, graph[e].end(), k);
					if(ptr == graph[e].end()){
						break;
					}
					int l = (*ptr == k);
					cnt -= l;
					tot += l;
				}
			}
			ans += cnt*tot;
			ans -= (dgr[n] + dgr[e] - 4)*tot;
		}
		ans %= MOD;
	}
	cout << ans << "\n";
}
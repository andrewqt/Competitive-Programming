
// Problem : CCO '19 P3 - Winter Driving
// Contest : DMOJ
// URL : https://dmoj.ca/problem/cco19p3
// Memory Limit : 1 MB
// Time Limit : 600 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N;
long long T;
vector<int> graph[200005];
int arr[200005];
int sz[200005];
long long dp[200005];
int szt[200005];
int par[200005];
long long ans = 0;

void dfs1(int n){
	sz[n] = arr[n];
	for(int e : graph[n]){
		if(e != par[n]){
			par[e] = n;
			dfs1(e);
			sz[n] += sz[e];
		}
	}
}

void dfs2(int n, int p){
	szt[n] = arr[n];
	dp[n] = 1LL * arr[n] * (arr[n] - 1);
	for(int e : graph[n]){
		if(e != p){
			dfs2(e, n);
			szt[n] += szt[e];
			dp[n] += dp[e];
			dp[n] += 1LL * szt[e] * arr[n];
		}
	}
}

vector<int> gen(vector<int> a){
	vector<int> pos;
	for(int m = 0; m<1<<a.size(); m++){
		int crnt = 0;
		for(int n = 0; n<a.size(); n++){
			if(m>>n&1){
				crnt += a[n];
			}
		}
		pos.emplace_back(crnt);
	}	
	return pos;
}

void solve(int n){
	long long cst = (T - arr[n])*arr[n];
	cst += arr[n] * (arr[n] - 1);
	vector<int> a, b;
	for(int e : graph[n]){
		dfs2(e, n);
		cst += dp[e];
		if(a.size() == 18){
			b.emplace_back(szt[e]);
		}
		else{
			a.emplace_back(szt[e]);
		}
	}
	a = gen(a);
	b = gen(b);
	sort(b.begin(), b.end());
	for(long long m : a){
		long long k = abs((T - arr[n])/2 - m);
		int idx = lower_bound(b.begin(), b.end(), k) - b.begin();
		int lim = min(idx+2, (int) (b.size()));
		for(idx = max(0, idx-1); idx < lim; idx++){
			ans = max(ans, cst + (T-arr[n]-m-b[idx])*(m+b[idx]));
		}
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
	}	
	for(int i = 2; i<=N; i++){
		int p;
		cin >> p;
		graph[p].emplace_back(i);
		graph[i].emplace_back(p);
	}
	dfs1(1);
	T = sz[1];
	for(int i = 1; i<=N; i++){
		bool isc = T-sz[i] <= T/2;
		for(int e : graph[i]){
			if(e != par[i]){
				isc &= (sz[e] <= T/2);
			}
		}
		if(isc){
			solve(i);
		}
	}
	cout << ans << "\n";
}
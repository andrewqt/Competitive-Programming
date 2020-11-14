
// Problem : DMOPC '20 Contest 1 P5
// Contest : DMOJ
// URL : https://dmoj.ca/problem/dmopc20c1p5
// Memory Limit : 512 MB
// Time Limit : 3500 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N, Q, K;
const int D = 19;
vector<int> graph[500005];
int tbl[20][500005];
set<pair<int, int>> clr[500005];
pair<int, int> srt[500005];
int arr[500005];
int lft[500005], rht[500005], t;
int bit[500005];

void dfs(int n){
	lft[n] = ++t;
	for(int e : graph[n]){
		if(e != tbl[0][n]){
			tbl[0][e] = n;
			dfs(e);
		}
	}
	rht[n] = t;
}

void upd(int n, int v){
	while(n <= N){
		bit[n] += v;
		n += n&-n;
	}
}

int query(int n){
	int ret = 0;
	while(n){
		ret += bit[n];
		n -= n&-n;
	}
	return ret;
}

int lca(int u, int v){
	if(lft[u] <= lft[v] && rht[u] >= rht[v]){
		return u;
	}
	if(lft[v] <= lft[u] && rht[v] >= rht[u]){
		return v;
	}
	for(int d = D; d>=0; d--){
		if(!tbl[d][u] || lft[tbl[d][u]] <= lft[v] && rht[tbl[d][u]] >= rht[v]);
		else{
			u = tbl[d][u];
		}
	}
	return tbl[0][u];
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> K >> Q;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
	}
	for(int i = 1; i<N; i++){
		int a, b;
		cin >> a >> b;
		graph[a].emplace_back(b);
		graph[b].emplace_back(a);
	}
	dfs(1);
	for(int d = 1; d<=D; d++){
		for(int n = 1; n<=N; n++){
			tbl[d][n] = tbl[d-1][tbl[d-1][n]];
		}
	}
	for(int i= 1; i<=N; i++){
		srt[i] = make_pair(lft[i], i);
	}
	sort(srt+1, srt+1+N);
	for(int i = 1; i<=N; i++){
		int n = srt[i].second;
		if(clr[arr[n]].size()){
			int p = lca((*clr[arr[n]].rbegin()).second, n);
			upd(lft[p], -1);
		}
		upd(lft[n], 1);
		clr[arr[n]].insert(make_pair(lft[n], n));
	}
	while(Q--){
		int cmd, n;
		cin >> cmd >> n;
		if(cmd == 1){
			int k;
			cin >> k;
			if(1){
				auto ptr = clr[arr[n]].lower_bound(make_pair(lft[n], n));
				if(ptr != clr[arr[n]].begin()){
					auto tmp = ptr--;
					int p = lca((*tmp).second, (*ptr).second);
					upd(lft[p], 1);
					ptr = tmp;
				}
				if(ptr != --clr[arr[n]].end()){
					auto tmp = ptr++;
					int p = lca((*tmp).second, (*ptr).second);
					upd(lft[p], 1);
					ptr = tmp;
				}
			}
			if(1){
				clr[arr[n]].erase(make_pair(lft[n], n));
				auto ptr = clr[arr[n]].lower_bound(make_pair(lft[n], n));
				if(ptr != clr[arr[n]].end() && ptr != clr[arr[n]].begin()){
					auto tmp = ptr--;
					int p = lca((*tmp).second, (*ptr).second);
					upd(lft[p], -1);
				}
			}
			arr[n] = k;
			if(1){
				auto ptr = clr[arr[n]].lower_bound(make_pair(lft[n], n));
				if(ptr != clr[arr[n]].begin() && ptr != clr[arr[n]].end()){
					auto tmp = ptr--;
					int p = lca((*tmp).second, (*ptr).second);
					upd(lft[p], 1);
					ptr = tmp;
				}
				if(ptr != clr[arr[n]].end()){
					int p = lca(n, (*ptr).second);
					upd(lft[p], -1);
				}
				if(ptr != clr[arr[n]].begin()){
					--ptr;
					int p = lca(n, (*ptr).second);
					upd(lft[p], -1);
				}
			}
			clr[arr[n]].insert(make_pair(lft[n], n));
		}
		else{
			cout << query(rht[n]) - query(lft[n] - 1) << "\n";
		}
	}
}
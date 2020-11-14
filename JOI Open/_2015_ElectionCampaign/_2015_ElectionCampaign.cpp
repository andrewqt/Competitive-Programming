#include <bits/stdc++.h>

using namespace std;

struct node{
	int l, r;
	long long tot, lzy;
};

int N, M;
vector<int> graph[100005];
vector<pair<long long, pair<int, int>>> v[100005];
int par[20][100005];
int lft[100005], rht[100005], t=0;
node seg[1000000];
long long dp[100005];
long long tot[100005];

void pd(int idx){
	if(seg[idx].lzy){
		seg[2*idx].lzy += seg[idx].lzy;
		seg[2*idx+1].lzy += seg[idx].lzy;
		seg[2*idx].tot += seg[idx].lzy;
		seg[2*idx+1].tot += seg[idx].lzy;
		seg[idx].lzy = 0;
	}
}

void build(int l, int r, int idx){
	seg[idx].l = l, seg[idx].r = r;
	if(l == r){
		return;
	}
	int mid = l+r>>1;
	build(l, mid, 2*idx);
	build(mid+1, r, 2*idx+1);
}

void upd(int l, int r, long long v, int idx){
	if(seg[idx].l == l && seg[idx].r == r){
		seg[idx].lzy += v;
		seg[idx].tot += v;
		return;
	}
	pd(idx);
	int mid = seg[idx].l + seg[idx].r >> 1;
	if(r <= mid){
		upd(l, r, v, 2*idx);
	}
	else if(l > mid){
		upd(l, r, v, 2*idx+1);
	}
	else{
		upd(l, mid, v, 2*idx);
		upd(mid+1, r, v, 2*idx+1);
	}
}

long long get(int p, int idx = 1){
	if(seg[idx].l == seg[idx].r){
		return seg[idx].tot;
	}
	pd(idx);
	get(p, 2*idx + (p > seg[idx].l + seg[idx].r >> 1));
}

int lca(int u, int v){
	if(lft[v] <= lft[u] && rht[u] <= rht[v]){
		return v;
	}
	if(lft[u] <= lft[v] && rht[v] <= rht[u]){
		return u;
	}
	for(int d = 16; d>=0; d--){
		int n = par[d][u];
		if(!n || (lft[n] <= lft[v] && rht[v] <= rht[n])){
			
		}
		else{
			u = n;
		}
	}
	return par[0][u];
}

void dfs1(int n){
	//cout << n << " " << par[0][n] << endl;
	lft[n] = ++t;
	for(int e : graph[n]){
		if(e != par[0][n]){
			par[0][e] = n;
			dfs1(e);
		}
	}
	rht[n] = ++t;
}

void dfs2(int n){
	for(int e : graph[n]){
		if(e != par[0][n]){
			dfs2(e);
			dp[n] += dp[e];
		}
	}
	tot[n] = dp[n];
	for(auto q : v[n]){
		if(q.second.first != n && q.second.second != n){
			dp[n] = max(dp[n], get(lft[q.second.first]) + get(lft[q.second.second]) + tot[n] + q.first);
		}
		else if(q.second.first != n || q.second.second != n){
			//cout << get(q.second.first == n ? lft[q.second.second] : lft[q.second.first]) << " " << tot[n] + q.first << "\n";
			dp[n] = max(dp[n], get(q.second.first == n ? lft[q.second.second] : lft[q.second.first]) + tot[n] + q.first);
		}
		else{
			dp[n] = max(dp[n], tot[n] + q.first);
		}
	}
	upd(lft[n], rht[n], -dp[n]+tot[n], 1);
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 1; i<N; i++){
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	dfs1(1);
	for(int d = 1; d<=16; d++){
		for(int n = 1; n<=N; n++){
			par[d][n] = par[d-1][par[d-1][n]];
		}
	}
	build(1, 2*N, 1);
	cin >> M;
	while(M--){
		int a, b, c;
		cin >> a >> b >> c;
		v[lca(a, b)].push_back({c,{a, b}});
		//cout << lca(a, b) << endl;
	}
	dfs2(1);
	for(int i = 1; i<=N; i++){
		//cout << dp[i] << " " << tot[i] << "\n";
	}
	cout << dp[1] << "\n";
}
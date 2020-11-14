
// Problem : Bob's Delivery Trip
// Contest : DMOJ
// URL : https://dmoj.ca/problem/oly20practice115
// Memory Limit : 512 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

struct SegmentTree{
	struct Node{
		int l, r;
		long long mx, lzy;
		int n;
	};
	vector<Node> seg;
	SegmentTree(){
		
	}
	SegmentTree(int N){
		seg.resize(4*N+2);
	}
	void build(int l, int r, int idx){
		seg[idx].l = l;
		seg[idx].r = r;
		if(l == r){
			return;
		}
		int mid = l+r>>1;
		build(l, mid, 2*idx);
		build(mid+1, r, 2*idx+1);
	}
	void pd(int idx){
		if(seg[idx].lzy){
			seg[2*idx].mx += seg[idx].lzy;
			seg[2*idx].lzy += seg[idx].lzy;
			seg[2*idx+1].mx += seg[idx].lzy;
			seg[2*idx+1].lzy += seg[idx].lzy;
			seg[idx].lzy = 0;
		}
	}
	void pu(int idx){
		if(make_pair(seg[2*idx].mx, -seg[2*idx].n) > make_pair(seg[2*idx+1].mx, -seg[2*idx+1].n)){
			seg[idx].mx = seg[2*idx].mx;
			seg[idx].n = seg[2*idx].n;
		}
		else{
			seg[idx].mx = seg[2*idx+1].mx;
			seg[idx].n = seg[2*idx+1].n;
		}
	}
	void upd(int l, int r, long long v, int idx){
		if(seg[idx].l == l && seg[idx].r == r){
			seg[idx].mx += v;
			seg[idx].lzy += v;
			return;
		}
		pd(idx);
		int mid = (seg[idx].l + seg[idx].r) >> 1;
		if(r <= mid){
			upd(l, r, v, 2*idx);
		}
		else if(l > mid){
			upd(l, r, v, 2*idx+1);
		}
		else{
			upd(l, mid, v, 2*idx);
			upd(mid+1,r, v, 2*idx+1);
		}
		pu(idx);
	}
	void add(int p, int n, int idx){
		if(seg[idx].l == seg[idx].r){
			seg[idx].n = n;
			return;
		}
		int mid = (seg[idx].l + seg[idx].r) >> 1;
		if(p <= mid){
			add(p, n, 2*idx);
		}
		else{
			add(p, n, 2*idx+1);
		}
		pu(idx);
	}
	pair<long long, int> query(int l, int r, int idx){
		if(l > r){
			return make_pair(LLONG_MIN, 0);
		}
		if(seg[idx].l == l && seg[idx].r == r){
			return make_pair(seg[idx].mx, -seg[idx].n);
		}
		pd(idx);
		int mid = (seg[idx].l + seg[idx].r) >> 1;
		if(r <= mid){
			return query(l, r, 2*idx);
		}
		else if(l > mid){
			return query(l, r, 2*idx+1);
		}
		else{
			return max(query(l, mid, 2*idx), query(mid+1, r, 2*idx+1));
		}
	}
};

int N, Q;
long long arr[100005];
vector<pair<int, long long>> graph[100005];
int lft[20][100005], rht[20][100005], t;
long long wt[20][100005];
long long dist[20][100005];
int cent[20][100005];
int cdep[100005];
bool done[100005];
int sz[100005];
SegmentTree tree[100005];

void dfs1(int n, int p){
	sz[n] = 1;
	for(auto e : graph[n]){
		if(e.first != p && !done[e.first]){
			dfs1(e.first, n);
			sz[n] += sz[e.first];
		}
	}
}

void dfs2(int n, int d, int p){
	lft[d][n] = ++t;
	tree[cent[d][n]].upd(lft[d][n], lft[d][n], arr[n] - dist[d][n], 1);
	tree[cent[d][n]].add(lft[d][n], n, 1);
	for(auto e : graph[n]){
		if(!done[e.first] && e.first != p){
			dist[d][e.first] = dist[d][n] + e.second;
			cent[d][e.first] = cent[d][n];
			wt[d][e.first] = e.second;
			dfs2(e.first, d, n);
		}
	}
	rht[d][n] = t;
}

void solve(int n, int d){
	dfs1(n, 0);
	int crntsz = sz[n];
	while(1){
		int hvy = 0;
		for(auto e : graph[n]){
			if(!done[hvy] && sz[hvy] < sz[e.first] && sz[e.first] < sz[n]){
				hvy = e.first;
			}
		}
		if((sz[hvy]<<1) <= crntsz){
			break;
		}
		n = hvy;
	}
	done[n] = 1;
	t = 0;
	cent[d][n] = n;
	cdep[n] = d;
	sz[n] = crntsz;	
	tree[n] = SegmentTree(sz[n]);
	tree[n].build(1, sz[n], 1);
	dfs2(n, d, 0);
	for(auto e : graph[n]){
		if(!done[e.first]){
			solve(e.first, d+1);
		}
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> Q;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
	}
	for(int i = 1; i<N; i++){
		int a, b;
		long long w;
		cin >> a >> b >> w;
		graph[a].emplace_back(b, w);
		graph[b].emplace_back(a, w);
	}
	solve(1, 0);
	int crnt = 1;
	while(Q--){ 
		int c;
		cin >> c;
		if(c == 1){
			int n;
			long long x;
			cin >> n >> x;
			for(int d = cdep[n]; d >= 0; d--){
				tree[cent[d][n]].upd(lft[d][n], lft[d][n], x - arr[n], 1);
			}
			arr[n] = x;
		}
		else{
			int a, b;
			long long x;
			cin >> a >> b >> x;
			for(int d = min(cdep[a], cdep[b]); d >= 0; d--){
				if(dist[d][a] < dist[d][b]){
					swap(a, b);
				}
				tree[cent[d][a]].upd(lft[d][a], rht[d][a], -(x - wt[d][a]), 1);
				wt[d][a] = x;
			}
		}		
		auto bst = tree[crnt].query(2, sz[crnt], 1);
		for(int d = cdep[crnt]-1; d>=0; d--){
			int c = cent[d][crnt];
			auto p = max(tree[c].query(1, lft[d][crnt]-1, 1), tree[c].query(rht[d][crnt]+1, sz[c], 1));
			auto n = tree[c].query(lft[d][crnt], lft[d][crnt], 1);
			if(bst.first < p.first + n.first - arr[crnt]){
				bst.first = p.first + n.first - arr[crnt];
				bst.second = p.second;
			}
			else if(bst.first == p.first + n.first - arr[crnt]){
				bst.second = max(bst.second, p.second);
			}
		}
		cout << (crnt = -bst.second) << " ";
	}
}
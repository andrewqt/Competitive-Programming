#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>

using namespace std;

int arr[200005];

struct line{
	mutable long long m, b, p;
	inline bool operator < (const line &l) const{
		return m < l.m;
	}
	inline bool operator < (long long x) const {
		return p < x;
	}
};

struct LineContainer : multiset<line, less<>>{
	const long long inf = LLONG_MAX/2;
	inline bool inter(iterator x, iterator y){
		if(y == end()){
			x->p = inf;
			return 0;
		}
		if(x->m == y->m){
			x->p = (x->b <= y->b ? -inf : inf);
		}
		else{
			long long db = (y->b - x->b), dm = (x->m - y->m);
			x->p = db/dm - ((db^dm) < 0 && db%dm);
		}
		return x->p >= y->p;
	}
	inline void add(long long m, long long b){
		auto z = insert({m, b, 0}), y = z++, x = y;
		while(inter(y, z)){
			z = erase(z);
		}
		if(x != begin() && inter(--x, y)){
			inter(x, y = erase(y));
		}
		while((y = x) != begin() && (--x)->p >= y->p){
			inter(x, erase(y));
		}
	}
	inline long long query(long long n){
		auto l = *lower_bound(n);
		return l.m * n + l.b;
	}
};

struct ExtremaSegTree{
	struct node{
		int l, r;
		long long mx;
		int idx;
	};
	node seg[1000000];
	inline void build(int l, int r, int idx, bool b = 0){
		seg[idx].l = l, seg[idx].r = r;
		seg[idx].idx = l;
		seg[idx].mx = 0;
		if(l == r){
			if(b){
				seg[idx].mx = -arr[l];
			}
			return;
		}
		int mid = (l+r)>>1;
		build(l, mid, 2*idx, b);
		build(mid+1, r, 2*idx+1, b);
		if(b){
			seg[idx].mx = max(seg[2*idx].mx, seg[2*idx+1].mx);
			//cout << seg[idx].mx << "\n";
			if(seg[2*idx].mx == seg[idx].mx){
				seg[idx].idx = seg[2*idx].idx;
			}
			else{
				seg[idx].idx = seg[2*idx+1].idx;
			}
		}
	}	
	inline void upd(int p, long long v, int idx){
		if(seg[idx].l == seg[idx].r){
			if(v > 0){
				seg[idx].mx = max(seg[idx].mx, v);
			}
			else{
				seg[idx].mx = v;
			}
			return;
		}
		int mid = (seg[idx].l + seg[idx].r) >> 1;
		if(p <= mid){
			upd(p, v, 2*idx);
		}
		else{
			upd(p, v, 2*idx+1);
		}
		seg[idx].mx = max(seg[2*idx].mx, seg[2*idx+1].mx);
		//cout << seg[idx].mx << "\n";
		if(seg[2*idx].mx == seg[idx].mx){
			seg[idx].idx = seg[2*idx].idx;
		}
		else{
			seg[idx].idx = seg[2*idx+1].idx;
		}
	}
	inline long long query(int l, int r, int idx, bool b = 1){
		//cout << l << " " << r << " " << seg[idx].l << " " << seg[idx].r << endl;
		if(seg[idx].l == l && seg[idx].r == r){
			return b ? seg[idx].mx : seg[idx].idx;
		}
		int mid = (seg[idx].l + seg[idx].r)>>1;
		if(r <= mid){
			return query(l, r, 2*idx, b);
		}
		else if(l > mid){
			return query(l, r, 2*idx+1, b);
		}
		else{
			if(!b){
				int lft = query(l, mid, 2*idx, b), rht = query(mid+1, r, 2*idx+1, b);
				//cout << arr[lft] << " " << arr[rht] << endl;
				return (-arr[lft] >= -arr[rht] ? lft : rht);
			}
			return max(query(l, mid, 2*idx, b), query(mid+1, r, 2*idx+1, b));
		}
	}
};

struct LineSegTree{
	struct node{
		int l, r;
		LineContainer lc;
	};
	node seg[1000000];
	inline void build(int l, int r, int idx){
		seg[idx].l = l, seg[idx].r = r;
		seg[idx].lc.clear();
		//assert(seg[idx].lc.empty());
		if(l == r){
			return;
		}
		int mid = (l+r)>>1;
		build(l, mid, 2*idx);
		build(mid+1, r, 2*idx+1);
	}
	inline void upd(int p, long long m, long long b, int idx){
		seg[idx].lc.add(m, b);
		if(seg[idx].l == seg[idx].r){
			return;
		}
		if(p <= (seg[idx].l + seg[idx].r)>>1){
			upd(p, m, b, 2*idx);
		}
		else{
			upd(p, m, b, 2*idx+1);
		}
	}
	inline long long query(int l, int r, long long x, int idx){
		//cout << l << " " << r << " " << seg[idx].l << " " << seg[idx].r << endl;
		if(seg[idx].l == l && seg[idx].r == r){
			return seg[idx].lc.query(x);
		}
		int mid = (seg[idx].l + seg[idx].r)>>1;
		if(r <= mid){
			return query(l, r, x, 2*idx);
		}
		else if(l > mid){
			return query(l, r, x, 2*idx+1);
		}
		else{
			return max(query(l, mid, x, 2*idx), query(mid+1, r, x, 2*idx+1));
		}
	}
};

int N, Q;
long long pre[200005], ans[200005];
pair<int, int> qu[200005], srt[200005];
pair<pair<int, int>, int> qus[200005];
vector<pair<pair<int, int>, long long>> upd;
vector<int> graph[200005];
set<int> st;
LineSegTree seg;
ExtremaSegTree mxseg;
int par[200005], sz[200005], hvy[200005], top[200005], id[200005], dep[200005], lim[200005], t;
int tbl[20][200005];

void dfs(int n){
	sz[n] = 1;
	hvy[n] = 0;
	for(int e : graph[n]){
		par[e] = n;
		dep[e] = dep[n] + 1;
		dfs(e);
		sz[n] += sz[e];
		hvy[n] = (hvy[n] && sz[hvy[n]] > sz[e] ? hvy[n] : e);
	}
}

void hld(int n, int k){
	//cout << n << " " << k << " " << t << endl;
	id[n] = t++;
	top[n] = k;
	seg.upd(id[n], arr[n], -arr[n]*pre[par[n]], 1);	
	if(hvy[n]){
		hld(hvy[n], k);
	}
	//cout << "hld: " << n << " " << arr[n] << " " << -arr[n]*pre[par[n]] << " " << pre[par[n]] << "\n";
	for(int e : graph[n]){
		if(e != par[n] && hvy[n] != e){
			hld(e, e);
		}
	}
}

long long query(int n, int lim){
	long long ret = 0;
	long long x = pre[n];
	while(top[n] > lim){
		//cout << "inhere: " << n << " " << lim << " " << id[top[n]] << " " << id[n] << endl;
		ret = max(ret, seg.query(id[top[n]], id[n], x, 1));
		n = par[top[n]];
	}
	if(n > lim){
		int nxt = n;
		for(int d = 17; d>=0; d--){
			if(tbl[d][nxt] > lim){
				nxt = tbl[d][nxt];
			}
		}
		//cout << " " << nxt << " " << n << " " << id[nxt] << " " << id[n] << endl;
		ret = max(ret, seg.query(id[nxt], id[n], x, 1));
	}
	return ret;
}

void solve(){
	seg.build(1, N, 1);
	st.clear();
	st.insert(0);
	sort(srt+1, srt+1+N);
	for(int i = 1; i<=N; i++){
		auto ptr = --st.upper_bound(srt[i].second);
		graph[*ptr].push_back(srt[i].second);
		st.insert(srt[i].second);
	}
	dfs(0);
	hld(0, 0);
	for(int i = 1; i<=N; i++){
		tbl[0][i] = par[i];
		//cout << par[i] << "\n";
	}
	for(int d = 1; d<18; d++){
		for(int i = 1; i<=N; i++){
			tbl[d][i] = tbl[d-1][tbl[d-1][i]];
		}
	}
	for(int q = 1; q<=Q; q++){
		//cout << qu[q].first << " " << qu[q].second << endl;
		//int lim = mxseg.query(qu[q].first, qu[q].second, 1, 0);
		//cout << lim << endl;
		ans[q] = max(ans[q], query(qu[q].second, lim[q]));
		ans[q] = max(ans[q], (pre[qu[q].second] - pre[qu[q].first-1])*arr[lim[q]]);
	}
	for(int i = 0; i<=N; i++){
		graph[i].clear();
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> Q;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
		srt[i].first = arr[i];
		srt[i].second = i;
		pre[i] = pre[i-1] + arr[i];
	}
	st.insert(0), st.insert(N+1);
	sort(srt+1, srt+1+N);
	for(int i = 1; i<=N; i++){
		auto ptr = st.lower_bound(srt[i].second);
		int r = *ptr - 1, l = *(--ptr) + 1;
		//cout << l << " " << r << " " << srt[i].second << " " << (pre[r] - pre[l-1]) * srt[i].first << "\n";
		upd.push_back({{r, l}, (pre[r]-pre[l-1])*srt[i].first});
		st.insert(srt[i].second);
	}
	for(int i = 1; i<=Q; i++){
		cin >> qu[i].first >> qu[i].second;
		qus[i] = {{qu[i].second, qu[i].first}, i};
	}
	sort(qus+1, qus+1+Q);
	sort(upd.begin(), upd.end());
	int idx = 0;
	mxseg.build(1, N, 1);
	for(int q = 1; q<=Q; q++){
		while(idx < (int) (upd.size()) && upd[idx].first.first <= qus[q].first.first){
			//cout << "index: " << upd[idx].second << "\n";
			mxseg.upd(upd[idx].first.second, upd[idx].second, 1);
			idx++;
		}
		ans[qus[q].second] = mxseg.query(qus[q].first.second, qus[q].first.first, 1);
	}
	mxseg.build(1, N, 1, 1);
	for(int q = 1; q<=Q; q++){
		lim[q] = mxseg.query(qu[q].first, qu[q].second, 1, 0);
	}
	solve();
	for(int i = 1; i<=N; i++){
		srt[i].second = N-srt[i].second+1;
		arr[srt[i].second] = srt[i].first;
	}
	for(int i = 1; i<=N; i++){
		pre[i] = pre[i-1] + arr[i];
	}
	for(int q = 1; q<=Q; q++){
		swap(qu[q].first, qu[q].second);
		qu[q].first = N - qu[q].first + 1;
		qu[q].second = N - qu[q].second + 1;
		lim[q] = N - lim[q] + 1;
	}
	t = 0;
	solve();
	for(int q = 1; q<=Q; q++){
		cout << ans[q] << "\n";
	}
}
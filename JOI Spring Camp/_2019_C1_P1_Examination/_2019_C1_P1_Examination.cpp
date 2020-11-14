#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

struct node{
	int l, r;
	tree<int, null_type, greater_equal<int>, rb_tree_tag, tree_order_statistics_node_update> st;
};

int N, Q;
pair<int, int> arr[100005];
int ans[100005];
int a[100005], b[100005], c[100005];
pair<int, int> qu[100005];
node seg[300005];
vector<int> cmp;

inline void build(int l, int r, int idx){
	seg[idx].l = l, seg[idx].r = r;
	if(l == r){
		return;
	}
	int mid = l+r>>1;
	build(l, mid, 2*idx);
	build(mid+1, r, 2*idx+1);
}

inline void upd(int p, int v, int idx){
	seg[idx].st.insert(v);
	if(seg[idx].l == seg[idx].r){
		return;
	}
	upd(p, v, 2*idx + (p > seg[idx].l + seg[idx].r >> 1));
}

inline int query(int l, int r, int k, int idx){
	if(seg[idx].l == l && seg[idx].r == r){
		return seg[idx].st.order_of_key(k-1);
	}
	int mid = seg[idx].l + seg[idx].r >> 1;
	if(r <= mid){
		return query(l, r, k, 2*idx);
	}
	else if(l > mid){
		return query(l, r, k, 2*idx+1);
	}
	else{
		return query(l, mid, k, 2*idx) + query(mid+1, r, k, 2*idx+1);
	}
}

bool comp1(pair<int, int> a, pair<int, int> b){
	return a.first+a.second > b.first+b.second;
}

int getidx(int v){
	return lower_bound(cmp.begin(), cmp.end(), v) - cmp.begin() + 1;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> Q;
	for(int i= 1; i<=N; i++){
		cin >> arr[i].first >> arr[i].second;
		cmp.push_back(arr[i].first);
	}
	sort(arr+1, arr+1+N, comp1);
	sort(cmp.begin(), cmp.end());
	cmp.erase(unique(cmp.begin(), cmp.end()), cmp.end());
	int M = cmp.size();
	for(int q = 1; q<=Q; q++){
		cin >> a[q] >> b[q] >> c[q];		
		qu[q] = {c[q], q};
	}
	build(1, M, 1);
	sort(qu+1, qu+1+N, greater<pair<int, int>>());
	int idx = 1;
	for(int q = 1; q<=Q; q++){
		while(idx <= N && arr[idx].first + arr[idx].second >= qu[q].first){
			upd(getidx(arr[idx].first), arr[idx].second, 1);
			idx++;
		}
		int n = qu[q].second;
		if(getidx(a[n]) > M){
			continue;
		}
		ans[n] = query(getidx(a[n]), M, b[n], 1);
	}
	for(int q = 1; q<=Q; q++){
		cout << ans[q] << "\n";
	}
}

// Problem : COCI '09 Contest 3 #5 Patuljci
// Contest : DMOJ
// URL : https://dmoj.ca/problem/coci09c3p5
// Memory Limit : 32 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

struct node{
	int l, r, m, v;
};

int N, C;
node seg[1500000];
int arr[300005];
vector<int> c[10005];

inline pair<int, int> pu(pair<int, int> lft, pair<int, int> rht){
	if(lft.first == rht.first){
		return {lft.first, lft.second + rht.second};
	}
	else if(rht.second > lft.second){
		return {rht.first, rht.second - lft.second};
	}
	else{
		return {lft.first, lft.second - rht.second};
	}
}

inline void build(int l, int r, int idx){
	seg[idx].l = l, seg[idx].r = r;
	if(l == r){
		seg[idx].m = arr[l];
		seg[idx].v = 1;
		return;
	}
	int mid = l+r>>1;
	build(l, mid, 2*idx);
	build(mid+1, r, 2*idx+1);
	auto p = pu(make_pair(seg[2*idx].m, seg[2*idx].v), make_pair(seg[2*idx+1].m, seg[2*idx+1].v));
	seg[idx].m = p.first;
	seg[idx].v = p.second;
}

inline pair<int, int> query(int l, int r, int idx){
	if(seg[idx].l == l && seg[idx].r == r){
		return make_pair(seg[idx].m, seg[idx].v);
	}
	int mid = seg[idx].l + seg[idx].r >> 1;
	if(r <= mid){
		return query(l, r, 2*idx);
	}
	else if(l > mid){
		return query(l, r, 2*idx+1);
	}
	else{
		return pu(query(l, mid, 2*idx), query(mid+1, r, 2*idx+1));
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> C;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
		c[arr[i]].emplace_back(i);
	}
	build(1, N, 1);
	int Q;
	cin >> Q;
	while(Q--){
		int l, r;
		cin >> l >> r;
		auto p = query(l, r, 1);
		int n = p.first;
		int rng = upper_bound(c[n].begin(), c[n].end(), r) - lower_bound(c[n].begin(), c[n].end(), l);
		if(2*rng > r-l+1){
			cout << "yes " << n << "\n";
		}
		else{
			cout << "no\n";
		}
	}
}
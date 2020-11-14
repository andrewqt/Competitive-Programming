
// Problem : F. Phoenix and Memory
// Contest : Codeforces - Codeforces Round #638 (Div. 2)
// URL : https://codeforces.com/contest/1348/problem/F
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

struct SegTree{
	struct node{
		int l, r;
		set<pair<int, int>> st;
	};
	node seg[1000000];
	void build(int l, int r, int idx){
		seg[idx].l = l, seg[idx].r = r;
		if(l == r){
			return;
		}
		int mid = l+r>>1;
		build(l, mid, 2*idx);
		build(mid+1, r, 2*idx+1);
	}
	void upd(int p, pair<int, int> v, int idx, bool rem){
		if(rem){
			seg[idx].st.erase(v);
		}
		else{
			seg[idx].st.erase(v);
		}
		if(seg[idx].l == seg[idx].r){
			return;
		}
		upd(p, v, 2*idx+(p > seg[idx].l + seg[idx].r >> 1), rem);
	}
	pair<int, int> query(int l, int r, int idx){
		if(seg[idx].l == l && seg[idx].r == r){
			return seg[idx].size() ? *seg[idx].begin() : {INT_MAX/2, 0};
		}
		int mid = seg[idx].l + seg[idx].r >> 1;
		if(r <= mid){
			return query(l, r, 2*idx);
		}
		else if(l > mid){
			return query(l, r, 2*idx+1);
		}
		else{
			return min(query(l, mid, 2*idx), query(mid+1, r, 2*idx+1));
		}
	}
};

int N;
int lft[200005], rht[200005];
int ans1[200005], ans2[200005];
int diff[200005];
SegTree segl, segr;
set<int> st;
queue<int> qu;

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	segl.build(1, N, 1);
	segr.build(1, N, 1);
	for(int i =1; i<=N; i++){
		cin >> lft[i] >> rht[i];
		st.insert(i);
		if(rht[i] - lft[i]){
			segl.upd(lft[i], {rht[i], i}, 1, 0);
			segr.upd(rht[i], {-lft[i], i}, 1, 0);
		}
		else{
			qu.push(lft[i]);
		}
	}
	while(qu.size()){
		int n = qu.front();
		qu.pop();
		
	}
}
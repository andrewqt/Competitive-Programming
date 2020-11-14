#pragma GCC optimize("Ofast","unroll-loops","omit-frame-pointer","inline")
#pragma GCC option("arch=native","tune=native","no-zero-upper")
#pragma GCC target("avx2")

// Problem : CCO '18 P5 - Boring Lectures (Online Version)
// Contest : DMOJ
// URL : https://dmoj.ca/problem/cco18p5online
// Memory Limit : 512 MB
// Time Limit : 1400 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

struct node{
	int l, r;
	pair<int, int> mx;
};

int N, K, Q;
node seg[4000005];
int arr[4000005];
priority_queue<pair<int, int>> pq;

void pu(int idx){
	if(seg[2*idx].mx.first > seg[2*idx+1].mx.first){
		seg[idx].mx = seg[2*idx].mx;
	}
	else{
		seg[idx].mx = seg[2*idx+1].mx;
	}
	//seg[idx].mx = max(seg[2*idx].mx, seg[2*idx+1].mx);
}

inline void build(int l, int r, int idx){
	seg[idx].l = l, seg[idx].r = r;
	if(l == r){
		seg[idx].mx.first = arr[l];
		seg[idx].mx.second = l;
		return;
	}
	int mid = (l+r)/2;
	build(l, mid, 2*idx);
	build(mid+1, r, 2*idx+1);
	pu(idx);
}

inline void upd(int p, int v, int idx){
	if(seg[idx].l == seg[idx].r){
		seg[idx].mx.first = v;
		return;
	}
	upd(p, v, 2*idx + (p > (seg[idx].l + seg[idx].r)/2));
	pu(idx);
}

inline pair<int, int> query(int l, int r, int idx){
	if(l > r){
		return {0, 0};
	}
	if(seg[idx].l == l && seg[idx].r == r){
		return seg[idx].mx;
	}
	int mid = seg[idx].l + seg[idx].r >> 1;
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

inline bool add(int i){
	if(query(max(1, i-K), min(i+K, N), 1).second == i){
		auto p = max(query(max(1, i-K), i-1, 1), query(i+1, min(i+K, N), 1));
		pq.push({p.first+arr[i], i});
		return 1;
	}
	return 0;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> K >> Q;
	for(int i =1 ; i<=N; i++){
		cin >> arr[i];
	}
	build(1, N, 1);
	K--;
	for(int i = 1; i<=N; i++){
		add(i);
	}
	int lst = pq.top().first;
	cout << lst << "\n";
	while(Q--){
		int n, x;
		cin >> n >> x;
		n ^= lst, x ^= lst;
		upd(n, x, 1);
		arr[n] = x;
		//cout << "here" << endl;
		if(!add(n)){
			if(n != 1){
				add(query(max(1, n-K), n-1, 1).second);
			}
			if(n != N){
				add(query(n+1, min(N, n+K), 1).second);
			}
		}
		while(1){
			auto p = pq.top();
			int i = p.second;
			if(max(query(max(1, i-K), i-1, 1), query(i+1, min(i+K, N), 1)).first + arr[i] == p.first){
				cout << (lst = p.first) << "\n";
				break;
			}
			else{
				pq.pop();
			}
		}
	}
	
}
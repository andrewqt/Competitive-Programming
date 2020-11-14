
// Problem : D. Buy Low Sell High
// Contest : Codeforces - MemSQL Start[c]UP 3.0 - Round 2 (onsite finalists)
// URL : https://codeforces.com/problemset/problem/865/D
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

struct node{
	int l, r, v, lzy;
};

int N;
node seg[1500000];
int arr[300005];
pair<int, int> srt[300005];

void pd(int idx){
	if(seg[idx].lzy){
		seg[2*idx].v += seg[idx].lzy;
		seg[2*idx+1].v += seg[idx].lzy;
		seg[2*idx].lzy += seg[idx].lzy;
		seg[2*idx+1].lzy += seg[idx].lzy;
		seg[idx].lzy = 0;
	}
}

void build(int l, int r, int idx){
	seg[idx].l = l, seg[idx].r = r;
	seg[idx].lzy = 0;
	if(l == r){
		seg[idx].v = l;
		return;
	}
	int mid = l+r>>1;
	build(l, mid, 2*idx);
	build(mid+1, r, 2*idx+1);
	seg[idx].v = min(seg[2*idx].v, seg[2*idx+1].v);
}

void upd(int l, int r, int v, int idx){
	if(seg[idx].l == l && seg[idx].r == r){
		seg[idx].v += v;
		seg[idx].lzy += v;
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
	seg[idx].v = min(seg[2*idx].v, seg[2*idx+1].v);
}

long long solve(){
	for(int i = 1; i<=N; i++){
		srt[i] = {arr[i], i};
	}
	sort(srt+1, srt+1+N, greater<pair<int, int>>());
	build(1, N, 1);
	long long ret = 0;
	//int cnt = 0;
	for(int i = 1; i<=N; i++){
		int k = srt[i].second;
		upd(k, N, -2, 1);
		if(seg[1].v < 0){
			upd(k, N, 1, 1);
		}
		else{
			cout << srt[i].second << " " << srt[i].first << "\n";
			ret += srt[i].first;
			//cnt++;
		}
	}
	cout << "\n";
	return ret;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
	}
	long long ans = solve();
	for(int i = 1; i<=N; i++){
		arr[i] *= -1;
	}
	for(int i = 1; i<=N/2; i++){
		swap(arr[i], arr[N-i+1]);
	}
	ans += solve();
	cout << ans;
}
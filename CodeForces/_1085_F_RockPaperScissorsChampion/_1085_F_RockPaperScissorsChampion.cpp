
// Problem : F. Rock-Paper-Scissors Champion
// Contest : Codeforces - Technocup 2019 - Elimination Round 4
// URL : https://codeforces.com/problemset/problem/1085/F
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

struct Node{
	int l, r;
	int cnt[3];
};

int N, Q;
Node seg[1000000];
int arr[200005];

int getidx(char c){
	if(c == 'R'){
		return 0;
	}
	else if(c == 'S'){
		return 1;
	}
	else{
		return 2;
	}
}

void pu(int idx){
	for(int i = 0; i<3; i++){
		seg[idx].cnt[i] = 0;
		if(seg[2*idx].cnt[i] || seg[2*idx].cnt[(i+1)%3]){
			seg[idx].cnt[i] = seg[2*idx+1].cnt[i];
		}
		if(seg[2*idx+1].cnt[i] || seg[2*idx+1].cnt[(i+1)%3]){
			seg[idx].cnt[i] += seg[2*idx].cnt[i];
		}
	}
}

void build(int l, int r, int idx){
	seg[idx].l = l;
	seg[idx].r = r;
	if(l == r){
		seg[idx].cnt[arr[l]] = 1;
		return;
	}
	int mid = seg[idx].l + seg[idx].r >> 1;
	build(l, mid, 2*idx);
	build(mid+1, r, 2*idx+1);
	pu(idx);
}

void upd(int p, int v, int idx){
	if(seg[idx].l == seg[idx].r){
		fill(seg[idx].cnt, seg[idx].cnt+3, 0);
		seg[idx].cnt[arr[p]] = 1;
		return;
	}
	int mid = seg[idx].l + seg[idx].r >> 1;
	if(p <= mid){
		upd(p, v, 2*idx);
	}
	else {
		upd(p, v, 2*idx+1);
	}
	pu(idx);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> Q;
	for(int i = 1; i<=N; i++){
		char c;
		cin >> c;
		arr[i] = getidx(c);
	}
	build(1, N, 1);
	cout << accumulate(seg[1].cnt, seg[1].cnt+3, 0) << "\n";
	while(Q--){
		int p;
		char c;
		cin >> p >> c;
		arr[p] = getidx(c);
		upd(p, c, 1);
		cout << accumulate(seg[1].cnt, seg[1].cnt+3, 0) << "\n";
	}
}
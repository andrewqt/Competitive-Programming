
// Problem : COCI '14 Contest 2 #6 Norma
// Contest : DMOJ
// URL : https://dmoj.ca/problem/coci14c2p6
// Memory Limit : 64 MB
// Time Limit : 1400 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

struct node{
	int msk[8]; //0 = lep, 1 mn, 2 mx
	int lzy[3];
};

int N;
node seg[1500005];
const long long MOD = 1000000000;
stack<pair<int, int>> mn, mx;

long long add(long long a, long long b){
	return (a+b)%MOD;
}

long long mult(long long a, long long b){
	return a*b%MOD;
}

void pu(int idx){
	for(int m = 0; m<8; m++){
		seg[idx].msk[m] = add(seg[2*idx].msk[m], seg[2*idx+1].msk[m]);
	}
}

void calc(int v, int t, int idx){
	for(int m = 1; m<8; m++){
		if(m>>t&1){
			seg[idx].msk[m] = mult(v, seg[idx].msk[m^(1<<t)]);
			//cout << m << " " << v << " " << t << "\n";
			//cout << seg[idx].msk[m] << "\n";
		}
	}
	seg[idx].lzy[t] = v;
}

void pd(int idx){
	if(seg[idx].lzy[1]){
		calc(seg[idx].lzy[1], 1, 2*idx);
		calc(seg[idx].lzy[1], 1, 2*idx+1);
		seg[idx].lzy[1] = 0;
	}
	if(seg[idx].lzy[2]){
		calc(seg[idx].lzy[2], 2, 2*idx);
		calc(seg[idx].lzy[2], 2, 2*idx+1);
		seg[idx].lzy[2] = 0;
	}
}

void build(int l, int r, int idx){
	if(l == r){
		seg[idx].msk[0] = 1;
		seg[idx].msk[1] = l-1;
		return;
	}
	int mid = l+r>>1;
	build(l, mid, 2*idx);
	build(mid+1, r, 2*idx+1);
	pu(idx);
}

void upd(int sl, int sr, int l, int r, int v, int t, int idx){
	if(sl == l && sr == r){
		calc(v, t, idx);
		return;
	}
	pd(idx);	
	int mid = sl + sr >> 1;
	if(r <= mid){
		upd(sl, mid, l, r, v, t, 2*idx);
	}
	else if(l > mid){
		upd(mid+1, sr, l, r, v, t, 2*idx+1);
	}
	else{
		upd(sl, mid, l, mid, v, t, 2*idx);
		upd(mid+1, sr, mid+1, r, v, t, 2*idx+1);
	}
	pu(idx);
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	build(1, N, 1);
	mn.push({0, 0});
	mx.push({1000000000, 0});
	long long ans = 0;
	for(int i = 1; i<=N; i++){
		int v;
		cin >> v;
		//cout << v << endl;
		while(mn.top().first >= v){
			//cout << mn.top().first << endl;
			mn.pop();
		}
		while(mx.top().first <= v){
			//cout << mx.top().first << endl;
			//cout << mx.size() << endl;
			mx.pop();
		}
		//cout << "reach" << endl;
		upd(1, N, mn.top().second+1, i, v, 1, 1);
		upd(1, N, mx.top().second+1, i, v, 2, 1);
		ans = add(ans, add(mult(i, seg[1].msk[6]) - seg[1].msk[7], MOD));
		mn.push({v, i});
		mx.push({v, i});
	}
	cout << ans << "\n";
}
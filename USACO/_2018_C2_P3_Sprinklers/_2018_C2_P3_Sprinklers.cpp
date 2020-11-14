
// Problem : Problem 3. Sprinklers
// Contest : USACO 2018 January Contest, Platinum
// URL : http://www.usaco.org/index.php?page=viewproblem2&cpid=794
// Memory Limit : 256.000000 MB 
// Time Limit : 4000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

struct node{
	int l, r;
	long long rng, sum, v, c, lzy;
};

int N;
node seg[400010];
long long MOD = 1e9+7;
int lft[400005], rht[400005];

long long add(long long a, long long b){
	return (a+b)%MOD;
}

long long mult(long long a, long long b){
	return a*b%MOD;
}

void pd(int idx){
	if(seg[idx].lzy){
		seg[2*idx].lzy += seg[idx].lzy;
		seg[2*idx+1].lzy += seg[idx].lzy;
		seg[2*idx].c += mult(seg[idx].lzy, seg[2*idx].rng);
		seg[2*idx+1].c += mult(seg[idx].lzy, seg[2*idx+1].rng);
		seg[2*idx].v += seg[idx].lzy*(seg[2*idx].rng)*(seg[2*idx].sum)/2;
		seg[2*idx+1].v += seg[idx].lzy*(seg[2*idx+1].rng)*(seg[2*idx+1].sum)/2;
		seg[2*idx].v %= MOD;
		seg[2*idx+1].v %= MOD;
		seg[2*idx].c %= MOD;
		seg[2*idx+1].c %= MOD;
		seg[idx].lzy = 0;
	}
}

void build(int l, int r, int idx){
	seg[idx].l = l, seg[idx].r = r;	
	seg[idx].rng = r-l+1;
	seg[idx].sum = r+l;
	if(l == r){
		return;
	}
	int mid = l+r>>1;
	build(l, mid, 2*idx);
	build(mid+1, r, 2*idx+1);
}

void upd(int l, int r, int idx){
	if(seg[idx].l == l && seg[idx].r == r){
		seg[idx].v += seg[idx].rng*(seg[idx].sum)/2;
		seg[idx].c += seg[idx].rng;
		seg[idx].lzy++;
		seg[idx].v %= MOD;
		seg[idx].c %= MOD;
		return;
	}
	int mid = seg[idx].l + seg[idx].r >> 1;
	pd(idx);
	if(r <= mid){
		upd(l, r, 2*idx);
	}
	else if(l > mid){
		upd(l, r, 2*idx+1);
	}
	else{
		upd(l, mid, 2*idx);
		upd(mid+1, r, 2*idx+1);
	}
	seg[idx].c = add(seg[2*idx].c, seg[2*idx+1].c);
	seg[idx].v = add(seg[2*idx].v, seg[2*idx+1].v);
}

pair<long long, long long> query(int l, int r, int idx){
	if(seg[idx].l == l && seg[idx].r == r){
		return {seg[idx].c, seg[idx].v};
	}
	pd(idx);
	int mid = seg[idx].l + seg[idx].r >> 1;	
	if(r <= mid){
		return query(l, r, 2*idx);
	}
	else if(l > mid){
		return query(l, r, 2*idx+1);
	}
	else{
		auto p = query(l, mid, 2*idx);
		auto q = query(mid+1, r, 2*idx+1);
		p.first = add(p.first, q.first);
		p.second = add(p.second, q.second);
		return p;
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("sprinklers.in", "r")){
		freopen("sprinklers.in", "r", stdin);
		freopen("sprinklers.out", "w", stdout);
	}
	cin >> N;
	for(int i = 1; i<=N; i++){
		int a, b;
		cin >> a >> b;
		lft[a] = rht[a] = b;
	}
	for(int i = N-2; i>=0; i--){
		rht[i] = max(rht[i], rht[i+1]);
	}
	for(int i = 1; i<N; i++){
		lft[i] = min(lft[i], lft[i-1]);
	}
	build(0, N, 1);
	long long ans = 0;
	for(int i = N-1; i>=0; i--){
		if(i != N-1 && lft[i] < rht[i+1]){
			auto x = query(lft[i]+1, rht[i+1], 1);
			//cout << " " << x.first << " " << x.second << endl;
			ans += x.second - mult(lft[i], x.first);
			ans %= MOD;
			if(ans < 0){
				ans += MOD;
			}
		}
		if(i && lft[i-1] < rht[i]){
			upd(lft[i-1]+1, rht[i], 1);
		}
		//cout << i << " " << ans << endl;
	}
	cout << ans << endl;
}
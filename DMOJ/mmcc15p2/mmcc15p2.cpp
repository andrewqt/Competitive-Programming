// Problem : Akame
// Contest : DMOJ
// URL : https://dmoj.ca/problem/mmcc15p2
// Memory Limit : 1 MB
// Time Limit : 7000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

struct Line{
	mutable long double m, b;
	mutable long long p;
	mutable int A, B, C;
	bool operator < (const Line & l) const {
		//cout << (m < l.m) << " " << (-1LL*A*l.B > -1LL*l.A*B) << "\n";
		//cout << m << " " <<  << "\n";
		if((B^l.B) < 0){
			return -1LL*A*l.B > -1LL*l.A*B;
		}
		return -1LL*A*l.B < -1LL*l.A*B;
	}
	bool operator < (const long long x) const{
		return p < x;
	}
};

//const long double EPS = 1e-15;

struct LineContainer : multiset<Line, less<>> {
	const long long oo = LLONG_MAX/2;
	long long divd(long double a, long double b){
		long long ret = floor(a/b);
		if(a/b != floor(a/b)){
			if(a < 0 && b > 0){
				ret--;
			}
			if(a > 0 && b < 0){
				ret--;
			}
		}
		return ret;
	}
	bool inter(iterator x, iterator y){
		if(y == end()){
			x->p = oo;
			return 0;
		}
		if(1LL*x->A*y->B == 1LL*x->B*y->A){
			x->p = x->b > y->b ? oo : -oo;
		}
		else{
			x->p = divd((y->b - x->b), (x->m - y->m));
		}
		return x->p >= y->p;
	}
	void add(int A, int B, int C){
		auto z = insert({-1.0*A/B, 1.0*C/B, 0, A, B, C}), y = z++, x = y;
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
	long double query(long long x){
		auto l = *lower_bound(x);
		return l.m * x + l.b;
	}
};

int N, Q;
int A[500005], B[500005], C[500005];
vector<pair<int, pair<int, int>>> qu[25];
int x[500005], y[500005], ans[500005];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> Q;
	for(int i = 1; i<=N; i++){
		cin >> A[i] >> B[i] >> C[i];
	}
	for(int q = 1; q<=Q; q++){
		cin >> x[q] >> y[q];
		ans[q] = -1;
		qu[0].push_back({q, {1, N}});
	}
	for(int lvl = 0; lvl<25; lvl++){
		LineContainer mx, mn;
		sort(qu[lvl].begin(), qu[lvl].end(), [](auto p, auto q){
			return p.second < q.second;
		});
		int lst = 0;
		for(auto p : qu[lvl]){
			int l = p.second.first, r = p.second.second;
			int mid = l+r>>1;
			//cout << lvl << " " << p.first << " " << l << " " << r << endl;
			while(lst < mid){
				lst++;
				mx.add(A[lst], B[lst], C[lst]);
				mn.add(-A[lst], B[lst], -C[lst]);
			}
			int q = p.first;
			//cout << -mn.query(x[q]) << " " << mx.query(x[q]) << "\n";
			//assert(-mn.query(x[q]) <= mx.query(x[q]));
			if(y[q] >= -mn.query(x[q]) && y[q] <= mx.query(x[q])){
				ans[q] = mid;
				if(l <= mid-1){
					qu[lvl+1].push_back({q, {l, mid-1}});
				}
			}
			else if(r >= mid+1){
				qu[lvl+1].push_back({q, {mid+1, r}});
			}
		}
	}
	for(int q = 1; q<=Q; q++){
		cout << ans[q] << "\n";
	}
}
//#include <game.h>
#include <bits/stdc++.h>

using namespace std;

mt19937 rando (chrono::steady_clock::now().time_since_epoch().count());

struct snode {
	pair<int, int> p;
	long long x, g;
	int pri;
	snode * c[2];
	snode (int pp1, int pp2, long long v){
		p = {pp1, pp2};
		x = g = v;
		pri = uniform_int_distribution<int>(INT_MIN, INT_MAX) (rando);
		c[0] = c[1] = NULL;
	}
};

struct bnode {
	snode * rt;
	bnode * lft, * rht;
	bnode(){
		lft = rht = NULL;
		rt = NULL;
	}
};

bnode * rt;
int N;

long long getg(snode * n){
	return n ? n->g : 0;
}

snode * pu(snode * n){
	n->g = __gcd(__gcd(getg(n->c[0]), getg(n->c[1])), n->x);
	return n;
}

pair<snode *, snode *> split(snode * n, pair<int, int> k){
	if(!n){
		return {n, n};
	}
	if(n->p >= k){
		auto p = split(n->c[0], k);
		n->c[0] = p.second;
		return {p.first, pu(n)};
	}
	else{
		auto p = split(n->c[1], k);
		n->c[1] = p.first;
		return {pu(n), p.second};
	}
}

pair<snode *, snode*> split(snode * n, int x, int y){
	return split(n, {x, y});
}

snode * merge(snode * lft, snode * rht){
	if(!lft){
		return rht;
	}
	if(!rht){
		return lft;
	}
	if(lft->pri > rht->pri){
		lft->c[1] = merge(lft->c[1], rht);
		return pu(lft);
	}
	else{
		rht->c[0] = merge(lft, rht->c[0]);
		return pu(rht);
	}
}

bnode * upd(int l, int r, int x, int y, long long v, bnode * n){
	//cout << l << " " << r << "\n";
	if(n == NULL){
		n = new bnode();
	}
	auto p = split(n->rt, y, x);
	auto q = split(p.second, y, x+1);
	n->rt = merge(p.first, merge(new snode(y, x, v), q.second));
	if(l == r){
		return n;
	}
	int mid = l+r>>1;
	if(x <= mid){
		n->lft = upd(l, mid, x, y, v, n->lft);
	}
	else{
		n->rht = upd(mid+1, r, x, y, v, n->rht);
	}
	return n;
}

long long query(int sl, int sr, int ql, int qr, int qsl, int qsr, bnode * n){
	if(n == NULL || sr < ql || sl > qr){
		return 0;
	}
	//cout << " " << sl << " " << sr << "\n";
	if(ql <= sl && qr >= sr){
		//cout << " " << n->rt->g << "\n";
		auto p = split(n->rt, qsl, -1);
		auto q = split(p.second, qsr+1, -1);
		long long ret = getg(q.first);
		n->rt = merge(p.first, merge(q.first, q.second));
		return ret;
	}
	int mid = sl+sr>>1;
	return __gcd(query(sl, mid, ql, qr, qsl, qsr, n->lft), query(mid+1, sr, ql, qr, qsl, qsr, n->rht));
}

void init(int R, int C){
	N = R-1;
}

void update(int r, int c, long long v){
	rt = upd(0, N, r, c, v, rt);
}

long long calculate(int r, int c, int sr, int sc){
	return query(0, N, r, sr, c, sc, rt);
}

/*
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	init(2, 3);
	update(0, 0, 20);
	update(0, 2, 15);
	update(1, 1, 12);
	cout << calculate(0, 0, 0, 2) << "\n";
	cout << calculate(0, 0, 1, 1) << "\n";
	update(0, 1, 6);
	update(1, 1, 14);
	cout << calculate(0, 0, 0, 2) << "\n";
	cout << calculate(0, 0, 1, 1) << "\n";
}
*/

/*
int main(){
	init(1000000000, 1000000000);
	update(0, 0, 1000000000000000000);
	update(999999999, 999999999, 1);
	cout << calculate(0, 0, 999999999, 999999999) << "\n";
}
*/
/*
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int A, B, Q;
	cin >> A >> B >> Q;
	init(A, B);
	while(Q--){
		int k;
		cin >> k;
		if(k == 1){
			int r, c;
			long long v;
			cin >> r >> c >> v;
			update(r, c, v);
		}
		else{
			int r1, c1, r2, c2;
			cin >> r1 >> c1 >> r2 >> c2;
			cout << calculate(r1, c1, r2, c2) << "\n";
		}
	}
}
*/
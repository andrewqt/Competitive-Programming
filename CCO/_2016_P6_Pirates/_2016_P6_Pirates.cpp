
// Problem : CCO '16 P6 - Pirates
// Contest : DMOJ
// URL : https://dmoj.ca/problem/cco16p6
// Memory Limit : 256 MB
// Time Limit : 7000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

mt19937 g1(chrono::steady_clock::now().time_since_epoch().count());

struct node{
	long long v;
	long long s;
	int pri;
	long long lzy;
	bool lzyr;
	int sz;
	node * c[2];
	node (long long _v){
		s = v = _v;
		pri = uniform_int_distribution<int> (INT_MIN, INT_MAX) (g1);
		lzy = 0;
		c[0] = c[1] = NULL;
		sz = 1;
	}
};

int N;
long long K;
//vector<pair<long long, int>> v;
node * treap;

long long getsum(node * n){
	return n ? n->s : 0;
}

int getsz(node * n){
	return n ? n->sz : 0;
}

node * pd(node * n){
	if(n->lzyr){
		for(int k = 0; k<2; k++){
			if(n->c[k]){
				n->c[k]->lzyr = 1;
				n->c[k]->lzy = 0;
				n->c[k]->v = n->c[k]->s = 0;
			}
		}
	}
	if(n->lzy){
		for(int k = 0; k<2; k++){
			if(n->c[k]){
				n->c[k]->lzy += n->lzy;
				n->c[k]->s += n->lzy * n->c[k]->sz;
				n->c[k]->v += n->lzy;
			}
		}
	}
	n->lzy = 0;
	n->lzyr = 0;
	return n;
}

node * pu(node * n){
	n->sz = getsz(n->c[0]) + getsz(n->c[1]) + 1;
	n->s = n->v + getsum(n->c[0]) + getsum(n->c[1]);
	return n;
}

pair<node *, node *> split(node * n, long long k){
	if(!n){
		return {n, n};
	}
	n = pd(n);
	if(n->v >= k){
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

pair<node *, node *> splitsz(node * n, int k){
	if(!n){
		return {n, n};
	}
	n = pd(n);
	if(getsz(n->c[0]) >= k){
		auto p = splitsz(n->c[0], k);
		n->c[0] = p.second;
		return {p.first, pu(n)};
	}
	else{
		auto p = splitsz(n->c[1], k-getsz(n->c[0])-1);
		n->c[1] = p.first;
		return {pu(n), p.second};
	}
}

node * merge(node * lft, node * rht){
	if(!lft){
		return rht;
	}
	if(!rht){
		return lft;
	}
	lft = pd(lft);
	rht = pd(rht);
	node * n;
	if(lft->pri > rht->pri){
		lft->c[1] = merge(lft->c[1], rht);
		n = lft;
	}
	else{
		rht->c[0] = merge(lft, rht->c[0]);
		n = rht;
	}
	return pu(n);
}

void traverse(node * n){
	if(!n){
		return;
	}
	pd(n);
	traverse(n->c[0]);
	cout << n->v << " ";
	traverse(n->c[1]);
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> K;
	for(int i = 1; i<=N; i++){
		int k;
		cin >> k;
		k--;
		auto p = splitsz(treap, k);
		//cout << getsz(p.first) << endl;
		//cout << getsum(p.first) << endl;
		if(getsz(p.first) == k && getsum(p.first) + k<= K){
			//cout << getsum(p.first) << " " << k << endl;
			long long val = K - getsum(p.first) - k;
			//cout << "here" << endl;
			if(p.first){
				//p.first = pd(p.first);
				//cout << " " << p.first->s << " " << p.first->sz << "\n";
				p.first->s += p.first->sz;
				p.first->lzy++;
				p.first->v++;
			}
			if(p.second){
				p.second->lzyr = 1;
				p.second->lzy = 0;
				p.second->s = p.second->v = 0;
			}
			//cout << "reach" << endl;
			//cout << getsum(p.first) << " " << k << endl;
			treap = merge(p.second, p.first);			
			auto q = split(treap, val);
			treap = merge(q.first, merge(new node(val), q.second));
			//cout << getsum(p.first) << "\n";
			cout << val << "\n";
		}
		else{
			treap = merge(p.first, p.second);
			treap = merge(new node(-1), treap);
			cout << -1 << "\n";
		}
		//traverse(treap);
		//cout << "\n";
	}
}
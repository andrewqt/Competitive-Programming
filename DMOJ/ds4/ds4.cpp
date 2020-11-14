#include <bits/stdc++.h>

using namespace std;

mt19937 g1(chrono::steady_clock::now().time_since_epoch().count());

//bqi343's treap
struct node{
	int val;
	int pri, sz;
	node * c[2];
	node (int v){
		val = v;
		pri = uniform_int_distribution<int>(INT_MIN, INT_MAX)(g1);
		sz = 1;
		c[0] = c[1] = NULL;
	}
};

int N, Q;
int arr[100005];
node * treap = NULL;

int getsz(node * n){
	return n?n->sz : 0;
}

node * pu(node * n){
	n->sz = 1 + getsz(n->c[0]) + getsz(n->c[1]);
	return n;
}

pair<node *, node *> split(node * n, int v){
	//cout << v << endl;
	if(!n){
		return {n, n};
	}
	if(n->val >= v){
		auto p = split(n->c[0], v);
		n->c[0] = p.second;
		return {p.first, pu(n)};
	}
	else{
		auto p = split(n->c[1], v);
		n->c[1] = p.first;
		return {pu(n), p.second};
	}
}

pair<node *, node *> splitsz(node * n, int s){
	//cout << getsz(n) << endl;
	if(!n){
		return {n, n};
	}
	if(getsz(n->c[0]) >= s){
		auto p = splitsz(n->c[0], s);
		n->c[0] = p.second;
		return {p.first, pu(n)};
	}
	else{
		auto p = splitsz(n->c[1], s-getsz(n->c[0])-1);
		n->c[1] = p.first;
		return {pu(n), p.second};
	}
}

node * merge(node * l, node * r){
	if(!l){
		return r;
	}
	if(!r){
		return l;
	}
	node * t;
	if(l->pri > r->pri){
		l->c[1] = merge(l->c[1], r);
		t = l;
	}
	else{
		r->c[0] = merge(l, r->c[0]);
		t = r;
	}
	return pu(t);
}

node * insert(node * x, int v){
	auto p = split(x, v);
	return merge(merge(p.first, new node(v)), p.second);
}

node * remove(node * x, int v){
	auto p = split(x, v);
	auto q = splitsz(p.second, 1);
	if(q.first && q.first->val == v){
		return merge(p.first, q.second);
	}
	return merge(p.first, merge(q.first, q.second));
}

int getval(node * n, int k){
	assert(getsz(n) >= k);
	auto p = splitsz(n, k-1);
	auto q = splitsz(p.second, 1);
	assert(getsz(p.first) == k-1);
	int ret = q.first->val;
	n = merge(p.first, merge(q.first, q.second));
	return ret;
}

int getpos(node * n, int k){
	auto p = split(n, k);
	auto q = splitsz(p.second, 1);
	int ret = -1;
	if(q.first && q.first->val == k){
		ret = getsz(p.first)+1;
	}
	n = merge(p.first, merge(q.first, q.second));
	return ret;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> Q;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
		treap = insert(treap, arr[i]);
	}
	int lst = 0;
	while(Q--){
		char c;
		int n;
		cin >> c >> n;
		n ^= lst;
		if(c == 'I'){
			treap = insert(treap, n);
		}
		else if(c == 'R'){
			treap = remove(treap, n);
		}
		else if(c == 'S'){
			cout << (lst = getval(treap, n)) << "\n";
		}
		else{
			cout << (lst = getpos(treap, n)) << "\n";
		}
	}
	for(int i = 1; i<=getsz(treap); i++){
		cout << getval(treap, i) << " ";
	}
	cout << "\n";
}
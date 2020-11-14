#include <bits/stdc++.h>

using namespace std;

mt19937 g1(chrono::steady_clock::now().time_since_epoch().count());

struct node{
	int lzy, pri, mx, a, v;	
	node * c[2];
	node(int a_, int b_){
		pri = uniform_int_distribution<int>(INT_MIN, INT_MAX)(g1);
		a = a_;
		v = mx = b_ - a_;
		lzy = 0;
		c[0] = c[1] = NULL;
	}
};

int N;
vector<pair<long long, long long>> v;
long long arr[200005], cst[200005];
int lst[200005];
node * treap;
int ans;

node * pd(node * n){
	if(n->lzy){
		for(int i = 0; i<2; i++){
			if(n->c[i]){
				n->c[i]->lzy += n->lzy;
				n->c[i]->mx += n->lzy;
				n->c[i]->v += n->lzy;
				n->c[i]->a -= n->lzy;
			}
		}
		n->lzy = 0;
	}
	return n;
}

node * pu(node * n){
	//cout << "enter" << endl;
	n->mx = n->v;
	if(n->c[0]){
		n->mx = max(n->mx, n->c[0]->mx);
	}	
	if(n->c[1]){
		n->mx = max(n->mx, n->c[1]->mx);
	}
	return n;
}

pair<node *, node *> split(node * n, int k){
	if(!n){
		return {n, n};
	}
	n = pd(n);
	if(n->a >= k){
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

node * merge(node * lft, node * rht){
	//cout << "here" << endl;
	if(!lft){
		return rht;
	}
	if(!rht){
		return lft;
	}
	//cout << "here again" << endl;
	lft = pd(lft);
	rht = pd(rht);
	//cout << "continuing here" << endl;
	node * t;
	if(lft->pri > rht->pri){
		lft->c[1] = merge(lft->c[1], rht);	
		t = lft;
	}
	else{
		rht->c[0] = merge(lft, rht->c[0]);
		t = rht;
	}
	//cout << "bad" << endl;
	return pu(t);
}

node * query(node * n, int i){
	auto p = split(n, arr[i]);
	assert(p.first);
	lst[i] = p.first->mx + arr[i] + cst[i];
	ans = max(lst[i], ans);
	p.first->mx++;
	p.first->lzy++;
	p.first->v++;
	p.first->a--;
	return merge(p.first, p.second);
}

node * insert(node * n, int a, int b){
	auto p = split(n, a);
	//cout << "split" << endl;
	return merge(p.first, merge(new node(a, b), p.second));
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("boarding.in", "r")){
		freopen("boarding.in", "r", stdin);
		freopen("boarding.out", "w", stdout);
	}
	cin >> N;
	for(int i = 1; i<=N; i++){
		cin >> arr[i] >> cst[i];
	}
	treap = insert(treap, 0, 0);
	for(int i = N; i; i--){
		//cout << i << endl;
		treap = query(treap, i);
		//cout << i << endl;
		treap = insert(treap, arr[i]-1, lst[i]);
		//cout << i << endl;
	}
	cout << ans << "\n";
}
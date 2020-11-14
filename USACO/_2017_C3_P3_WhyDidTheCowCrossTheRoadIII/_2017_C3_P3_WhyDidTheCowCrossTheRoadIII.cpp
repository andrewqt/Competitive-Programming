
#include <bits/stdc++.h>

using namespace std;

struct smallnode{
	int sum;
	smallnode *lft, *rht;
};

int N, K;
int pos[100005];
smallnode * seg[300005];

void build(int l, int r, int idx){
	//seg[idx].rt = new smallnode();
	//seg[idx].l = l, seg[idx].r = r;
	seg[idx] = new smallnode();
	//seg[idx].rt->l = 1, seg[idx].rt->r = N;
	//seg[idx]->lft = seg[idx]->rht = NULL;
	if(l == r){
		return;
	}
	int mid = l + r>> 1;
	build(l, mid, 2*idx);
	build(mid+1, r, 2*idx+1);
}

void smallupd(int segl, int segr, int p, int v, smallnode *n){
	if(segl == segr){
		n->sum += v;
		return;
	}
	int mid = segl + segr >>1;
	if(n->lft == NULL){
		n->lft = new smallnode();
		n->rht = new smallnode();
		/*
		n->lft->l = n->l;
		n->lft->r = mid;
		n->rht->l = mid+1;
		n->rht->r = n->r;
		*/
		//n->lft->lft = n->lft->rht = n->rht->lft = n->rht->rht = NULL;
	}
	if(p <= mid){
		if(n->lft == NULL){
			n->lft = new smallnode();
		}
		smallupd(segl, mid, p, v, n->lft);
	}
	else{
		if(n->rht == NULL){
			n->rht = new smallnode();
		}
		smallupd(mid+1, segr, p, v, n->rht);
	}
	n->sum = 0;
	if(n->lft != NULL){
		n->sum += n->lft->sum;
	}
	if(n->rht != NULL){
		n->sum += n->rht->sum;
	}
	//n->sum = n->lft->sum + n->rht->sum;
}

void bigupd(int segl, int segr, int x, int p, int v, int idx){
	smallupd(1, N, p, v, seg[idx]);
	if(segl == segr){
		return;
	}
	int mid = segl + segr >> 1;	
	if(x <= mid){
		bigupd(segl, mid, x, p, v, 2*idx);
	}
	else{
		bigupd(mid+1, segr, x, p, v, 2*idx+1);
	}
}

int smallquery(int segl, int segr, int l, int r, smallnode * n){
	if(n == NULL){
		return 0;
	}
	if(segl == l && segr == r){
		return n->sum;
	}
	int mid = (segl+segr)>>1;
	if(r <= mid){
		return smallquery(segl, mid, l, r, n->lft);
	}
	else if(l > mid){
		return smallquery(mid+1, segr, l, r, n->rht);
	}
	else{
		return smallquery(segl, mid, l, mid, n->lft) + smallquery(mid+1, segr, mid+1, r, n->rht);
	}
}

int bigquery(int segl, int segr, int l, int r, int sl, int sr, int idx){
	if(segl == l && segr == r){
		return smallquery(1, N, sl, sr, seg[idx]);
	}
	int mid = segl+segr >> 1;
	if(r <= mid){
		return bigquery(segl, mid, l, r, sl, sr, 2*idx);
	}
	else if(l > mid){
		return bigquery(mid+1, segr, l, r, sl, sr, 2*idx+1);
	}
	else{
		return bigquery(segl, mid, l, mid, sl, sr, 2*idx) + bigquery(mid+1, segr, mid+1, r, sl, sr, 2*idx+1);
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("friendcross.in", "r")){
		freopen("friendcross.in", "r", stdin);
		freopen("friendcross.out", "w", stdout);
	}
	cin >> N >> K;
	for(int i = 1; i<=N; i++){
		int n;
		cin >> n;
		pos[n] = i;
	}
	build(1, N, 1);
	long long ans = 0;
	for(int i = 1; i<=N; i++){
		int n;
		cin >> n;
		/*
		if(n-K-1 >= 1){
			ans += bigquery(1, N, pos[n], N, 1, n-K-1, 1);
		}
		if(n+K+1 <= N){
			ans += bigquery(1, N, pos[n], N, n+K+1, N, 1);
		}
		*/
		ans += bigquery(1, N, pos[n], N, 1, N, 1);
		ans -= bigquery(1, N, pos[n], N, max(1, n-K), min(n+K, N), 1);
		//cout << pos[r[i]] << " " << r[i] << endl;
		//cout << ans << endl;
		bigupd(1, N, pos[n], n, 1, 1);
	}
	cout << ans << endl;
}
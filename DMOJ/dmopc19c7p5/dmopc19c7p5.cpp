// Problem : DMOPC '19 Contest 7 P5
// Contest : DMOJ
// URL : https://dmoj.ca/problem/dmopc19c7p5
// Memory Limit : 128 MB
// Time Limit : 3000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

struct event{
	int pl, pr, vl, vr, idx, typ;
};

int N;
int arr[500005];
int bit[500005];
long long ans[500005];
event lst[1500005];

void upd(int n, int v){
	while(n <= N){
		bit[n] += v;
		n += n&-n;
	}
}

int query(int n){
	int ret = 0;
	while(n){
		ret += bit[n];
		n -= n&-n;
	}
	return ret;
}

void solve(int l, int r, vector<int> * v){
	//cout << "here" << endl;
	int mid = l+r>>1;
	vector<int> lft, rht;
	for(auto it = v->begin(); it != v->end(); it++){
		auto e = lst[*it];
		//cout << e.typ << endl;
		if(e.typ == 0){
			if(e.pl <= l && e.pr >= r){
				ans[e.idx] += query(e.vr) - query(e.vl-1);
			}
			else if(e.pr <= mid){
				lft.push_back(*it);
			}
			else if(e.pl > mid){
				rht.push_back(*it);
			}
			else{
				lft.push_back(*it);
				rht.push_back(*it);
			}
		}
		else{
			upd(arr[e.idx], 1);
			if(e.idx <= mid){
				lft.push_back(*it);
			}
			else{
				rht.push_back(*it);
			}
		}
	}
	for(auto it = v->begin(); it != v->end(); it++){
		auto e = lst[*it];
		if(e.typ){
			upd(arr[e.idx], -1);
		}
	}
	if(l == r){
		return;
	}
	solve(l, mid, &lft);
	solve(mid+1, r, &rht);
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i=1; i<=N; i++){
		cin >> arr[i];
	}
	vector<int> v;
	int tot = 0;
	for(int i = 1; i<=N; i++){
		int idx;
		cin >> idx;
		if(idx != 1 && arr[idx] < N){
			lst[++tot] = {1, idx-1, arr[idx]+1, N, i, 0};
			v.push_back(tot);
		}
		if(idx != N && arr[idx] != 1){
			lst[++tot] = {idx+1, N, 1, arr[idx]-1, i, 0};
			v.push_back(tot);
		}
		lst[++tot] = {0, 0, 0, 0, idx, 1};
		v.push_back(tot);
	}
	solve(1, N, &v);
	partial_sum(ans, ans+1+N, ans);
	for(int i = 1; i<=N; i++){
		cout << ans[i] << "\n";
	}
}
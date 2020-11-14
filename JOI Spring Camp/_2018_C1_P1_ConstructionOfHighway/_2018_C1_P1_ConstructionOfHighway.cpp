#include <bits/stdc++.h>
 
using namespace std;
 
int N, M;
int arr[100005];
int a[100005], b[100005];
vector<int> graph[100005];
int par[100005], top[100005], sz[100005], dep[100005], id[100005], hvy[100005], rng[100005], tim;
int bit[100005];
vector<int> cmp;
set<pair<int, int>> st;
 
void dfs(int n){
	sz[n] = 1;
	for(int e : graph[n]){
		par[e] = n;
		dep[e] = dep[n] + 1;
		dfs(e);
		sz[n] = sz[e] + 1;
		hvy[n] = sz[hvy[n]] < sz[e] ? e : hvy[n];
	}
}
 
void hld(int n, int t){
	top[n] = t;
	id[n] = ++tim;
	rng[id[t]] = tim;
	if(hvy[n]){
		hld(hvy[n], t);
	}
	for(int e : graph[n]){
		if(hvy[n] != e){
			hld(e, e);
		}
	}
}
 
void upd(int n, int v){
	while(n <= M){
		bit[n] = (v ? bit[n] + v : 0);
		n += n&-n;
	}
}
 
int sum(int n){
	int ret = 0;
	while(n){
		ret += bit[n];
		n -= n&-n;
	}
	return ret;
}
 
long long query(int n){
	vector<int> clr;
	int value = arr[n];
	long long ret = 0;
	bool fst = 1;
	while(n){
		//cout << n << " " << par[top[n]] << endl;
		vector<pair<int, int>> v;
		vector<pair<int, int>> rem;
		int lft = id[top[n]], rht = id[n];
		if(fst){
			rht = id[par[n]];
		}
		int lst = lft-1;
		for(auto it = st.lower_bound({lft, 0}); it != st.end() && lft <= rht; it++){
			//cout << st.size() << endl;
			auto p = *it;
			if(p.first <= rht){
				rem.push_back(p);
			}
			int amt = min(p.first, rht) - lst;
			v.push_back({p.second, amt});
			clr.push_back(p.second);
			if(p.first >= rht){
				break;
			}
			lst = min(p.first, rht);
		}
		reverse(v.begin(), v.end());
		for(auto p : v){
			ret += sum(p.first-1)*p.second;
			upd(p.first, p.second);
		}
		for(auto p : rem){
			st.erase(p);
		}
		if(fst){
			/*
			if(top[n] == n){
				st.insert({id[par[n]], value});
			}
			*/
			st.insert({id[n], value});
		}
		else{
			st.insert({rht, value});
		}
		n = par[top[n]];
		fst = 0;
	}
	for(int n : clr){
		upd(n, 0);
	}
	return ret;
}
 
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
		cmp.push_back(arr[i]);
	}
	sort(cmp.begin(), cmp.end());
	cmp.erase(unique(cmp.begin(), cmp.end()), cmp.end());
	for(int i = 1; i<=N; i++){
		arr[i] = lower_bound(cmp.begin(), cmp.end(), arr[i]) - cmp.begin() + 1;
	}
	M = cmp.size();
	for(int i = 1; i<N; i++){
		cin >> a[i] >> b[i];
		graph[a[i]].push_back(b[i]);
	}
	dfs(1);
	hld(1, 1);
	st.insert({1, arr[1]});
	for(int i = 1; i<N; i++){
		cout << query(b[i]) << "\n";
	}
}
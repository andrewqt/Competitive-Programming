
// Problem : Problem 2. Switch Grass
// Contest : USACO 2017 US Open Contest, Platinum
// URL : http://www.usaco.org/index.php?page=viewproblem2&cpid=745
// Memory Limit : 256.000000 MB 
// Time Limit : 4000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int N, M, K, Q;
vector<pair<int, int>> graph[200005];
int par[200005];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int wt[200005];
map<int, multiset<int>> mp[200005];
multiset<pair<int, int>> ms[200005];
multiset<int> bst;
int clr[200005];
int crnt[200005];
bool used[200005];

void add(int i){
	crnt[i] = 0;
	if(ms[i].empty()){
		return;
	}
	if((*ms[i].begin()).second != clr[i]){
		crnt[i] = (*ms[i].begin()).first;
	}
	else if(ms[i].size() > 1){
		crnt[i] = (*++ms[i].begin()).first;
	}	
	if(crnt[i]){
		bst.insert(crnt[i]);
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("grass.in", "r")){
		freopen("grass.in", "r", stdin);
		freopen("grass.out", "w", stdout);
	}
	cin >> N >> M >> K >> Q;
	for(int i = 1; i<=M; i++){
		int a, b, l;
		cin >> a >> b >> l;
		graph[a].push_back({l, b});
		graph[b].push_back({l, a});
	}
	pq.push({0, 1});
	fill(wt+2, wt+2+N, INT_MAX);
	while(pq.size()){
		auto p = pq.top();
		pq.pop();
		int n = p.second;
		if(used[n]){
			continue;
		}
		used[n] = 1;
		for(auto e : graph[n]){
			if(!used[e.second] && wt[e.second] > e.first){
				wt[e.second] = e.first;
				par[e.second] = n;
				pq.push(e);
			}
		}
	}
	for(int i = 1; i<=N; i++){
		cin >> clr[i];
	}
	for(int i = 1; i<=N; i++){
		if(par[i]){
			mp[par[i]][clr[i]].insert(wt[i]);
		}
	}
	for(int i = 1; i<=N; i++){
		for(auto p : mp[i]){
			ms[i].insert({*p.second.begin(), p.first});
		}
		add(i);
	}
	while(Q--){
		int n, c;
		cin >> n >> c;
		if(par[n]){
			if(crnt[par[n]]){
				bst.erase(bst.lower_bound(crnt[par[n]]));
			}
			ms[par[n]].erase({*mp[par[n]][clr[n]].begin(), clr[n]});
			mp[par[n]][clr[n]].erase(mp[par[n]][clr[n]].find(wt[n]));
			if(*mp[par[n]][clr[n]].begin()){
				ms[par[n]].insert({*mp[par[n]][clr[n]].begin(), clr[n]});
			}
			clr[n] = c;
			if(*mp[par[n]][clr[n]].begin()){
				ms[par[n]].erase({*mp[par[n]][clr[n]].begin(), clr[n]});
			}
			mp[par[n]][clr[n]].insert(wt[n]);
			ms[par[n]].insert({*mp[par[n]][clr[n]].begin(), clr[n]});
			add(par[n]);
		}
		if(crnt[n]){
			bst.erase(bst.lower_bound(crnt[n]));
		}
		clr[n] = c;
		add(n);
		cout << *bst.begin() << "\n";
	}
}
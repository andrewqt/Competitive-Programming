
// Problem : C. Tournament
// Contest : Codeforces Round #443 (Div. 1)
// URL : https://codeforces.com/problemset/problem/878/C
// Memory Limit : 256.000000 MB 
// Time Limit : 2000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int N, K, C;
int arr[11][50005];
vector<int> graph[50005], cgraph[50005];
stack<int> stk;
int dfn[50005], low[50005], t;
bool instk[50005];
int sz[50005], typ[50005];
vector<vector<int>> cmp;
int in[50005];
int ans[50005];
queue<int> qu;

void dfs(int n){
	dfn[n] = low[n] = ++t;
	stk.push(n);
	instk[n] = 1;
	for(int e : graph[n]){
		if(!dfn[e]){
			dfs(e);
			low[n] = min(low[n], low[e]);
		}
		else if(instk[e]){
			low[n] = min(low[n], dfn[e]);
		}
	}
	if(low[n] == dfn[n]){
		vector<int> v;
		int x = 0;
		C++;
		do{
			x = stk.top();
			stk.pop();
			instk[x] = 0;
			v.push_back(x);
			sz[C]++;
			typ[x] = C;
		}
		while(n != x);
		cmp.push_back(v);
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> K;
	for(int i = 1; i<=N; i++){
		for(int k = 1; k<=K; k++){
			cin >> arr[k][i];
		}
	}
	for(int k = 1; k<=K; k++){
		vector<pair<int, int>> v;
		for(int i = 1; i<=N; i++){
			v.push_back({arr[k][i], i});
		}
		sort(v.begin(), v.end());
		for(int i = 1; i<v.size(); i++){
			graph[v[i].second].push_back(v[i-1].second);
		}
	}
	for(int i = 1; i<=N; i++){
		if(!dfn[i]){
			dfs(i);
		}
	}
	for(int c = 1; c<=C; c++){
		for(int n : cmp[c-1]){
			for(int e : graph[n]){
				in[typ[e]]++;
				cgraph[typ[n]].push_back(typ[e]);
			}
		}
	}
	long long crnt = 0;
	for(int c = 1; c<=C; c++){
		if(!in[c]){
			crnt += sz[c];
		}
	}
	for(int n = N; n; n--){
		ans[n] = crnt;
		sz[typ[n]]--;
		if(!in[typ[n]]){
			crnt--;
		}
		if(!in[typ[n]] && !sz[typ[n]]){
			qu.push(typ[n]);
			while(typ[n]){
				for(int e : cgraph[typ[n]]){
					in[e]--;
					if(!in[e] && !sz[e]){
						qu.push(e);
					}
				}
			}
		}
	}
}
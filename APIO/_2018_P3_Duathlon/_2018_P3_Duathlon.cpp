
// Problem : APIO '18 P3 - Duathlon
// Contest : DMOJ
// URL : https://dmoj.ca/problem/apio18p3
// Memory Limit : 1 MB
// Time Limit : 600 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> graph[100005], cgraph[500005];
vector<pair<int, int>> stk;
vector<vector<pair<int, int>>> cmp;
int par[500005], dfn[500005], low[500005], t;
long long sz[500005], csz[500005];
long long ans;

void dfs1(int n){
	low[n] = dfn[n] = ++t;
	int c = 0;
	for(int e : graph[n]){
		if(e == par[n]){
			continue;
		}
		if(!dfn[e]){
			c++;
			par[e] = n;
			stk.emplace_back(n, e);					
			dfs1(e);
			low[n] = min(low[n], low[e]);
			if((!par[n] && c >= 2) || (par[n] && low[e] >= dfn[n])){
				//cout << "enter: " << n << "\n";
				pair<int, int> edg = {0, 0};
				vector<pair<int, int>> tmp;
				do{
					edg = stk.back();
					stk.pop_back();
					tmp.push_back(edg);
					//cout << "indfs: " << edg.first << " " << edg.second << "\n";
				}
				while(edg != make_pair(n, e));
				cmp.push_back(tmp);
			}
		}
		else if(dfn[e] < dfn[n]){
			low[n] = min(dfn[e], low[n]);
			stk.emplace_back(n, e);		
		}
	}
}

void dfs2(int n){
	sz[n] = n <= N;
	for(int e : cgraph[n]){
		if(e != par[n]){
			par[e] = n;
			dfs2(e);
			sz[n] += sz[e];
		}
	}
	if(n > N){
		csz[n] = cgraph[n].size();
	}
}

void dfs3(int n, long long tot){
	if(n > N){
		ans -= (csz[n]-1) * (tot-sz[n]) * (tot-sz[n]-1);
	}
	for(int e : cgraph[n]){
		if(n <= N && e == par[n]){
			ans -= (csz[e]-1)*sz[n]*(sz[n]-1);
		}
		if(e != par[n]){
			dfs3(e, tot);
		}
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	for(int i = 1; i<=M; i++){
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	int C = N;
	for(int i = 1; i<=N; i++){
		if(!dfn[i]){
			dfs1(i);
			if(stk.size()){
				cmp.push_back(stk);
				stk.clear();
			}
			for(auto v : cmp){
				++C;
				for(auto p : v){
					//cout << p.first << " " << p.second << "\n";
					cgraph[C].push_back(p.second);
					cgraph[C].push_back(p.first);
				}
				//cout << "\n";
				sort(cgraph[C].begin(), cgraph[C].end());
				cgraph[C].erase(unique(cgraph[C].begin(), cgraph[C].end()), cgraph[C].end());
				for(int n : cgraph[C]){
					cgraph[n].push_back(C);
				}
			}
			dfs2(i);
			dfs3(i, sz[i]);
			ans += sz[i] * (sz[i]-1) * (sz[i] -2);
			cmp.clear();
		}
	}
	cout << ans << "\n";
}
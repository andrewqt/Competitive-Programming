#include <bits/stdc++.h>

using namespace std;

int N, M;
int nxt[300005][26];
int ed[300005];
int graph[30][30];
string s;
vector<pair<int, string>> ans;
bool vis[30], instk[30];

bool iscyclic(int n){
	vis[n] = 1;	
	instk[n] = 1;
	for(int c = 0; c<26; c++){
		if(graph[n][c]){
			if(instk[c]){
				return 1;
			}
			else if(!vis[c] && iscyclic(c)){
				return 1;
			}
		}
	}
	instk[n] = 0;
	return 0;
}

bool chk(){
	fill(vis, vis+26, 0);
	fill(instk, instk+26, 0);
	for(int c = 0; c<26; c++){
		if(iscyclic(c)){
			return 0;
		}
	}
	return 1;
}

void dfs(int n){
	if(ed[n]){
		ans.push_back({ed[n], s});
		return;
	}
	for(int c = 0; c<26; c++){
		if(nxt[n][c]){
			for(int d = 0; d<26; d++){
				if(nxt[n][d] && d != c){
					graph[c][d]++;
				}
			}
			if(chk()){
				s.push_back(c+'a');
				dfs(nxt[n][c]);
				s.pop_back();
			}
			for(int d = 0; d<26; d++){
				if(nxt[n][d] && d != c){
					graph[c][d]--;
				}
			}
		}
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("first.in", "r")){
		freopen("first.in", "r", stdin);
		freopen("first.out", "w", stdout);
	}
	cin >> N;
	for(int i = 1; i<=N; i++){
		string s;
		cin >> s;
		int crnt = 0;
		for(char c : s){
			if(!nxt[crnt][c-'a']){
				nxt[crnt][c-'a'] = ++M;
			}
			crnt = nxt[crnt][c-'a'];
		}
		ed[crnt] = i;
	}
	dfs(0);
	sort(ans.begin(), ans.end());
	cout << ans.size() << "\n";
	for(auto p : ans){
		cout << p.second << "\n";
	}
}
#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> graph[200005];
int par[200005];
int clr[200005];
vector<int> lst[3];
int ans[200005];
int cnt[2];

void dfs(int n){
	cnt[clr[n]]++;
	for(int e : graph[n]){
		if(e != par[n]){
			par[e] = n;
			clr[e] = clr[n] ^ 1;
			dfs(e);
		}
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 1; i<N; i++){
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	dfs(1);
	for(int i = 1; i<=N; i++){
		lst[i%3].push_back(i);
	}
	if(cnt[0] < cnt[1]){
		swap(lst[1], lst[2]);
	}
	if(cnt[0] <= N/3){
		for(int i = 1; i<=N; i++){
			if(clr[i] == 0){
				ans[i] = lst[0].back();
				lst[0].pop_back();
			}
			else if(lst[1].size()){
				ans[i] = lst[1].back();
				lst[1].pop_back();
			}
			else if(lst[2].size()){
				ans[i] = lst[2].back();
				lst[2].pop_back();
			}
			else{
				ans[i] = lst[0].back();
				lst[0].pop_back();
			}
		}
	}
	else if(cnt[1] <= N/3){
		for(int i = 1; i<=N; i++){
			if(clr[i] == 1){
				ans[i] = lst[0].back();
				lst[0].pop_back();
			}
			else if(lst[1].size()){
				ans[i] = lst[1].back();
				lst[1].pop_back();
			}
			else if(lst[2].size()){
				ans[i] = lst[2].back();
				lst[2].pop_back();
			}
			else{
				ans[i] = lst[0].back();
				lst[0].pop_back();
			}
		}
	}
	else{
		for(int i = 1; i<=N; i++){
			if(!clr[i]){
				if(lst[1].size()){
					ans[i] = lst[1].back();
					lst[1].pop_back();
				}
				else {
					ans[i] = lst[0].back();
					lst[0].pop_back();
				}
			}
			else{
				if(lst[2].size()){
					ans[i] = lst[2].back();
					lst[2].pop_back();
				}
				else {
					ans[i] = lst[0].back();
					lst[0].pop_back();
				}		
			}
		}
	}
	for(int i =1 ; i<=N; i++){
		cout << ans[i] << " ";
	}
}
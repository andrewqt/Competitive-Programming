#include <bits/stdc++.h>

using namespace std;

int N, M, K;
int arr[505][505];
int par[250005];
pair<int, pair<int, int>> ed[1000005];
int c[250005];
int sz[250005];

int getrt(int n){
	return par[n] = (par[n] == n ? n : getrt(par[n]));
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("skilevel.in", "r")){
		freopen("skilevel.in", "r", stdin);
		freopen("skilevel.out", "w", stdout);
	}
	cin >> N >> M >> K;
	if(K==1){
		cout << 0 << "\n";
		return 0;
	}
	for(int i = 0; i<N; i++){
		for(int j = 0; j<M; j++){
			cin >> arr[i][j];
		}
	}
	int idx = 0;
	for(int i =0 ; i<N; i++){
		for(int j = 0; j<M; j++){
			if(i+1 < N){
				ed[idx++] = {abs(arr[i][j]-arr[i+1][j]),{i*M+j, (i+1)*M+j}};
			}
			if(j+1 < M){
				ed[idx++] = {abs(arr[i][j]-arr[i][j+1]), {i*M+j, i*M+j+1}};
			}
		}
	}
	sort(ed, ed+idx);
	for(int i = 0; i<N*M; i++){
		par[i ]= i;
		cin >> c[i];
		sz[i] = 1;
	}
	long long ans = 0;
	for(int k = 0; k<idx; k++){
		int u = ed[k].second.first, v = ed[k].second.second;
		if(getrt(u) != getrt(v)){
			sz[getrt(v)] += sz[getrt(u)];
			c[getrt(v)] += c[getrt(u)];
			par[getrt(u)] = getrt(v);
			if(sz[getrt(v)] >= K){
				ans += 1LL*ed[k].first*c[getrt(v)];
				c[getrt(v)] = 0;
			}
		}
	}
	cout << ans << endl;
}
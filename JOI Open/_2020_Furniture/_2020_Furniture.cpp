#include <bits/stdc++.h>

using namespace std;

int N, M, Q;
map<pair<int, int>, pair<int, int>> par;
map<pair<int, int>, int> sz;
vector<pair<int, int>> stk;
int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};
int arr[1005][1005];

pair<int, int> getrt(pair<int, int> p){
	if(par[p] == p){
		return p;
	}
	return getrt(par[p]);
}

bool unite(pair<int, int> p, pair<int, int> q){
	p = getrt(p);
	q = getrt(q);
	if(p == q){
		return 0;
	}
	//cout << p.first << " " << p.second << " " << q.first << " " << q.second << "\n";
	if(sz[p] > sz[q]){
		par[q] = p;
		sz[p] += sz[q];
		stk.push_back(q);
	}
	else{
		par[p] = q;
		sz[q] += sz[p];
		stk.push_back(p);
	}
	return 1;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=M; j++){
			cin >> arr[i][j];
			sz[make_pair(i, j)] = 1;
			par[make_pair(i, j)] = make_pair(i, j);
		}
	}
	for(int i= 0; i<=N+1; i++){
		arr[i][M+1] = arr[i][0] = 1;
		sz[make_pair(i, M+1)] = sz[make_pair(i, 0)] = 1;
		par[make_pair(i, 0)] = make_pair(i, 0);
		par[make_pair(i, M+1)] = make_pair(i, M+1);
	}
	for(int j = 0; j<=M+1; j++){
		arr[N+1][j] = arr[0][j] = 1;
		sz[make_pair(N+1, j)] = sz[make_pair(0, j)] = 1;
		par[make_pair(N+1, j)] = make_pair(N+1, j);
		par[make_pair(0, j)] = make_pair(0, j);
	}

	arr[0][0] = arr[N+1][M+1] = 0;
	for(int i = 0; i<=N+1; i++){
		for(int j= 0; j<=M+1; j++){
			if(!arr[i][j]){
				continue;
			}
			for(int m = 0; m<(i*j == 0 || i == N+1 || j == M+1 ? 4 : 8); m++){
				if(i+dx[m] >= 0 && j+dy[m] >= 0 && arr[i+dx[m]][j+dy[m]] == 1){
					unite(make_pair(i+dx[m], j+dy[m]), make_pair(i, j));
				}
			}	
		}
	}
	/*
	for(int i = 0; i<=N+1; i++){
		for(int j = 0; j<=M+1; j++){
			if(getrt(make_pair(i, j)) == make_pair(0, 0)){
				cout << i << " " << j << "\n";
			}
		}
	}
	*/	
	//cout << "done" << "\n";
	cin >> Q;
	while(Q--){
		int a, b;
		cin >> a >> b;
		arr[a][b] = 1;
		int c = 0;
		for(int m = 0; m<8; m++){
			if(arr[a+dx[m]][b+dy[m]] == 1){
				c += unite(make_pair(a+dx[m], b+dy[m]), make_pair(a, b));
			}
		}
		//cout << getrt(make_pair(0, 1)).first << " " << getrt(make_pair(0, 1)).second << "\n";
		//cout << getrt(make_pair(1, 0)).first << " " << getrt(make_pair(0, 1)).second << "\n";
		if(getrt(make_pair(0, 1)) == getrt(make_pair(1, 0))){
			while(c--){
				sz[getrt(stk.back())] -= sz[stk.back()];
				par[stk.back()] = stk.back();
				stk.pop_back();
			}
			cout << 0 << "\n";
		}
		else{
			cout << 1 << "\n";
		}
	}
}
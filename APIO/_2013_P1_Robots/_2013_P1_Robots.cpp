#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
// Problem : APIO '13 P1 - Robots
// Contest : DMOJ
// URL : https://dmoj.ca/problem/apio13p1
// Memory Limit : 128 MB
// Time Limit : 750 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)
 
#include <bits/stdc++.h>
 
using namespace std;
 
int K, N, M;
int dist[10][10][505][505];
char mp[505][505];
pair<short, short> moves[4] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
pair<short, short> endpos[4][505][505];
queue<pair<short, short>> qu;
vector<pair<int, pair<short, short>>> vec;
int oo = INT_MAX>>2;
 
pair<int, int> fnd(int d, int x, int y){
	if(endpos[d][x][y].first){
		return endpos[d][x][y];
	}
	int r = 0;
	if(mp[x][y] == 'A'){
		r = 3;
	}
	if(mp[x][y] == 'C'){
		r = 1;
	}
	if(mp[x+moves[(d+r)%4].first][y+moves[(d+r)%4].second] == 'x'){
		return endpos[d][x][y] = {x, y};
	}
	return endpos[d][x][y] = fnd((d+r)%4, x+moves[(d+r)%4].first, y+moves[(d+r)%4].second);
}
 
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> K >> M >> N;
	oo = K*M*N;
	for(int l = 1; l<=K; l++){
		for(int r = l; r<=K; r++){
			for(int i = 1; i<=N; i++){
				for(int j = 1; j<=M; j++){
					dist[l][r][i][j] = oo;
				}
			}		
		}
	}
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=M; j++){
			cin >> mp[i][j];
			if(mp[i][j] > '0' && mp[i][j] <= '9'){
				dist[mp[i][j]-'0'][mp[i][j]-'0'][i][j] = 0;
			}
		}
	}
	for(int i = 0; i<=N+1; i++){
		mp[i][0] = mp[i][M+1] = 'x';
	}
	for(int j = 0; j<=M+1; j++){
		mp[0][j] = mp[N+1][j] = 'x';
	}
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=M; j++){
			for(int k = 0; k<4; k++){
				fnd(k, i, j);
			}
		}
	}
	for(int len = 1; len<=K; len++){
		for(int l = 1; l+len-1<=K; l++){
			int r = l+len-1;
			vec.clear();
			for(int i = 1; i<=N; i++){
				for(int j = 1; j<=M; j++){
					for(int k = l; k<r; k++){
						dist[l][r][i][j] = min(dist[l][k][i][j] + dist[k+1][r][i][j], dist[l][r][i][j]);
					}
					if(dist[l][r][i][j] != oo){
						vec.push_back({dist[l][r][i][j], make_pair(i, j)});
					}
				}
			}
			sort(vec.begin(), vec.end());
			if(vec.empty()){
				cout << -1 << "\n";
				return 0;
			}
			int idx = 0;
			while(qu.size() || idx < vec.size()){
				if(qu.empty()){
					qu.push(vec[idx++].second);
				}
				else{
					auto p = qu.front();
					qu.pop();
					while(idx < vec.size() && dist[l][r][p.first][p.second] == vec[idx].first){
						if(dist[l][r][vec[idx].second.first][vec[idx].second.second] == dist[l][r][p.first][p.second]){
							qu.push(vec[idx].second);
						}
						idx++;
					}
					for(int m = 0; m<4; m++){
						auto e = endpos[m][p.first][p.second];
						if(dist[l][r][e.first][e.second] > dist[l][r][p.first][p.second]+1){
							dist[l][r][e.first][e.second] = dist[l][r][p.first][p.second]+1;
							qu.push(e);
						}
					}					
				}
			}
		}
	}
	int ans = oo;
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=M; j++){
			ans = min(dist[1][K][i][j], ans);
		}
	}
	cout << (ans == oo ? -1 : ans);
}
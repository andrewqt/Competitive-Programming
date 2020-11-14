#include <bits/stdc++.h>

using namespace std;

int N, M;
long long MOD = 1e9+7;
bool tkn[1005][1005];
pair<int, int> par[1005][1005];
vector<pair<int, int>> moves = {{0, -1}, {0, 1}, {1, 0}};
long long cnt[1005][1005];

long long add(long long a, long long b){
	return (a+b)%MOD;
}

long long mult(long long a, long long b){
	return (a*b)%MOD;
}

long long sub(long long a, long long b){
	a = add(a, -b);
	if(a < 0){
		a += MOD;
	}
	return a;
}

pair<int, int> getrt(pair<int, int> p){
	return par[p.first][p.second] = (par[p.first][p.second] == p ? p : getrt(par[p.first][p.second]));
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("cave.in", "r")){
		freopen("cave.in", "r", stdin);
		freopen("cave.out", "w", stdout);
	}
	cin >> N >> M;
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=M; j++){
			char c;
			cin >> c;
			if(c == '.'){
				tkn[i][j] = 1;
			}
			par[i][j] = {i, j};
		}
	}
	long long ans = 1;
	for(int i = N-1; i; i--){
		for(int j = 2; j<M; j++){
			if(tkn[i][j]){
				auto p = getrt({i, j});
				auto q1 = getrt({i, j-1});
				auto q2 = getrt({i, j+1});
				if(tkn[i][j-1] && q1 != p){
					par[q1.first][q1.second] = p;
				}
				if(tkn[i][j+1] && q2 != p){
					par[q2.first][q2.second] = p;
				}				
			}
		}
		for(int j = 2; j<M; j++){
			if(tkn[i][j] && getrt({i, j}) == make_pair(i, j)){
				cnt[i][j]++;
			}
		}
		for(int j = 2; j<M; j++){
			auto p = getrt({i+1, j});
			auto q = getrt({i, j});
			if(tkn[i+1][j] && tkn[i][j] && p != q){
				par[p.first][p.second] = q;
				cnt[q.first][q.second] = mult(cnt[p.first][p.second], cnt[q.first][q.second]);
			}
		}
		for(int j = 2; j<M; j++){
			if(tkn[i][j] && getrt({i, j}) == make_pair(i, j)){
				cnt[i][j]++;
			}
		}
	}
	for(int i = 2; i<N; i++){
		for(int j = 2; j<M; j++){
			//cout << getrt({i, j}).first << " " << getrt({i, j}).second << endl;
			if(tkn[i][j] && getrt({i, j}) == make_pair(i, j)){
				ans = mult(ans, cnt[i][j]);
			}
		}
	}
	cout << ans << "\n";
}

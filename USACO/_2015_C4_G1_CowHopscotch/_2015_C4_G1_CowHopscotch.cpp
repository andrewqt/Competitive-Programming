#include <bits/stdc++.h>

using namespace std;

int N, M, K;
long long bit[2][1000005];
long long MOD = 1e9+7;
int arr[1000][1000];
long long ans[1000][1000];
vector<pair<int, int>> vec;

int bs(pair<int, int> p){
	return (upper_bound(vec.begin(), vec.end(), p)) - vec.begin() + 1;
}

void upd(int n, int v, int t){
	int sz = t ? (int) (vec.size()) : M;
	while(n <= sz){
		bit[t][n] += v;
		bit[t][n] %= MOD;
		n += (n&-n);
	}
}

long long query(int n, int t){
	long long ret = 0;
	while(n){
		ret += bit[t][n];
		n -= n&-n;
	}
	return ret % MOD;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("hopscotch.in", "r")){
		freopen("hopscotch.in", "r", stdin);
		freopen("hopscotch.out", "w", stdout);
	}
	cin >> N >> M >> K;
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=M; j++){
			cin >> arr[i][j];
			vec.push_back({arr[i][j], j});
		}
	}
	sort(vec.begin(), vec.end());
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
	long long crnt = 0;
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=N; j++){
			if(i == 1 && j == 1){
				crnt = 1;
			}
			else{
				crnt = query(j-1, 0);
				crnt -= query(bs({arr[i][j], j})-1, 1);
				crnt += query(bs({arr[i][j], 0}), 1);
				crnt %= MOD;
				crnt += MOD;
				crnt %= MOD;
			}
			ans[i][j] = crnt;		
		}
		for(int j = 1; j<=N; j++){
			upd(bs({arr[i][j], j}), ans[i][j], 1);
			upd(j, ans[i][j], 0);	
		}
	}
	cout << crnt << endl;
}
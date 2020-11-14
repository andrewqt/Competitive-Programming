#include <bits/stdc++.h>

using namespace std;

int N, M, K;
long long mx[105][105];
long long dis[105][105];
long long buy[105][10005];
long long sell[105][10005];
long long tmp[105][105];
long long a, b, c;

bool solve(long long k){
	for(int i =1 ; i<=N; i++){
		for(int j = 1; j<=N; j++){
			tmp[i][j] = mx[i][j] - k*dis[i][j];
		}
	}
	for(int k = 1; k<=N; k++){
		for(int i = 1; i<=N; i++){
			for(int j = 1; j<=N; j++){
				if(i == j){
					if(k != i && tmp[i][k] + tmp[k][j] >= 0){
						return 1;
					}	
				}
				tmp[i][j] = max(tmp[i][j], tmp[i][k] + tmp[k][j]);
			}
		}
	}
	return 0;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M >> K;
	for(int i =1 ; i<=N; i++){
		for(int k = 1; k<=K; k++){
			cin >> buy[i][k] >> sell[i][k];
		}
	}
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=N; j++){
			for(int k = 1; k<=K; k++){
				if(sell[j][k]+1 && buy[i][k]+1){
					mx[i][j] = max(mx[i][j], sell[j][k] - buy[i][k]);
				}
			}
		}
	}
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=N; j++){
			dis[i][j] = 2000000000;
			if(i == j){
				dis[i][j] = 0;
			}
		}
	}
	for(int i = 1; i<=M; i++){
		cin >> a >> b >> c;
		dis[a][b] = min(dis[a][b], c);
	}
	for(int k = 1; k<=N; k++){
		for(int i = 1; i<=N; i++){
			for(int j = 1; j<=N; j++){
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
	}
	int l = 1,r = 1000000000, ans = 0;
	while(l <= r){
		int mid = l + r>> 1;
		if(solve(mid)){
			l = mid + 1;
			ans = mid;
		}
		else{
			r =mid - 1;
		}
	}
	cout << ans << endl;
}
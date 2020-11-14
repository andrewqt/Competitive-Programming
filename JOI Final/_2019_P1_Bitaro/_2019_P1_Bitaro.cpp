#include <bits/stdc++.h>

using namespace std;

int N, M;
int ingot[3005][3005];
int orb[3005][3005];
char mp[3005][3005];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=M; j++){
			cin >> mp[i][j];
		}
	}
	for(int i = 1; i<=N; i++){
		for(int j = M; j; j--){
			orb[i][j] = orb[i][j+1] + (mp[i][j] == 'O');
		}
	}
	for(int i = 1; i<=M; i++){
		for(int j = N; j; j--){
			ingot[j][i] = ingot[j+1][i] + (mp[j][i] == 'I');
		}
	}
	long long ans = 0;
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=M; j++){
			if(mp[i][j] == 'J'){
				ans += ingot[i][j] * orb[i][j];
			}
		}
	}
	cout << ans << "\n";
}
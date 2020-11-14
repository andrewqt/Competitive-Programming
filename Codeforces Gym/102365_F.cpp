
// Problem : F. Fair Distribution
// Contest : Codeforces - UBC Programming Contest 2019 (UBCPC 2019)
// URL : https://codeforces.com/gym/102365/problem/F
// Memory Limit : 1024 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N;
pair<int, int> arr[205];
int tbl[205][205];

int crs(int a, int b, int c){
	return (arr[b].first - arr[a].first) * (arr[c].second - arr[a].second) - (arr[b].second - arr[a].second) * (arr[c].first - arr[a].first);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout << setprecision(14);
	cin >> N;
	for(int i = 1; i<=N; i++){
		cin >> arr[i].first >> arr[i].second;
	}
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=N; j++){
			if(i == j){
				continue;
			}
			for(int k = 1; k<=N; k++){
				if(k == i || k == j){
					continue;
				}
				if(crs(i, j, k) > 0){
					tbl[i][j]++;
				}
				else if(crs(i, j, k) == 0){
					tbl[i][j]++;
					tbl[i][j] -= (arr[i] < arr[k] && arr[k] < arr[j]);
					tbl[i][j] -= (arr[j] < arr[k] && arr[k] < arr[i]);
				}
				//cout << k << " " << tbl[i][j] << "\n";
			}
			//cout << i << " " << j << " " << tbl[i][j] << "\n";
		}
	}
	for(int i= 1; i<=N; i++){
		long double ans = 0;
		for(int j = 1; j<=N; j++){
			for(int k = j+1; k<=N; k++){
				if(j == i || k == i){
					continue;
				}
				long double A = abs(crs(j, k, i));
				if(crs(j, k, i) > 0){
					ans += A / (tbl[j][k] + 1) / (tbl[j][k] + 2) / (tbl[j][k]);
				}
				else if(crs(k, j, i) > 0){
					ans += A / (tbl[k][j] + 1) / (tbl[k][j] + 2) / (tbl[k][j]);
				}
				//cout << i << " " << j << " " << k << " " << A << " " << ans << "\n";
			}
		}
		cout << ans << "\n";
	}
}
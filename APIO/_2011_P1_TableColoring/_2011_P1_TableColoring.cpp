
// Problem : APIO '11 P1 - Table Coloring
// Contest : DMOJ
// URL : https://dmoj.ca/problem/apio11p1
// Memory Limit : 256 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N, M, K;
const long long MOD = 1e9;
vector<pair<int, int>> row[100005];
int arr[2][100005];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M >> K;
	for(int i = 1; i<=K; i++){
		int n, m, c;
		cin >> n >> m >> c;
		row[n].push_back({m, c});
	}
	fill(arr[0]+1, arr[0]+1+M, 2);
	fill(arr[1]+1, arr[1]+1+M, 2);
	for(int i = 1; i<=N; i++){
		if(row[i].size()){
			bool same = 0, diff = 0;
		}
	}
}
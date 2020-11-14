
// Problem : 
// 			C - +/- Rectangle
// 			Editorial
// 		
// Contest : AtCoder - AtCoder Grand Contest 016
// URL : https://atcoder.jp/contests/agc016/tasks/agc016_c
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N, M, H, W;
int arr[505][505];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M >> H >> W;
	long long ans = N*M*3000LL;
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=M; j++){
			arr[i][j] = 3000;
		}
	}
	for(int i = H; i<=N; i+=H){
		for(int j = W; j<=M; j+=W){
			arr[i][j] = -(H*W-1)*3000LL-1;
			ans += -(H*W-1)*3000LL-1-3000;
		}
	}
	if(ans > 0){
		cout << "Yes\n";
		for(int i = 1; i<=N; i++){
			for(int j = 1; j<=M; j++){
				cout << arr[i][j] << " ";
			}
			cout << "\n";
		}
	}
	else{
		cout << "No\n";
	}
}
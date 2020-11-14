
// Problem : E. Square Tiling
// Contest : Codeforces - Codeforces Round #246 (Div. 2)
// URL : https://codeforces.com/contest/432/problem/E
// Memory Limit : 256 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N, M;
char ans[105][105];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	for(int i= 1; i<=N; i++){
		for(int j = 1; j<=M; j++){
			if(ans[i][j] < 'A'){
				int k = min(N-i, M-j);
				for(int a = 0; a<=k; a++){
					for(int b = 0; b<=k; b++){
						ans[i+a][j+b] = 'A';
					}
				}
				if(N-i == M-j){
					break;
				}
				else if(N-i < M-j){
					
				}
				else{
					
				}
			}
		}
	}
}
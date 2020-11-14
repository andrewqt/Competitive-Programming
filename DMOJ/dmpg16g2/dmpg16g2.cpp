
// Problem : DMPG '16 G2 - Kabane Apocalypse
// Contest : DMOJ
// URL : https://dmoj.ca/problem/dmpg16g2
// Memory Limit : 256 MB
// Time Limit : 1400 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N;
int mp[1005][1005];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=N; j++){
			char c;
			cin >> c;
			if(c == '.'){
				mp[i][j] = 5;
			}
			else{
				mp[i][j] = c - 'A' + 1;
			}
		}
	}
	for(int m = 0; m<32; m++){
		for(int i = 1; i<=N; i++){
			for(int j = 1; j<=M; j++){
				
			}
		}
	}
}
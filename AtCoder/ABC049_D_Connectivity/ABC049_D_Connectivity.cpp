
// Problem : 
// 			D - Connectivity
// 			Editorial
// 		
// Contest : AtCoder - AtCoder Beginner Contest 049
// URL : https://atcoder.jp/contests/abc049/tasks/arc065_b
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N, A, B;
int dsu[2][200005];
map<int, int> mp[200005];

int getrt(int t, int n){
	return dsu[t][n] = (dsu[t][n] == n ? n : getrt(t, dsu[t][n]));
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> A >> B;
	for(int i = 1; i<=N; i++){
		dsu[0][i] = dsu[1][i] = i;
	}
	for(int i = 1; i<=A; i++){
		int a, b;
		cin >> a >> b;
		if(getrt(0, a) != getrt(0, b)){
			dsu[0][getrt(0, a)] = getrt(0, b);
		}
	}
	for(int i = 1; i<=B; i++){
		int a, b;
		cin >> a >> b;
		if(getrt(1, a) != getrt(1, b)){
			dsu[1][getrt(1, a)] = getrt(1, b);
		}
	}
	for(int i = 1; i<=N; i++){
		mp[getrt(1, i)][getrt(0, i)]++;
	}
	for(int i = 1; i<=N; i++){
		cout << mp[getrt(1, i)][getrt(0, i)] << " ";
	}
}
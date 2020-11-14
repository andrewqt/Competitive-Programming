
// Problem : E. Maximum Matching
// Contest : Codeforces - Codeforces Round #508 (Div. 2)
// URL : https://codeforces.com/contest/1038/problem/E
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N, C;
map<pair<int, int>, int> mp;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	for(int i = 1; i<=4; i++){
		for(int j= 1; j<=4; j++){
			mp[make_pair(i, j)] = C++;
		}
	}
	cin >> N;
}
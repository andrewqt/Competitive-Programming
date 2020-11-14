
// Problem : E. Obtain a Permutation
// Contest : Codeforces - Codeforces Round #615 (Div. 3)
// URL : https://codeforces.com/problemset/problem/1294/E
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

vector<int> arr[200005];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int M, N;
	cin >> N >> M;
	for(int i = 0; i<N; i++){
		for(int j = 0; j<M; j++){
			int n;
			cin >> n;
			arr[i].push_back(n);
		}
	}
	
}
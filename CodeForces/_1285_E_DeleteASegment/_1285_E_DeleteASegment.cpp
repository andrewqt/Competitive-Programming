
// Problem : E. Delete a Segment
// Contest : Codeforces - Codeforces Round #613 (Div. 2)
// URL : https://codeforces.com/contest/1285/problem/E
// Memory Limit : 256 MB
// Time Limit : 4000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int T;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while(T--){
		int N;
		cin >> N;
		vector<pair<int, int>> v;
		for(int i = 0; i<N; i++){
			int a, b;
			cin >> a >> b;
			b++;
			v.emplace_back(a, b);
		}
		sort(v.begin(), v.end(), [](auto a, auto b){
			if(a.first == b.first){
				return a.second > b.second;
			}
			return a.first < b.first;
		});
		int bst = -2e9;
		bool b = 0;
		for(auto p : v){
			if(p.second <= bst){
				b = 1;
				break;
			}
			bst = p.second;
		}
		long long tot = 0;
		bst = -2e9;
		for(auto p : v){
			if(p.second > bst){
				tot += p.second - max(p.first, bst);
				bst = p.second;
			}
			cout << " " << tot << "\n";
		}
		if(!b){
			int mn = min(v[0].second, v[1].first) - v[0].first;
			mn = min(mn, v.back().second - max(v.back().first, v[v.size()-2].second));
			for(int i = 1; i+1<v.size(); i++){
				int l = max(v[i].first, v[i-1].second);
				int r = min(v[i].second, v[i+1].first);
				if(l > r){
					mn = 0;
				}
				else{
					mn = min(mn, r - l);
				}
			}
			tot -= mn;
		}
		cout << tot << "\n";
	}
}

// Problem : CCO '06 P5 - Domino
// Contest : DMOJ
// URL : https://dmoj.ca/problem/cco06p5
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int T;

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while(T--){
		int N;
		cin >> N;
		map<int, int> mp;
		for(int i =1 ; i<=N; i++){
			int a, b;
			cin >> a >> b;
			mp[a]++;
			mp[b]++;
		}		
		vector<int> odd;
		for(auto p : mp){
			if(p.second&1){
				odd.push_back(p.first);
			}
		}
		if(odd.size() >= 2){
			odd.pop_back();
			odd.pop_back();
		}
		vector<pair<int, int>> ans;
		for(int i = 0; i < odd.size(); i+=2){
			ans.push_back(make_pair(odd[i], odd[i+1]));
		}
		cout << ans.size() << "\n";
		for(auto p : ans){
			cout << p.first << " " << p.second << "\n";
		}
	}
}
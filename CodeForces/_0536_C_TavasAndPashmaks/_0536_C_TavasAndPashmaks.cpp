
// Problem : C. Tavas and Pashmaks
// Contest : Codeforces - Codeforces Round #299 (Div. 1)
// URL : https://codeforces.com/contest/536/problem/C
// Memory Limit : 256 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N;
pair<pair<long double, long double>, int> arr[200005];
deque<pair<pair<long double, long double>, int>> dq;

bool cross(pair<long double, long double> a, pair<long double, long double> b, pair<long double, long double> c){
	return ((b.first-c.first)*(a.second-c.second) - (b.second-c.second)*(a.first-c.first)) <= 0;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 1; i<=N; i++){
		int a, b;
		cin >> a >> b;
		arr[i].first.first = 1.0/a;
		arr[i].first.second = 1.0/b;
		arr[i].second = i;
	}
	sort(arr+1, arr+1+N, [](auto a, auto b){
		if(a.first.first == b.first.first){
			return a.first.second < b.first.second;
		}
		return a.first.first < b.first.first;
	});
	arr[0] = {{0, 100000}, 0};
	arr[N+1] = {{100000, 0}, 0};
	for(int i = 0; i<=N+1; i++){
		//cout << arr[i].second << "\n";
		while(dq.size() >= 2){
			auto p = dq.back();
			dq.pop_back();
			if(cross(dq.back().first, p.first, arr[i].first)){
				dq.push_back(p);
				break;
			}
		}
		dq.push_back(arr[i]);
	}
	vector<int> ans;
	while(dq.size()){
		ans.push_back(dq.back().second);
		dq.pop_back();
	}
	sort(ans.begin(), ans.end());
	for(auto p : ans){
		if(p){
			cout << p << " ";
		}
	}
}
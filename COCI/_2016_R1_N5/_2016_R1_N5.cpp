
// Problem : COCI '16 Contest 1 #5 Kralj
// Contest : DMOJ
// URL : https://dmoj.ca/problem/coci16c1p5
// Memory Limit : 128 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N;
int arr[500005], apow[500005], bpow[500005];
vector<int> v[500005];

int solve(int s){
	set<int> st;
	int ret = 0;
	for(int i = s, c = 0; c<N; c++, i = (i+1)%N){
		for(int n : v[i]){
			st.insert(n);
		}
		if(st.empty()){
			return 0;
		}
		if(st.lower_bound(apow[i]) != st.end()){
			ret++;
			st.erase(st.lower_bound(apow[i]));
		}
		else{
			st.erase(st.begin());
		}
	}
	//cout << s << "\n";
	return ret;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 0; i<N; i++){
		cin >> arr[i];
		arr[i]--;
	}
	for(int i = 0; i<N; i++){
		cin >> apow[i];
		//v[arr[i]].push_back(apow[i]);
	}
	for(int i = 0; i<N; i++){
		cin >> bpow[i];
		v[arr[i]].push_back(bpow[i]);
	}
	int delta = 0, pre = 0;
	deque<pair<int, int>> mn;
	for(int i = 0 ;i<N; i++){
		pre += v[i].size();
		pre--;
		while(mn.size() && mn.back().second > pre){
			mn.pop_back();
		}
		mn.push_back(make_pair(i, pre));
	}
	int ans = -1;
	for(int i = 0; i<N; i++){
		//cout << mn.front().first << " " << mn.front().second-delta << " " << delta << endl;
		if(mn.front().second - delta >= 0){
			//cout << mn.back().second-delta << " " << i << "\n";
			ans = solve(i);
			break;
		}
		/*
		pre += v[i].size();
		pre--;
		*/
		delta += v[i].size();
		delta--;
		//cout << pre << " " << delta << endl;
		if(mn.front().first == i){
			mn.pop_front();
		}
		while(mn.size() && mn.back().second > pre + delta){
			mn.pop_back();
		}
		mn.push_back(make_pair(i, pre+delta));
	}
	assert(ans != -1);
	cout << ans << "\n";
}

// Problem : APIO '18 P1 - New Home
// Contest : DMOJ
// URL : https://dmoj.ca/problem/apio18p1
// Memory Limit : 1 MB
// Time Limit : 2500 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

struct obj{
	int x, t, a, b, ca, cb;
};

struct qu{
	int x, t, ct;
};

int N, K, Q, M;
set<pair<int, int>> st[300005];
long long ans[300005];
obj arr[300005];
qu qrr[300005];
int lst[300005];
pair<int, int> rng[300005];
vector<int> add[600005];
vector<int> rem[600005];
vector<int> tst[600005];
vector<int> compt;
vector<int> compx;
vector<pair<pair<int, int>, pair<int, int>>> qu;

void rec(int l, int r, vector<pair<pair<int, int>, pair<int, int>>> qu){
	
}

void solve(){
	compx.push_back(1000000000);
	for(int i = 1; i<=M; i++){
		for(int n : add[i]){
			st[arr[n].t].insert({arr[n].x, n});
			auto ptr = st[arr[n].t].lower_bound({arr[n].x, n});
			rng[ptr->second].first = arr[n].x;
			compx.push_back(arr[n].x);
			if(ptr != st[arr[n].t].begin()){
				--ptr;
				qu.push_back(make_pair(rng[ptr->second], make_pair(lst[ptr->second], i-1)));
				lst[ptr->second] = i;
				rng[ptr->second].second = (ptr->first+arr[n].x)/2;
				compx.push_back(ptr->first+arr[n].x>>1);
				++ptr;
			}
			if(++ptr != st[arr[n].t].end()){
				rng[n].second = (ptr->first+arr[n].x)/2;
				compx.push_back(rng[n].second);
			}
			else{
				rng[n].second = 1000000000;
			}
			ptr--;
		}
		for(int n : rem[i]){
			qu.push_back(make_pair(rng[n], make_pair(lst[n], i)));
			st[arr[n].t].erase({arr[n].x, n});
			auto ptr = st[arr[n].t].lower_bound({arr[n].x, n});
			if(ptr != st[arr[n].t].begin()){
				ptr--;
				qu.push_back(make_pair(rng[ptr->second], make_pair(lst[n], i)));
				lst[n] = i+1;
				rng[ptr->second].second = 1000000000;
				int x = ptr->first;
				if(++ptr != st[arr[n].t].end()){
					rng[ptr->second].second = (ptr->first + x)/2;
					compx.push_back(rng[ptr->second].second);
				}
			}
		}
	}
	sort(compx.begin(), compx.end());
	compx.erase(unique(compx.begin(), compx.end()), compx.end());
	
	qu.clear();
	compx.clear();
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> K >> Q;
	for(int i = 1; i<=N; i++){
		cin >> arr[i].x >> arr[i].t >> arr[i].a >> arr[i].b;
		compt.emplace_back(arr[i].a);
		compt.emplace_back(arr[i].b);
	}
	sort(compt.begin(), compt.end());
	compt.erase(unique(compt.begin(), compt.end()), compt.end());
	M = compt.size();
	for(int i = 1; i<=N; i++){
		arr[i].ca = lower_bound(compt.begin(), compt.end(), arr[i].a) - compt.begin() + 1;
		arr[i].cb = lower_bound(compt.begin(), compt.end(), arr[i].b) - compt.begin() + 1;
		add[arr[i].ca].emplace_back(i);
		rem[arr[i].cb].emplace_back(i);
	}
	for(int q = 1; q<=Q; q++){
		cin >> qrr[q].x >> qrr[q].t;
		qrr[q].ct = upper_bound(compt.begin(), compt.end(), qrr[q].t) - compt.begin();
		tst[qrr[q].ct].emplace_back(q);
	}
	int cnt = K;
	for(int i = 1; i<=M; i++){
		for(int n : add[i]){
			st[n].insert({i, 0});
			if(st[n].size() == 1){
				cnt--;
			}
		}
		if(cnt){
			for(int n : tst[i]){
				ans[n] = -1;
			}
		}
		for(int n : rem[i]){
			st[n].erase({i, 0});
			if(st[n].empty()){
				cnt++;
			}
		}
	}	
	solve();
	for(int i = 1; i<=N; i++){
		arr[i].x = 1000000000 - arr[i].x;
	}
	for(int i = 1; i<=Q; i++){
		qrr[i].x = 1000000000 - qrr[i].x;
	}
	solve();
}
#include "meetings.h"
#include <bits/stdc++.h>

using namespace std;

void rec(vector<int> v){
	if(v.size() == 1){
		return;
	}
	int c = v[0];
	vector<vector<int>> st;
	for(int i = 1; i<v.size(); i++){
		int n = v[i];
		bool b = 0;
		for(int j = 0; j<st.size(); j++){
			if(Query(n, st[j][0], c) != c){
				b = 1;
				st[j].push_back(n);
				break;
			}
		}
		if(!b){
			st.push_back({n});
		}
	}
	for(auto k : st){
		vector<int> lst;
		if(k.size() == 1){
			continue;
		}
		int lca = Query(k[0], k[1], c);
		for(int j = 2; j<k.size(); j++){
			lca = Query(lca, k[j], c);
		}
		lst.push_back(lca);
		Bridge(lca, c);
		for(int n : k){
			if(lca != n){
				lst.push_back(n);
			}
		}
		rec(lst);
	}
}

void Solve(int N) {
	vector<int> v;
	for(int i = 0; i<N; i++){
		v.push_back(i);
	}
	rec(v);
}

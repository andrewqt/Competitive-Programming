
// Problem : APIO '19 P3 - Street Lamps
// Contest : DMOJ
// URL : https://dmoj.ca/problem/apio19p3
// Memory Limit : 512 MB
// Time Limit : 2500 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

struct FenwickTree{
	int bit[300005];
	int lim;
	vector<int> vec;
	int query(int n){
		//cout << "q: " << n << endl;
		int ret = 0;
		while(n){
			ret += bit[n];
			n -= n&-n;
		}
		return ret;
	}
	void add(int n, int v){
		//cout << "a: " << n << endl;
		while(n <= lim){
			bit[n] += v;
			vec.push_back(n);
			n += n&-n;
		}
	}
	void clr(){
		//cout << "c: " << n << endl;
		for(int n : vec){
			bit[n] = 0;
		}
		vec.clear();
	}
};

int N, Q;
bool state[300005];
set<int> st;
multiset<int> rhthand;
vector<pair<pair<int, int>, int>> upd, qu;
int ans[300005];
FenwickTree bit;

void solve(int l, int r, vector<pair<pair<int, int>, int>> upd, vector<pair<pair<int, int>, int>> qu){
	if(l > r){
		return;
	}
	//cout << l << " " << r << endl;
	int mid = (l+r)>>1;
	vector<pair<pair<int, int>, int>> lftu, rhtu, lftq, rhtq;
	int idx = 0;
	int cnt = 0;
	for(auto q : qu){
		while(idx < (int) upd.size() && abs(upd[idx].second) > q.second){
			if(upd[idx].first.first <= mid){
				if(upd[idx].first.second >= mid){
					//cout << upd[idx].second << endl;
					bit.add(1, upd[idx].second);
					bit.add(upd[idx].first.second+1, -upd[idx].second);
					if(upd[idx].second > 0){
						cnt++;
						rhthand.insert(upd[idx].first.second);
					}
					else{
						cnt--;
						rhthand.erase(rhthand.lower_bound(upd[idx].first.second));
					}
				}
				lftu.push_back(upd[idx]);
			}
			else{
				rhtu.push_back(upd[idx]);
			}
			idx++;
		}
		assert(cnt <= 1);
		if(q.first.first >= mid){
			if(cnt && *rhthand.begin() >= q.first.second){
				ans[q.second] -= q.second;
			}
			ans[q.second] += bit.query(q.first.second);
			if(q.first.first > mid){
				rhtq.push_back(q);
			}
		}
		else{
			lftq.push_back(q);
		}
	}
	bit.clr();
	rhthand.clear();
	solve(l, mid-1, lftu, lftq);
	solve(mid+1, r, rhtu, rhtq);
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> Q;
	st.insert(0);
	st.insert(N+1);
	for(int i = 1; i<=N; i++){
		char c;
		cin >> c;
		state[i] = (c == '1');
		if(!state[i]){
			st.insert(i);
		}
	}
	for(int i = 1; i<=N; i++){
		if(state[i]){
			int idx = *st.lower_bound(i);
			idx--;
			upd.push_back({{i, idx}, Q+1});
			i = idx;
		}
	}
	for(int q = Q; q; q--){
		string s;
		cin >> s;
		if(s == "query"){
			int l, r;
			cin >> l >> r;
			r--;
			qu.push_back({{l, r}, q});
		}
		else{
			int i;
			cin >> i;
			state[i] ^= 1;
			const int coe = state[i] ? 1 : -1;
			int r = i, l = i;
			if(state[i]){
				st.erase(i);
			}
			if(state[i+1]){
				r = *st.lower_bound(i)-1;
				upd.push_back({{i+1, r}, -coe*q});
			}
			if(state[i-1]){
				l = *(--st.lower_bound(i))+1;
				upd.push_back({{l, i-1}, -coe*q});
			}
			upd.push_back({{l, r}, coe*q});			
			if(!state[i]){
				st.insert(i);
			}
			ans[q] = -1;
		}
	}
	bit.lim = N;
	solve(1, N, upd, qu);
	for(int q = Q; q; q--){
		if(ans[q] != -1){
			cout << ans[q] << "\n";
		}
	}
}
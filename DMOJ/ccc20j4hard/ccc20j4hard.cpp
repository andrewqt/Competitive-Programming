
// Problem : CCC '20 J4 - Cyclic Shifts (Hard)
// Contest : DMOJ
// URL : https://dmoj.ca/problem/ccc20j4hard
// Memory Limit : 32 MB
// Time Limit : 200 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

struct hash_pair { 
    size_t operator()(const pair<long long, long long >& p) const
    { 
        auto hash1 = hash<T1>{}(p.first); 
        auto hash2 = hash<T2>{}(p.second); 
        return hash1 ^ hash2; 
    } 
}; 

mt19937 rando(chrono::steady_clock::now().time_since_epoch().count());
int N, M;
string s, t;
long long pows[2][400005];
pair<long long, long long> hsh[400005];
const long long MOD = 1197672433;
long long sd[2];
unordered_set<pair<long long, long long, bool, hash_pair>> st;

pair<long long, long long> gethsh(int l, int r){
	long long h1 = ((hsh[r].first - hsh[l-1].first * pows[0][r - l + 1])%MOD+MOD)%MOD;
	long long h2 = ((hsh[r].second - hsh[l-1].second * pows[1][r - l + 1])%MOD+MOD)%MOD;
	return make_pair(h1, h2);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t >> s;
	N = s.size();
	M = t.size();
	s += s;
	sd[0] = uniform_int_distribution<long long>(MOD/2, MOD-1)(rando);
	sd[1] = uniform_int_distribution<long long>(MOD/2, MOD-1)(rando);
	pows[1][0] = pows[0][0] = 1;
	for(int i = 1; i<=400000; i++){
		pows[0][i] = pows[0][i-1] * sd[0] % MOD;
		pows[1][i] = pows[1][i-1] * sd[1] % MOD;
	}
	for(int i = 1; i<=2*N; i++){
		hsh[i].first = (hsh[i-1].first * sd[0] + s[i-1])%MOD;
		hsh[i].second = (hsh[i-1].second * sd[1] + s[i-1])%MOD;
		if(i >= N){
			st.insert(gethsh(i-N+1, i));
		}
	}
	for(int i =1; i<=M; i++){
		hsh[i].first = (hsh[i-1].first * sd[0] + t[i-1])%MOD;
		hsh[i].second = (hsh[i-1].second * sd[1] + t[i-1])%MOD;
		if(i >= N){
			if(st.count(gethsh(i-N+1, i))){
				cout << "yes\n";
				return 0;
			}
		}
	}
	cout << "no\n";
}
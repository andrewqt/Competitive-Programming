#include <bits/stdc++.h>

using namespace std;

string s;
int N;
long long hsh;
const long long MOD = 1e9+7;
const long long sd = 31;
vector<int> len;
unordered_set<int> st[100005];
vector<char> v;
vector<long long> h;
long long pows[100005];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("censor.in", "r")){
		freopen("censor.in", "r", stdin);
		freopen("censor.out", "w", stdout);
	}
	cin >> s >> N;
	for(int i =1 ; i<=N; i++){
		string t;
		cin >> t;
		long long hsh = 0;
		len.emplace_back(t.size());
		for(auto c : t){
			hsh *= sd;
			hsh += c - 'a' + 1;
			hsh %= MOD;
		}
		st[t.size()].insert(hsh);
	}
	sort(len.begin(), len.end());
	len.erase(unique(len.begin(), len.end()), len.end());
	h.emplace_back(0);
	pows[0] = 1;
	int idx = 0;
	for(char c : s){
		++idx;
		pows[idx] = pows[idx-1] * sd %MOD;
		h.emplace_back((h.back()*sd+c-'a'+1)%MOD);
		v.push_back(c);
		int l = h.size()-1;
		for(const int k : len){
			if(k > l){
				break;
			}
			long long hsh = h[l] - h[l-k] * pows[k];
			hsh %= MOD;			
			hsh += MOD;
			hsh %= MOD;
			if(st[k].count(hsh)){
				int p = k;
				while(p--){
					h.pop_back();
					v.pop_back();
				}
				break;
			}
		}
	}
	for(auto c : v){
		cout << c;
	}
}
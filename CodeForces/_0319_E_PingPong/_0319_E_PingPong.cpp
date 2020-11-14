
// Problem : E. Ping-Pong
// Contest : Codeforces - Codeforces Round #189 (Div. 1)
// URL : https://codeforces.com/contest/319/problem/E
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N,M;
bool used[1000000];
int par[1000000];
bool typ[500005];
int lft[500005], rht[500005];
vector<int> cmp;

int getrt(int n){
	return par[n] = (par[n] == n ? n : getrt(par[n]));
}

void cover(int sl, int sr, int idx, int v){
	//cout << idx << "\n";
	par[getrt(idx)] = getrt(v);
	if(sl == sr || used[idx]){
		return;
	}
	used[idx] = 1;
	cover(sl, (sl+sr)/2, 2*idx, v);
	cover((sl+sr)/2+1, sr, 2*idx+1, v);
}

void add(int sl, int sr, int l, int r, int idx, int v){
	if(l == sl && sr == r){
		//cout << l << " " << r << " " << idx << "\n";
		par[getrt(v)] = getrt(idx);
		if(!used[idx]){
			cover(sl, sr, idx, v);
		}
		return;
	}
	int mid = sl+sr>>1;
	if(r <= mid){
		add(sl, mid, l, r, 2*idx, v);
	}
	else if(l > mid){
		add(mid+1, sr, l, r, 2*idx+1, v);
	}
	else{
		add(sl, mid, l, mid, 2*idx, v);
		add(mid+1, sr, mid+1, r, 2*idx+1, v);
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	M = 4*N;
	for(int i = 1; i<=N; i++){
		int c;
		cin >> c >> lft[i] >> rht[i];
		if(c == 1){
			rht[i]--;
			cmp.push_back(lft[i]);
			cmp.push_back(rht[i]);
			typ[i] = 1;
		}
	}
	sort(cmp.begin(), cmp.end());
	cmp.erase(unique(cmp.begin(), cmp.end()), cmp.end());
	for(int i = 1; i<=M; i++){
		par[i] = i;
	}	
	for(int i = 1; i<=N; i++){
		if(typ[i]){
			++M;
			par[M] = M;
			//cout << "idx: " << M << "\n";
			lft[i] = lower_bound(cmp.begin(), cmp.end(), lft[i]) - cmp.begin() + 1;
			rht[i] = lower_bound(cmp.begin(), cmp.end(), rht[i]) - cmp.begin() + 1;
			cout << lft[i] << " " << rht[i] << "\n";
			add(1, cmp.size(), lft[i], rht[i], 1, M);
		}
		else{
			lft[i] += 4*N;
			rht[i] += 4*N;
			//cout << lft[i] << " " << rht[i] << "\n";
			cout << (getrt(lft[i]) == getrt(rht[i]) ? "YES\n" : "NO\n");
		}
	}
}
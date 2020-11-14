
// Problem : DMPG '19 G6 - Pairs
// Contest : DMOJ
// URL : https://dmoj.ca/problem/dmpg19g6
// Memory Limit : 256.000000 MB 
// Time Limit : 2000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int N;
vector<char> v;
pair<pair<int, int>, int> srt[200005];
int sa[200005];
int pos[200005];
int lcp[200005];
int par[200005];
int sz[200005];
long long MOD = 1e9+7;
long long ans[200005];
long long coe[200005];
long long con[200005];
long long tot[200005];
vector<pair<int, int>> edg;

long long add(long long a, long long b){
	return (a+b)%MOD;
}

long long mult(long long a, long long b){
	return (a*b)%MOD;
}

long long sub(long long a, long long b){
	a = add(a, -b);
	if(a < 0){
		a += MOD;
	}
	return a;
}

int getrt(int n){
	return par[n] = (par[n] == n ? n : getrt(par[n]));
}

void getpos(){
	sort(srt, srt+N);
	int idx = 0;
	for(int i = 0; i<N; i++){
		if(i){
			idx += (srt[i].first != srt[i-1].first);
		}
		pos[srt[i].second] = idx;
		sa[i] = srt[i].second;
	}
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 1; i<=N; i++){
		char c;
		cin >> c;
		v.emplace_back(c);
		srt[i-1].second = i-1;
		srt[i-1].first.first = v[i-1] - 'a' + 1;
	}
	v.emplace_back('$');
	srt[N].second = N;
	sz[N] = 1, par[N] = N;
	N++;
	getpos();
	for(int d = 0; d<20; d++){
		for(int i = 0; i<N; i++){
			srt[i].first.first = pos[srt[i].second];
			srt[i].first.second = pos[(srt[i].second+(1<<d))%N];
		}
		getpos();
	}
	int d = 0;
	for(int i = 0; i<N-1; i++){
		if(pos[i] == N-1){
			d = 0;
			continue;
		}
		d -= !!d;
		int j = sa[pos[i]+1];
		while(v[i+d] == v[j+d]){
			d++;
		}
		lcp[pos[i]] = d;
	}
	N--;
	for(int i = 1; i<=N; i++){
		ans[i] = mult(N-i+1, N-i+1);
		tot[i] = N - sa[i];
		sz[i] = 1;
		par[i] = i;
		if(i != N){
			edg.emplace_back(make_pair(lcp[i], i));
		}
	}
	sort(edg.begin(), edg.end(), greater<pair<int, int>>());
	for(auto p : edg){
		int idx = p.second;
		long long v = p.first;
		int lp = getrt(idx), rp = getrt(idx+1);
		long long tl = sub(tot[lp], mult(v, sz[lp]));
		long long tr = sub(tot[rp], mult(v, sz[rp]));
		ans[v] = add(ans[v], mult(2, mult(tl, tr)));
		long long c1 = mult(sz[lp], tot[rp]);
		long long c2 = mult(sz[rp], tot[lp]);
		long long c3 = mult(2, mult(sz[lp], sz[rp]));
		con[v] = add(con[v], 2*c1+2*c2+c3);
		coe[v] = add(coe[v], 2*c3);
		par[lp] = rp;
		sz[rp] += sz[lp];
		tot[rp] += tot[lp];
	}
	long long sum = 0;
	for(int i = N; i>=1; i--){
		con[i] = add(con[i], con[i+1]);
		coe[i] = add(coe[i], coe[i+1]);
		ans[i] = add(ans[i], con[i]);
		ans[i] = sub(ans[i], mult(coe[i], i));
		sum = add(ans[i], sum);
	}
	long long subst = 1LL*(N)*(N+1)/2%MOD;
	cout << sub(mult(subst, subst), sum) << "\n";
	for(int i = 1; i<=N; i++){
		cout << ans[i] << "\n";
	}
}

// Problem : D - Stamp Rally
// Contest : AtCoder - AtCoder Grand Contest 002
// URL : https://atcoder.jp/contests/agc002/tasks/agc002_d#
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N, M, Q;
int u[100005], v[100005], ans[100005], dsu[100005], sz[100005];
int a[100005], b[100005], t[100005], l[100005], r[100005];
vector<int> qu[100005];

int getrt(int n){
	return dsu[n] = (dsu[n] == n ? n : getrt(dsu[n]));
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> M;
	for(int i = 1; i<=M; i++){
		cin >> u[i] >> v[i];
	}
	cin >> Q;
	for(int q = 1; q<=Q; q++){
		cin >> a[q] >> b[q] >> t[q];
		l[q] = 1, r[q] = M;
		qu[(l[q]+r[q])/2].push_back(q);
	}
	for(int d = 0; d<20; d++){
		for(int n = 1; n<=N; n++){
			dsu[n] = n;
			sz[n] = 1;
		}
		for(int k = 1; k<=M; k++){
			if(getrt(u[k]) != getrt(v[k])){
				sz[getrt(u[k])] += sz[getrt(v[k])];
				dsu[getrt(v[k])] = getrt(u[k]);
			}
			while(qu[k].size()){
				int q = qu[k].back();
				qu[k].pop_back();
				if(getrt(a[q]) == getrt(b[q])){
					if(sz[getrt(a[q])] >= t[q]){
						ans[q] = k;
						r[q] = k-1;
					}
					else{
						l[q] = k+1;
					}
				}
				else{
					if(sz[getrt(a[q])] + sz[getrt(b[q])] >= t[q]){
						ans[q] = k;
						r[q] = k-1;
					}
					else{
						l[q] = k+1;
					}
				}
				if(l[q] <= r[q]){
					qu[(l[q]+r[q])/2].push_back(q);
				}
			}
		}
	}
	for(int q = 1; q<=Q; q++){
		cout << ans[q] << "\n";
	}
}
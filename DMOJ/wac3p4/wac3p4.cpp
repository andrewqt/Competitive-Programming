#include <bits/stdc++.h>

using namespace std;

int N, Q;
int par[100005];
int cnt[100005];
int numodd[100005];
int dgr[100005];

int getrt(int n){
	return par[n] = (par[n] == n ? n : getrt(par[n]));
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> Q;
	for(int i = 1; i<=N; i++){
		par[i] = i;
	}
	for(int q = 1; q<=Q; q++){
		int a, b, x;
		cin >> a >> b >> x;
		x &=1;
		dgr[a] ^= x;
		dgr[b] ^= x;
		if(x == 1){
			numodd[getrt(a)] += (dgr[a]&1 ? 1 : -1);
			numodd[getrt(b)] += (dgr[b]&1 ? 1 : -1);
		}
		if(getrt(a) != getrt(b)){
			numodd[getrt(a)] += numodd[getrt(b)];
			cnt[getrt(a)] += cnt[getrt(b)];
			par[getrt(b)] = getrt(a);
		}
		cnt[getrt(a)]++;
		if(cnt[getrt(a)] == q && numodd[getrt(a)] <= 2){
			cout << "YES\n";
		}
		else{
			cout << "NO\n";
		}
	}
}
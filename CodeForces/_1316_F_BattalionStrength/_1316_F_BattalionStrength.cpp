
// Problem : F. Battalion Strength
// Contest : Codeforces - CodeCraft-20 (Div. 2)
// URL : https://codeforces.com/contest/1316/problem/F
// Memory Limit : 256 MB
// Time Limit : 5000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N;
const long long MOD = 1e9+7;
long long pows[300005];
long long arr[300005];
long long inv[300005];

long long mult(long long a, long long b){
	return a*b%MOD;
}

long long add(long long a, long long b){
	return ((a+b)%MOD+MOD)%MOD;
}

struct FenwickTree{
	int bit[300005];
	long long query(int n){
		long long ret = 0;
		while(n){
			ret = add(ret, bit[n]);
			n -= n&-n;
		}
		return ret;
	}
	void upd(int n, long long v){
		while(n <= N){
			bit[n] = add(bit[n], v);
			n += n&-n;	
		}
	}
} lft, rht;

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	inv[0] = pows[0] = 1;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
		pows[i] = mult(pows[i-1], 2);
		inv[i] = mult(inv[i-1], (MOD+1)/2);
	}
	long long tot = 0;
	for(int i = 1; i<=N; i++){
		lft.upd(i, mult(pows[i-1], arr[i]));
		rht.upd(i, mult(pows[N-i], arr[i]));
		tot = add(tot, mult(lft.query(i-1), mult(pows[N-i], arr[i])));
	}
	cout << mult(tot, inv[N]) << "\n";
	int Q;
	cin >> Q;
	while(Q--){
		int i;
		long long x;
		cin >> i >> x;
		tot = add(tot, -mult(lft.query(i-1), mult(pows[N-i], arr[i])));
		tot = add(tot, -mult(add(rht.query(N), -rht.query(i)), mult(pows[i-1], arr[i])));
		lft.upd(i, -mult(pows[i-1], arr[i]));
		rht.upd(i, -mult(pows[N-i], arr[i]));
		arr[i] = x;
		lft.upd(i, mult(pows[i-1], arr[i]));
		rht.upd(i, mult(pows[N-i], arr[i]));
		tot = add(tot, mult(lft.query(i-1), mult(pows[N-i], arr[i])));
		tot = add(tot, mult(add(rht.query(N), -rht.query(i)), mult(pows[i-1], arr[i])));
		cout << tot << "\n";
		cout << mult(tot, inv[N]) << "\n";
	}
}
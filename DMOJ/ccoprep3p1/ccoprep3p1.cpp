
// Problem : CCO Preparation Test 3 - Primitive Pythagorean Pairs
// Contest : DMOJ
// URL : https://dmoj.ca/problem/ccoprep3p1
// Memory Limit : 128.000000 MB 
// Time Limit : 600.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int par[200005];
int sz[200005];
int dgr[200005];
int cyc[200005];

int getrt(int n){
	return par[n] = (par[n] == n ? n : getrt(par[n]));
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int mx = 0, k = 0, mxd = 0;
	for(int i = 1; i<=200000; i++){
		par[i] = i;
		sz[i] = 1;
	}
	for(int i = 1; i<=200000; i++){
		for(int j = i+1; j<=200000; j+=2){
			if(__gcd(i, j) != 1){
				continue;
			}
			long long a = 1LL*j*j-1LL*i*i;
			long long b = 2LL*i*j;
			if(a > 200000 || b > 200000){
				break;
			}
			else if(getrt(a) != getrt(b)){
				sz[getrt(b)] += sz[getrt(a)];
				cyc[getrt(b)] += cyc[getrt(a)];
				par[getrt(a)] = getrt(b);
				mx = max(mx, sz[getrt(b)]);
				if(mx == sz[getrt(b)]){
					k = getrt(b);
				}
			}
			else{
				cout << " " << i << " " << j << endl;
				cout << a << " " << b << endl;
				cyc[getrt(a)]++;
			}
			dgr[a]++;
			dgr[b]++;			
			mxd = max(max(dgr[a], dgr[b]), mxd);
		}
	}
	int mxc = 0;
	for(int i = 1; i<=200000; i++){
		if(cyc[i] && par[i] == i){
			cout << cyc[i] << " " << i << endl;
		}
	}
	//cout << mxc << endl;
	//cout << mxd << "\n";
	//cout << mx << "\n";
	//cout << k << "\n";
	/*
	for(int i = 1; i<=200000; i++){
		if(getrt(i) == k){
			cout << i << "\n";
		}
	}
	*/
	/*
	for(int i = 1; i<=200000; i++){
		if(getrt(i) == i){
			cout << i << " " << sz[i] << "\n";
		}
	}
	*/
}
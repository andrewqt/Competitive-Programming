#pragma GCC optimize "O3"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt,tune=native"
// Problem : F. Classical?
// Contest : Codeforces Round #613 (Div. 2)
// URL : https://codeforces.com/contest/1285/problem/F
// Memory Limit : 256.000000 MB 
// Time Limit : 1000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int N, M = 100000;
int sieve[100005];
bool exist[100005];
int arr[100005];
int mob[100005];
int tem[100005];
int mp[100005];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	fill(mob+1, mob+1+M, 1);
	fill(mp+1, mp+1+M, 1);
	for(int i = 2; i<=M; i++){
		if(!sieve[i]){
			for(int j = i; j<=M; j+=i){
				sieve[j]++;
				mp[j] *= i;
			}
			for(long long j = 1LL*i*i; j<=M; j+=1LL*i*i){
				mob[j] = 0;
			}
		}
	}
	long long ans = 0;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
		exist[arr[i]] = 1;
		ans = max(1LL*arr[i], ans);
	}
	for(long long g = 1; g<=M; g++){
		vector<int> v;
		for(int p = 1; p<=M/g; p++){
			if(mob[p]){
				tem[p] = 0;
			}
		}
		for(int i = g; i<=M; i += g){
			if(exist[i]){
				tem[mp[i/g]] = i;
			}
		}
		for(int p = 1; p<=M/g; p++){
			if(mob[p]){
				v.emplace_back(tem[p]);
			}
		}
		sort(v.begin(), v.end(), greater<int>());
		v.erase(unique(v.begin(), v.end()), v.end());
		int lst = v.size();
		for(int i = 0; i<v.size(); i++){
			int k = v[i];
			//cout << k << " " << g << "\n";
			for(int j = i+1; j<lst; j++){
				int n = v[j];
				//cout << n << "\n";
				if(!n){
					break;
				}
				if(__gcd(n, k) == g){
					//cout << n << " " << k << " " << g << "\n";
					ans = max(ans, 1LL*n*k/g);
					lst = j;
					break;
				}
			}
		}
	}
	cout << ans << "\n";
}
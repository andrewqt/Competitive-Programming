
// Problem : E - Flatten
// Contest : AtCoder Beginner Contest 152
// URL : https://atcoder.jp/contests/abc152/tasks/abc152_e
// Memory Limit : 1024.000000 MB 
// Time Limit : 2000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int N;
long long arr[10005];
int cnt[1000005];
long long MOD = 1e9+7;

long long mult(long long a, long long b){
	return (a*b)%MOD;
}

long long add(long long a, long long b){
	return (a+b)%MOD;
}

long long qikpow(long long a, long long b){
	if(!b){
		return 1;
	}
	long long ret = qikpow(a, b/2);
	ret = mult(ret, ret);
	if(b&1){
		ret = mult(ret, a);
	}
	return ret;
}

long long divd(long long a, long long b){
	return mult(a, qikpow(b, MOD-2));
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
		int t = arr[i];
		for(int j = 2; j<=sqrt(t); j++){
			if(t%j == 0){
				int k = 0;
				while(t%j == 0){
					k++;
					t /= j;
				}
				cnt[j] = max(cnt[j], k);
			}
		}
		if(t-1){
			cnt[t] = max(cnt[t], 1);
		}
	}
	long long p = 1;
	for(int i = 2; i<=1000000; i++){
		for(int j = 1; j<=cnt[i]; j++){
			p = mult(p, i);
		}
	}
	long long ans = 0;
	for(int i = 1; i<=N; i++){
		ans = add(ans, divd(p, arr[i]));
	}
	cout << ans << endl;
}
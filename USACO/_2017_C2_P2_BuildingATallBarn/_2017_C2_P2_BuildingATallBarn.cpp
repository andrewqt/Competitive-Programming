
// Problem : Problem 2. Building a Tall Barn
// Contest : USACO 2017 January Contest, Platinum
// URL : http://www.usaco.org/index.php?page=viewproblem2&cpid=697
// Memory Limit : 256.000000 MB 
// Time Limit : 4000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int N;
long long arr[100005];
long long K;

long long quad(long double d, long long n){
	return (long long) ((-d + sqrt(d*d+4*d*n))/(2*d));
}

long long solve(long double d){
	long long ret = 0;
	for(int i= 1; i<=N; i++){
		ret += quad(d, arr[i]);
	}
	//cout << d << " " << ret << endl;
	return ret;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("tallbarn.in", "r")){
		freopen("tallbarn.in", "r", stdin);
		freopen("tallbarn.out", "w", stdout);
	}
	cin >> N >> K;
	K -= N;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
	}
	long double ans = 0;
	long double l = 0, r = 1e13;
	for(int k = 0; k<200; k++){
		long double mid = (l+r)/2;
		if(solve(mid) <= K){
			r = mid;
			ans = mid;
		}
		else{
			l = mid;
		}
	}
	//cout << ans << endl;
	long long cnt = 0;
	long double tot = 0;
	for(int i = 1; i<=N; i++){
		long long x = quad(ans, arr[i]);
		tot += 1.0*arr[i]/(x+1);
		cnt += x;
	}
	//cout << cnt << endl;
	tot -= (K-cnt)*ans-0.5;
	cout << (long long) (tot) << endl;
}
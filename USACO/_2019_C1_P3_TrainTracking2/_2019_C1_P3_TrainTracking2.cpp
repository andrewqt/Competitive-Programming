
// Problem : Problem 3. Train Tracking 2
// Contest : USACO 2019 January Contest, Platinum
// URL : http://www.usaco.org/index.php?page=viewproblem2&cpid=902
// Memory Limit : 256.000000 MB
// Time Limit : 4000.000000 milisec
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int N, K;
int arr[100005];
int tbl[20][100005];
long long MOD = 1e9+7;
long long dp[100005];
long long pows[100005];

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

long long qikpow(long long b, long long e){
	if(!e){
		return 1;
	}
	long long ret = qikpow(b, e/2);
	ret = mult(ret, ret);
	if(e&1){
		ret = mult(ret, b);
	}
	return ret;
}

long long solve(int l, int r, int lidx, int ridx){
	//cout << l << " " << r << " " << lidx << " " << ridx << endl;
	if(lidx > ridx){
		return 1;
	}
	if(l > r){
		//cout << "hi" << endl;
		return 0;
	}
	int rng = ridx-lidx+1;
	int d = 31 - __builtin_clz(rng);
	int n = tbl[d][lidx];
	if(arr[n] > arr[tbl[d][ridx-(1<<d)+1]]){
		n = tbl[d][ridx-(1<<d)+1];
	}
	//cout << arr[n] << endl;
	int templft = n, temprht = n;
	int lft = n, rht = n;
	while(rht < r){
		if(arr[rht+1] == arr[lft]){
			rht++;
			temprht++;
		}
		else{
			break;
		}
	}
	rht += K-1;
	rht = min(rht, r);
	if(lft+K-1 < l){
		return 0;
	}
	lft = max(lft, l);
	//cout << lft << " " << rht << endl;
	dp[lft-1] = dp[lft] = 1;
	long long x = qikpow(arr[n]-1, K);
	for(int i = lft+1; i<=rht; i++){
		dp[i] = mult(arr[n], dp[i-1]);
		if(i - K - 1>= lft-1){
			dp[i] = sub(dp[i], mult(x, dp[i-K-1]));
		}
		//cout << i << " " << dp[i] << endl;
	}
	long long temp = 0, p = 1;
	for(int i = rht; i>=max(lft, rht-K+1); i--){
		temp = add(temp, mult(p, dp[i]));
		//cout << " " << dp[i] << " " << p << endl;
		p = mult(p, arr[n]-1);
		//cout << temp << " ";
	}
	//cout << "ans: " << temp << endl;
	return mult(temp, mult(solve(l, lft-1, lidx, templft-1), solve(rht+1, r, temprht+1, ridx)));
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("tracking2.in", "r")){
		freopen("tracking2.in", "r", stdin);
		freopen("tracking2.out", "w", stdout);
	}
	cin >> N >> K;
	for(int i = 1; i<=N-K+1; i++){
		cin >> arr[i];
		arr[i] = 1000000001 - arr[i];
		tbl[0][i] = i;
	}
	for(int d = 1; d<20; d++){
		for(int n = 1; n<=N-K+1-(1<<d)+1; n++){
			tbl[d][n] = (arr[tbl[d-1][n]] <= arr[tbl[d-1][n+(1<<(d-1))]] ? tbl[d-1][n] : tbl[d-1][n+(1<<(d-1))]);
		}
	}
	cout << solve(1, N, 1, N-K+1);
}

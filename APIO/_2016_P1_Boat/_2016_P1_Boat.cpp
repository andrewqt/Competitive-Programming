#include <bits/stdc++.h>

using namespace std;

int N;
const long long MOD = 1e9+7;
long long cst[505][1005];
long long dp[505][1005];
long long choose[505][505];
long long temp[505];
int lft[505], rht[505];
vector<int> cmp;

long long add(long long a, long long b){
	return (a+b)%MOD;
}

long long mult(long long a, long long b){
	return (a*b)%MOD;
}

long long qikpow(long long b, long long e){
	if(!e){
		return 1;
	}
	long long ret = qikpow(b, e>>1);
	ret = mult(ret, ret);
	if(e&1){
		ret = mult(ret, b);
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
	//cmp.push_back(0);
	for(int i= 1; i<=N; i++){
		cin >> lft[i] >> rht[i];
		cmp.push_back(lft[i]);
		cmp.push_back(rht[i]+1);
	}
	sort(cmp.begin(), cmp.end());
	cmp.erase(unique(cmp.begin(), cmp.end()), cmp.end());
	const int K = cmp.size()-1;
	for(int i = 1; i<=N; i++){
		lft[i] = lower_bound(cmp.begin(), cmp.end(), lft[i]) - cmp.begin();
		rht[i] = lower_bound(cmp.begin(), cmp.end(), rht[i]+1) - cmp.begin();
	}
	choose[0][0] = 1;
	for(int i = 0; i<=N; i++){
		choose[i][0] = 1;
		for(int k = 1; k<=N; k++){
			choose[i][k] = add(choose[i-1][k], choose[i-1][k-1]);
		}
	}
	temp[0] = 1;
	for(int k = 1; k<=K; k++){
		for(int n = 1; n<=N; n++){
			if(n > cmp[k]-cmp[k-1]){
				temp[n] = 0;
			}
			else{
				temp[n] = mult(temp[n-1], cmp[k]-cmp[k-1]-n+1);
				temp[n] = divd(temp[n], n);
			}
		}
		for(int n = 1; n<=N; n++){
			for(int a = 1; a<=n; a++){
				//cout << temp[a] << " " << choose[n-1][a-1] << "\n";
				cst[n][k] = add(cst[n][k], mult(choose[n-1][a-1], temp[a]));
			}
			//cout << n << " " << k << " " << cst[n][k] << "\n";
		}
	}
	for(int k = 0; k<=K; k++){
		dp[0][k] = 1;
	}
	for(int i = 1; i<=N; i++){
		for(int k = 1; k<=K; k++){
			dp[i][k] = dp[i][k-1];
			if(rht[i] >= k && lft[i] < k){
				int cnt = 0;
				for(int j = i; j; j--){
					if(rht[j] >= k && lft[j] < k){
						cnt++;
					}
					dp[i][k] = add(dp[i][k], mult(dp[j-1][k-1], cst[cnt][k]));
				}
			}
		}
	}
	long long ans = 0;
	for(int i = 1; i<=N; i++){
		//cout << dp[i][K] << " ";
		ans = add(ans, dp[i][K]);
	}
	cout << ans << "\n";
}
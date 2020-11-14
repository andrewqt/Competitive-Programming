#include <bits/stdc++.h>

using namespace std;

int N, K, Q;
int arr[50005];
long long ans[200005];
long long tbl[50005][20][20];
int lft[200005], rht[200005];
long long pre[25], suf[25];
long long MOD = 1e9+7;

long long add(long long a, long long b){
	a += b;
	if(a >= MOD){
		a -= MOD;
	}
	return a;
}

long long mult(long long a, long long b){
	return (a*b)%MOD;
}

void solve(int l, int r, vector<int> v){
	if(l > r || v.empty()){
		return;
	}
	int mid = l+r>>1;
	vector<int> lv, rv;
	for(int i = l-1; i<=r+1; i++){
		for(int k1 = 0; k1<K; k1++){
			for(int k2 = k1; k2<K; k2++){
				tbl[i][k1][k2] = 0;
			}
		}
	}
	for(int i = mid; i>=l; i--){
		int n = arr[i];
		for(int k1 = 0; k1<K; k1++){
			for(int k2 = k1; k2<K; k2++){
				tbl[i][k1][k2] = tbl[i+1][k1][k2];
			}
		}
		for(int k1 = n; k1<K; k1++){
			for(int k2 = k1; k2<K; k2++){
				tbl[i][n][k2] = add(tbl[i][n][k2], tbl[i+1][k1][k2]);
			}
		}
		tbl[i][n][n] = add(tbl[i][n][n], 1);
	}
	if(1){
		int n = arr[mid+1];	
		tbl[mid+1][n][n] = 1;
	}
	for(int i = mid+2; i<=r; i++){
		int n = arr[i];
		for(int k1 = 0; k1<K; k1++){
			for(int k2 = k1; k2<K; k2++){
				tbl[i][k1][k2] = tbl[i-1][k1][k2];
			}
		}
		for(int k1 = n; k1>=0; k1--){
			for(int k2 = k1; k2<=n; k2++){
				tbl[i][k1][n] = add(tbl[i-1][k1][k2], tbl[i][k1][n]);
			}
		}
		tbl[i][n][n] = add(tbl[i][n][n], 1);
	}
	for(int q : v){
		if(rht[q] < mid){
			lv.emplace_back(q);
		}
		else if(lft[q] > mid+1){
			rv.emplace_back(q);
		}
		else{
			ans[q] = 1;
			if(lft[q] <= mid && rht[q] > mid){
				for(int k = 0; k<K; k++){
					pre[k] = suf[k] = 0;
				}
				for(int k1 = 0; k1<K; k1++){
					for(int k2 = k1; k2<K; k2++){
						ans[q] += tbl[lft[q]][k1][k2];
						ans[q] += tbl[rht[q]][k1][k2];		
						pre[k2] += tbl[lft[q]][k1][k2];
						suf[k1] += tbl[rht[q]][k1][k2];
					}
				}
				for(int k = K-1; k>=0; k--){
					suf[k] += suf[k+1];
					pre[k] %= MOD;
					suf[k] %= MOD;
					ans[q] += mult(pre[k], suf[k]);
				}
			}
			else if(rht[q] > mid){
				for(int k1 = 0; k1<K; k1++){
					for(int k2 = k1; k2<K; k2++){
						ans[q] = add(ans[q], tbl[rht[q]][k1][k2]);
					}
				}
			}
			else {
				for(int k1 = 0; k1<K; k1++){
					for(int k2 = k1; k2<K; k2++){
						ans[q] = add(ans[q], tbl[lft[q]][k1][k2]);
					}
				}
			}
		}
	}
	solve(l, mid-1, lv);
	solve(mid+2, r, rv);
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("nondec.in", "r")){
		freopen("nondec.in", "r", stdin);
		freopen("nondec.out", "w", stdout);
	}
	cin >> N >> K;
	for(int i =1 ; i<=N; i++){
		cin >> arr[i];
		arr[i]--;
	}
	cin >> Q;
	vector<int> qu;
	for(int i = 1; i<=Q; i++){
		cin >> lft[i] >> rht[i];
		qu.emplace_back(i);
	}
	solve(1, N, qu);
	for(int i = 1; i<=Q; i++){
		cout << ans[i]%MOD << "\n";
	}
}
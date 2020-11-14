#pragma GCC optimize "O3"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt,tune=native"

#include <bits/stdc++.h>

using namespace std;

int N, L, Q;
short arr[1<<20];
int pre[2][1<<20];
short cnt[3];
int msk, t;
int ret;
vector<short> v;
vector<short> k;

/*
void rec(int n){
	if(n == -1){
		if(2 == t){
			ret += arr[msk];
		}
		else{
			const short c = ((__builtin_popcount(msk)&1)<<1)-1;
			ret += pre[1-t][msk]*c;
		}
		return;
	}
	msk <<= 1;	
	if(v[n] == 2){
		rec(n-1);
		msk |= 1;
		rec(n-1);
	}
	else{
		msk |= v[n];
		rec(n-1);
	}
	msk >>= 1;
}
*/

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> L >> Q;
	N = 1<<L;
	for(int m = 0; m<N; m++){
		char c;
		cin >> c;
		arr[m] = c-'0';
		pre[0][m] = arr[m];
	}
	for(int m = 0; m<N; m++){
		pre[1][m] = arr[m^(N-1)];
	}
	for(int d = 0; d<L; d++){
		for(int m = N-1; m>=0; m--){
			if((1<<d)&m){
				pre[0][m] += pre[0][m^(1<<d)];
				pre[1][m] += pre[1][m^(1<<d)];
			}			
		}
	}
	while(Q--){
		cnt[0] = cnt[1] = cnt[2] = 0;
		for(int k = 0; k<L; k++){
			char c;
			cin >> c;
			if(c == '?'){
				v.emplace_back(2);
			}
			else{
				v.emplace_back(c-'0');
			}
			cnt[v.back()]++;
		}
		ret = 0;
		if(cnt[2] <= cnt[0] && cnt[2] <= cnt[1]){
			t = 2;
		}
		else if(cnt[1] < cnt[0]){
			for(int k = 0; k<L; k++){
				if(v[k] == 2){
					v[k] = 1;
				}
				else if(v[k] == 1){
					v[k] = 2;
				}
				else{
					v[k] = 0;
				}
			}		
			t = 1;	
		}
		else{
			for(int k = 0; k<L; k++){
				if(v[k] == 2){
					v[k] = 1;
				}
				else if(v[k] == 1){
					v[k] = 0;
				}
				else{
					v[k] = 2;
				}
			}
			t = 0;
		}
		for(int b = 0; b<L; b++){
			//cout << v[b];
			if(v[b] == 2){
				k.emplace_back(L-b-1);
			}
			else if(v[b] == 1){
				msk |= (1<<(L-b-1));			
			}
		}
		/*
		cout << " ";
		for(int n : k){
			cout << n << " ";
		}
		*/
		const int S = 1<<k.size();
		for(int m = 0; m<S; m++){
			int temp = 0;
			for(int n = 0; n<k.size(); n++){
				if(m>>n&1){
					temp |= (1<<k[n]);
				}
			}
			if(t == 2){
				ret += arr[temp|msk];
			}
			else{
				ret += pre[1-t][msk|temp]*(((__builtin_popcount(msk|temp)&1)<<1)-1);
			}
		}
		msk = 0;
		//cout << t << " ";
		cout << abs(ret) << "\n";
		k.clear();
		v.clear();
	}
}

/*
#include <bits/stdc++.h>

using namespace std;

int N, L, Q, T;
int arr[1<<20];
int dp[60000];
vector<char> ternary[60000];
int pows[20];
int pre[1000005];
vector<char> qu[1000005];
int ans[1000005];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> L >> Q;
	N = 1<<L;
	for(int m = 0; m<N; m++){
		char c;
		cin >> c;
		arr[m] = c-'0';
	}
	int H = L/2;
	T = 1;
	pows[0] = 1;
	for(int k = 0; k<H; k++){
		T *= 3;
		pows[k+1] = pows[k] * 3;
	}
	for(int m = 0; m<T; m++){
		int temp = m;
		for(int k = 0; k<H; k++){
			ternary[m].emplace_back(temp%3);
			temp /= 3;
		}
	}
	for(int q = 1; q<=Q; q++){
		int t = 0;
		for(int i = 0; i<L; i++){
			char c;
			cin >> c;
			if(c == '?'){
				qu[q].emplace_back(2);
			}
			else{
				qu[q].emplace_back(c-'0');
			}
		}
		for(int k = 0; k<H; k++){
			t *= 3;
			t += qu[q][k];
		}
		reverse(qu[q].begin(), qu[q].end());
		pre[q] = t;
	}
	for(int m = 0; m<1<<(L-H); m++){
		fill(dp, dp+T, 0);
		for(int t = 0; t<T; t++){
			bool has2 = 0;
			int temp = 0;
			for(int h = 0; h<H; h++){
				if(ternary[t][h] == 2){
					has2 = 1;
					dp[t] = dp[t-pows[h]] + dp[t-pows[h]*2];
					break;
				}
				temp += (1<<h)*ternary[t][h];
			}
			if(!has2){
				dp[t] = arr[(temp<<(L-H)) + m];
			}
		}
		for(int q = 1; q<=Q; q++){
			bool good = 1;
			for(int b = 0; b<L-H; b++){
				if(qu[q][b] == 2 || qu[q][b] == ((m>>b)&1)){
					
				}
				else{
					good = 0;
					break;
				}
			}
			if(good){
				ans[q] += dp[pre[q]];
			}
		}
	}
	for(int q = 1; q<=Q; q++){
		cout << ans[q] << "\n";
	}
}
*/
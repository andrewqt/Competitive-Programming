
// Problem : B. Teams Formation
// Contest : Codeforces - Codeforces Round #443 (Div. 1)
// URL : https://codeforces.com/contest/878/problem/B
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N, K, M;
int arr[200005];//, pre[200005], suf[200005];
stack<pair<int, int>> stkp;
stack<int> stki;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> K >> M;
	long long T = 1LL*N*M;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
		pre[i] = suf[i] = arr[i];
		if(stkp.empty() || stkp.top().first != arr[i]){
			stkp.push(make_pair(arr[i], 1));
		}
		else{
			stkp.top().second++;
		}
		stki.push(i);
		if(stkp.top().second == K){
			stkp.pop();
			T -= 1LL*K*N;
			for(int k = 1; k<=K; k++){
				arr[stki.top()] = 0;
				//pre[stki.top()] = 0;
				//suf[stki.top()] = 0;
				stki.pop();
			}
		}
	}
	/*
	for(int i = 1; i<=N; i++){
		if(!arr[i]){
			continue;
		}
		if(stkp.empty() || stkp.top().first != arr[i]){
			break;
		}
		else{
			stkp.top().second++;
		}
		stki.push(i);
		if(stk.top().second == K){
			stkp.pop();
			T -= 1LL*K*(N-1);
			for(int k = 1; k<=K; k++){
				arr[stki.top()] = 0;
				stki.pop();
			}
		}
	}
	*/
	int L = 1, R = N;
	while(L <= R){
		
	}
}
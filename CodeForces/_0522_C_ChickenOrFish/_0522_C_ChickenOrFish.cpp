
// Problem : C. Chicken or Fish?
// Contest : Codeforces - VK Cup 2015 - Qualification Round 1
// URL : https://codeforces.com/contest/522/problem/C
// Memory Limit : 256 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int arr[100005];
bool ans[100005];
bool typ[100005];
int dish[100005];

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin >> T;
	while(T--){
		int N, M;
		cin >> N >> M;
		for(int i = 1; i<=M; i++){
			cin >> arr[i];
			ans[i] = 0;
		}
		for(int i = 1; i<N; i++){
			cin >> typ[i] >> dish[i];
		}
		bool seentyp0 = 0;
		int cnt = 0;
		for(int i = 1; i<N; i++){
			if(dish[i]){
				arr[dish[i]]--;
			}
			if(typ[i] == 0){
				if(!seentyp0){
					set<int> st;
					for(int j = i; j<N; j++){
						st.insert(dish[j]);
					}
					seentyp0 = 1;
					int idx = 0;
					for(int k = 1; k<=M; k++){
						if(!st.count(k) && (!idx || arr[idx] > arr[k])){
							idx = k;
						}
						if(!st.count(k) && arr[k] <= cnt){
							ans[k] = 1;
						}
					}
					cnt -= arr[idx];
				}
			}
			if(!dish[i]){
				cnt++;
			}
		}
		for(int k = 1; k<=M; k++){
			if(arr[k] <= cnt){
				ans[k] = 1;
			}
			cout << (ans[k] ? 'Y' : 'N');
		}
		cout << "\n";
	}
}
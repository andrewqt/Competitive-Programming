
// Problem : F. Cyclic Shifts Sorting
// Contest : Codeforces - Codeforces Round #653 (Div. 3)
// URL : https://codeforces.com/problemset/problem/1374/F
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int arr[505];
vector<int> v;

void f(int idx){
	swap(arr[idx+1], arr[idx+2]);
	swap(arr[idx], arr[idx+1]);
	v.push_back(idx+1);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin >> T;
	while(T--){
		int N;
		cin >> N;
		v.clear();
		for(int i = 0; i<N; i++){
			cin >> arr[i];
		}
		for(int i = 0; i<N-2; i++){
			int n = min_element(arr+i, arr+N) - arr;
			while(n-i>=2){
				f(n-2);
				//f(n-2);
				n -= 2;
			}
			while(n-i>=1){
				f(n-1);
				f(n-1);
				n--;
			}
		}
		for(int i = 0; i<N; i++){
			cout << arr[i] << " ";
		}
		cout << "\n";
		if(arr[N-2] > arr[N-1]){
			cout << -1 << "\n";
			continue;
		}
		cout << v.size() << "\n";
		for(int n : v){
			cout << n << " ";
		}
		cout << "\n";
	}
}
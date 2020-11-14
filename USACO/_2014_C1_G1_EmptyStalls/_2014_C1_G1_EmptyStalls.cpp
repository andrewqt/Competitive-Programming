#include <bits/stdc++.h>

using namespace std;

int N, K;
int arr[3000000];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("empty.in", "r")){
		freopen("empty.in", "r", stdin);
		freopen("empty.out", "w", stdout);
	}
	cin >> N >> K;
	while(K--){
		int X, Y, A, B;
		cin >> X >> Y >> A >> B;
		A %= N, B %= N;
		for(int i =1; i<=Y; i++){
			int idx = (1LL*A*i+B)%N;
			arr[idx] += X;
		}
	}
	int tot = 0;
	for(int i = 0; i<N; i++){
		tot += arr[i];
		if(tot){
			arr[i] = 1;
			tot--;
		}
	}
	for(int i = 0; i<N && tot; i++){
		if(!arr[i]){
			arr[i] = 1;
			tot--;
		}
	}
	cout << min_element(arr, arr+N)-arr << endl;
}
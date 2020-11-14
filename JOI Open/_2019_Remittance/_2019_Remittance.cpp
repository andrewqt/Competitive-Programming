#include <bits/stdc++.h>

using namespace std;

int N;
long long arr[1000005], brr[1000005];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 0; i<N; i++){
		cin >> arr[i] >> brr[i];
	}
	int cnt = 0;
	for(int i = 0; cnt <= N; cnt++, i++, i%=N){
		if(arr[i] == 1 && brr[i] == 0 || arr[i] <= brr[i]){
			cnt++;	
		}
		else{
			long long d = arr[i]-brr[i];
			d += d&1;
			if(d > arr[i]){
				d-=2;
			}
			arr[i] -= d;			
			arr[(i+1)%N] += d>>1;
			cnt = 0;
		}
	}
	for(int i = 0; i<N; i++){
		if(arr[i] != brr[i]){
			cout << "No";
			return 0;
		}
	}
	cout << "Yes";
}
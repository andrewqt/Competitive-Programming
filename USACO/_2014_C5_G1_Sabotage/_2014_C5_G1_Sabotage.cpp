#include <bits/stdc++.h>

using namespace std;

int N;
int arr[100005];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("sabotage.in", "r")){
		freopen("sabotage.in", "r", stdin);
		freopen("sabotage.out", "w", stdout);
	}
	cin >> N;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
	}
	long double l = 0, r = 10000, ans = 0;
	for(int t = 0; t<100; t++){
		long double mid = (l+r)/2.0;
		long double mx = INT_MIN;
		long double tot = 0;
		long double crnt = 0;
		for(int i = 1; i<=N; i++){
			tot += arr[i];
			tot -= mid;
		}
		for(int i = 2; i<N; i++){
			crnt += arr[i];
			crnt -= mid;
			mx = max(mx, crnt);
			if(crnt < 0){
				crnt = 0;
			}
		}
		//cout << mid << " " << tot << " " << mx << " " << (tot-crnt <= 0) << "\n";
		if(tot - mx <= 0){
			r = mid;
			ans = mid;
		}
		else{
			l = mid;
		}
	}
	cout << fixed << setprecision(3) << ans << "\n";
}
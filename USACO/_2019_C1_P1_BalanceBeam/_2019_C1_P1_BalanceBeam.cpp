#include <bits/stdc++.h>

using namespace std;

int N;
long long arr[100005];
vector<int> hull;

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("balance.in", "r")){
		freopen("balance.in", "r", stdin);
		freopen("balance.out", "w", stdout);
	}
	cin >> N;
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
	}
	for(int i = 0; i<=N+1; i++){
		while(hull.size() >= 2){
			int idx1 = hull.back(), idx2 = hull[hull.size()-2];
			if((arr[idx1]-arr[idx2])*(i-idx1)-(arr[i]-arr[idx1])*(idx1-idx2) < 0){
				hull.pop_back();
			}			
			else{
				break;
			}
		}
		hull.push_back(i);
	}
	int idx = 1;
	for(int i = 1; i<=N; i++){
		unsigned long long d = (hull[idx]-i)*(arr[hull[idx-1]])+(i-hull[idx-1])*(arr[hull[idx]]);
		d *= 100000;
		d /= hull[idx]-hull[idx-1];
		cout << d << "\n";
		if(hull[idx] == i){
			idx++;
		}
	}
}
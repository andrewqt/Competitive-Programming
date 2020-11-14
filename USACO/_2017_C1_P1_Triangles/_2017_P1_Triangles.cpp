
// Problem : Problem 1. Lots of Triangles
// Contest : USACO 2016 December Contest, Platinum
// URL : http://www.usaco.org/index.php?page=viewproblem2&cpid=672
// Memory Limit : 256.000000 MB 
// Time Limit : 4000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int N;
pair<int, int> arr[1000];
int sum[305][305];
int ans[305];

long long crs(pair<long long, long long> p, pair<long long, long long> q){
	return p.first*q.second - q.first*p.second;
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("triangles.in", "r")){
		freopen("triangles.in", "r", stdin);
		freopen("triangles.out", "w", stdout);
	}
	cin >> N;
	for(int i =1 ; i<=N ;i++){
		cin >> arr[i].first >> arr[i].second;
	}	
	sort(arr+1, arr+1+N);
	for(int i = 1; i<=N; i++){
		for(int j = i+1; j<=N; j++){
			for(int k = 1; k<=j; k++){
				if(arr[k].first >= arr[i].first && arr[k].first < arr[j].first){
					if(crs({arr[j].first-arr[i].first, arr[j].second-arr[i].second}, {arr[k].first-arr[j].first, arr[k].second-arr[j].second}) <= 0){
						sum[i][j]++;
						//cout << k << endl;
					}
				}
			}
			//cout << i << " " << j << " " << sum[i][j] << endl;
		}
	}
	for(int i = 1; i<=N; i++){
		for(int j = i+1; j<=N; j++){
			for(int k = j+1; k<=N; k++){
				int s;
				if(crs({arr[k].first-arr[i].first, arr[k].second-arr[i].second}, {arr[j].first-arr[k].first, arr[j].second-arr[k].second}) <= 0){
					s = sum[i][k] - sum[i][j] - sum[j][k];
				}
				else{
					s = sum[i][j] + sum[j][k] - 1 - sum[i][k];
				}
				ans[s]++;
			}
		}
	}
	for(int k = 0; k<N-2; k++){
		cout << ans[k] << "\n";
	}
}
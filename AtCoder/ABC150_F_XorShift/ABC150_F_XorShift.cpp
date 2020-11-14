#include <bits/stdc++.h>

using namespace std;

int N;
int arr[400005], brr[400005];
int lps[400005];
bool ok[35][400005];

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;	
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
	}
	for(int i = 1; i<=N; i++){
		cin >> brr[i];
		brr[i+N] = brr[i];
	}
	lps[1] = 1;
	for(int b = 0; b<30; b++){
		for(int k = 0; k<=1; k++){
			for(int i = 2, j = 1; i<=N; ){
				if((arr[i]&(1<<b)) == (arr[j]&(1<<b))){
					lps[i++] = ++j;
				}
				else if(j-1){
					j = lps[j-1];
				}
				else{
					lps[i++] = j;
				}	
			}
			for(int i = 1, j = 1; i<2*N; ){
				if((brr[i]&(1<<b)) == ((arr[j]&(1<<b))^(k<<b))){
					i++, j++;
					if(j == N+1){
						j = lps[N];
						ok[b][i-N] = 1;
					}
				}
				else if(j-1){
					j = lps[j-1];
				}
				else{
					i++;
				}
			}
		}
	}
	vector<pair<int, int>> v;
	for(int i = 1; i<=N; i++){
		int cnt = 0;
		for(int b = 0; b<30; b++){
			cnt += ok[b][i];
		}
		if(cnt == 30){
			v.push_back({(N-i+1)%N, (arr[1]^brr[i])});
		}
	}
	sort(v.begin(), v.end());
	for(auto p : v){
		cout << p.first << " " << p.second << "\n";
	}
}

/*

*/
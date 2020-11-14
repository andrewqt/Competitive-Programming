#include <bits/stdc++.h>

using namespace std;

int N, K;
int lftmst[4][200005];
string s;
const string joi = "JOI";

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> K >> s;
	for(int i = 1; i<=N; i++){
		lftmst[0][i] = i;
	}
	for(int t = 1; t<=3; t++){
		int cnt = 0;
		for(int l = 1, r = 1; r<=N; r++){
			if(s[r-1] == joi[t-1]){
				cnt++;
			}
			while(cnt > K){
				cnt -= (s[l-1] == joi[t-1]);
				l++;
			}
			while(cnt == K && l < r && s[l-1] != joi[t-1]){
				l++;
			}
			//cout << l << " " << r << "\n";
			if(cnt == K){
				lftmst[t][r] = lftmst[t-1][l];
			}
			//cout << lftmst[t][r] << " " << r << "\n";
		}
		//cout << "\n";
	}
	int rng = N+2;
	for(int i = 1; i<=N; i++){
		if(lftmst[3][i]) {
			rng = min(rng, i-lftmst[3][i]+1);
		}
	}
	if(rng == N+2){
		rng = -1;
	}
	else{
		rng -= 3*K;
	}
	cout << rng << "\n";
}
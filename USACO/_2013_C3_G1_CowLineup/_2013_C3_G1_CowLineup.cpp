#include <bits/stdc++.h>

using namespace std;

queue<int> qu;
map<int, int> cnt;

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	if(fopen("lineup.in", "r")){
		freopen("lineup.in", "r", stdin);
		freopen("lineup.out", "w", stdout);
	}
	int N, K;
	cin >> N >> K;
	K++;
	int ans = 0;
	while(N--){
		int n;
		cin >> n;
		qu.push(n);
		cnt[n]++;
		if(cnt[n] == 1){
			K--;
		}
		while(K < 0){
			int m = qu.front();
			cnt[m]--;
			K += !cnt[m];
			qu.pop();
		}
		ans = max(ans, cnt[n]);
	}
	cout << ans << "\n";
}
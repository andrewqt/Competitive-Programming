#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("no-stack-protector")
#include <bits/stdc++.h>

using namespace std;

pair<pair<int, int>, int> arr[4005];
pair<pair<pair<int, int>, int>, double> srt[8005];

long long crs(pair<int, int> a, pair<int, int> b){
	//cout << "cross: " << 1LL*(b.first-c.first)*(a.second-c.second) - 1LL*(b.second-c.second)*(a.first-c.first) << "\n";
	return 1LL*(b.first)*(a.second) - 1LL*(b.second)*(a.first);
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int N;
	cin >> N;
	for(int i = 1; i<=N; i++){
		cin >> arr[i].first.first >> arr[i].first.second >> arr[i].second;
	}
	int ans = INT_MIN;
	for(int p = 1; p<=N; p++){
		for(int i = 1; i<=N; i++){
			if(i == p){
				continue;
			}
			pair<pair<int, int>, int> k = arr[i];
			k.first.first -= arr[p].first.first;
			k.first.second -= arr[p].first.second;
			srt[i-1-(i > p)] = {k, atan2(k.first.second, k.first.first)};
		}
		sort(srt, srt+N-1, [](auto a, auto b){
			return  a.second < b.second;
		});
		for(int i = 0; i<N-1; i++){
			srt[i+N-1] = (srt[i]);
		}
		int l = 0, r = 0;
		int tot = arr[p].second;
		while(r < N-1 && crs(srt[0].first.first, srt[r].first.first) <= 0){
			tot += srt[r++].first.second;
		}
		ans = max(ans, tot);
		for(; r<2*N-2; r++){
			while(r-l+1 > N-1 || (crs(srt[l].first.first, srt[r].first.first) > 0)){
				assert(l <= r);
				int c = l;
				while(crs(srt[c].first.first, srt[l].first.first) == 0){
					tot -= srt[l++].first.second;
				}
				ans = max(ans, tot);
			}
			tot += srt[r].first.second;
			while(r+1 <2*N-2 && crs(srt[r].first.first, srt[r+1].first.first) == 0){
				tot += srt[++r].first.second;
			}
			ans = max(ans, tot);
		}
	}
	cout << ans;
}
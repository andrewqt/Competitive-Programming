
// Problem : PIB '20 P7 - Karnaugh Maps
// Contest : DMOJ
// URL : https://dmoj.ca/problem/pib20p7
// Memory Limit : 128 MB
// Time Limit : 500 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

int N;
int arr[50005];
int srt[50005];
int ans[50005];
vector<int> v;
bool sieve[50005];
vector<int> cand;
int temp[50005];
int cnt[50005];
vector<int> pos[50005];
int idx[50005];

void out(){
	for(int i = 1; i<=N; i++){
		cout << v[ans[i]-1] << " ";
	}
	cout << "\n";
	exit(0);
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	for(int i = 2; i<=N; i++){
		if(!sieve[i]){
			cand.emplace_back(i);
		}
		for(int j = i*2; j<=N; j+=i){
			sieve[j] = 1;
		}
	}
	for(int i = 1; i<=N; i++){
		cin >> arr[i];
		v.push_back(arr[i]);
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	for(int i = 1; i<=N; i++){
		arr[i] = lower_bound(v.begin(), v.end(), arr[i]) - v.begin() + 1;
		srt[i] = arr[i];
		ans[i] = arr[i];
		pos[arr[i]].emplace_back(i);
	}
	sort(srt + 1, srt+1+N);
	/*
	for(int i = 1; i<=N; i++){
		if(arr[i] != srt[i]){
			for(int j = i+2; j<=N; j++){
				if(arr[j] == srt[i]){
					int k = j-i;
					for(int p = 2; p<=sqrt(k); p++){
						if(k%p == 0){
							while(k%p == 0){
								k /= p;
							}
							cand.emplace_back(p);
						}
					}
					if(k > 1){
						cand.emplace_back(k);
					}
				}
			}
			if(cand.empty()){
				for(int j = i+2; j<=N; j++){
					if(arr[j] == srt[i]+1){
						int k = j-i;
						for(int p = 2; p<=sqrt(k); p++){
							if(k%p == 0){
								while(k%p == 0){
									k /= p;
								}
								cand.emplace_back(p);
							}
						}
						if(k > 1){
							cand.emplace_back(k);
						}
					}
				}
			}
			if(cand.empty()){
				out();
			}
			break;
		}
	}
	sort(cand.begin(), cand.end());
	cand.erase(unique(cand.begin(), cand.end()), cand.end());
	*/
	for(int p : cand){
		fill(idx, idx+p, 0);
		idx[0]++;
		for(int i = 1; i<=v.size(); i++){
			for(int k : pos[i]){
				int t = k%p;
				temp[idx[t]*p+t] = i;
				idx[t]++;
			}
		}
		for(int i = 1; i<=N; i++){
			if(temp[i] < ans[i]){
				for(; i<=N; i++){
					swap(temp[i], ans[i]);
				}
				break;
			}
			else if(temp[i] > ans[i]){
				break;
			}
		}
	}
	out();
}
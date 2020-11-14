
// Problem : UTS Open '21 P2 - Attraction
// Contest : DMOJ
// URL : https://dmoj.ca/problem/utso21p2
// Memory Limit : 64 MB
// Time Limit : 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>

using namespace std;

priority_queue<int> pq;

void gen(int N){
	for(int i = 1; i<=N; i++){
		int mx = 0;
		for(int j = 1; j<=i; j++){
			int cnt = 0;
			for(int k = 1; k<=i; k++){
				if(abs(k-j) < k && abs(k-j) < i+1-k){
					cnt++;
				}
			}
			mx = max(mx, cnt);	
		}
		cout << i << " " << mx << "\n";
		mx = 0;
		for(int j = 1; j<=i; j++){
			for(int jj = j+1; jj<=i; jj++){
				int cnt = 0;
				for(int k = 1; k<=i; k++){
					if(((abs(k-j) < k && abs(k-j) < i+1-k) || (abs(k-jj) < k && abs(k-jj) < i+1-k)) && abs(k-j) != abs(k-jj)){
						cnt++;
					}
				}
				//cout << cnt << " " << j << " " << jj << "\n";
				mx = max(mx, cnt);
			}
		}
		cout << mx << "\n";
		mx = 0;
		for(int j = 1; j<=i; j++){
			for(int jj = j+1; jj<=i; jj++){
				for(int jjj = jj+1; jjj<=i; jjj++){
					int cnt = 0;					
					for(int k = 1; k<=i; k++){
						int bst = min({abs(k-jjj), abs(k-j), abs(k-jj)});
						if(bst < k && bst < i+1-k){
							int c = abs(k-j) == bst;
							c += abs(k-jj) == bst;
							c += abs(k-jjj) == bst;
							if(c == 1){
								cnt++;
							}
						}
						/*
						if(((abs(k-jjj) < k && abs(k-jjj) < i+1-k) || (abs(k-j) < k && abs(k-j) < i+1-k) || (abs(k-jj) < k && abs(k-jj) < i+1-k)) && abs(k-j) != abs(k-jj) && abs(k-j) != abs(k - jjj)){
							cnt++;
						}
						*/
					}
					//cout << cnt << " " << j << " " << jj << "\n";
					mx = max(mx, cnt);
				}
			}
		}
		cout << mx << "\n";
	}
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin >> T;
	//gen(20);
	while(T--){
		int N, A, B;
		cin >> N >> A >> B;
		vector<int> v;
		for(int i = 0; i<A; i++){
			int n;
			cin >> n;
			v.push_back(n);
		}
		sort(v.begin(), v.end());
		pq.push(v[0] - 1);
		pq.push(N - v[A-1]);
		for(int i = 1; i<A; i++){
			int rng = v[i] - v[i-1] - 1;
			if(rng == 0){
				
			}
			else if(rng == 1){
				pq.push(1);
			}
			else if(rng == 3){
				pq.push(2);
				pq.push(-1);
			}
			else if(rng%2 == 1){
				pq.push((rng+1)/2);
				pq.push(rng-1 - (rng+1)/2);
				pq.push(1);
			}
			else{
				pq.push(rng/2);
				pq.push(rng - rng/2);
			}
		}
		long long ans = 0;
		while(pq.size() && B--){
			//cout << pq.top() << "\n";
			if(pq.top() == 0){
				pq.pop();
				B++;
			}
			else if(pq.top() == -1){
				pq.pop();
				pq.push(1);
			}
			else{
				ans += pq.top();
				pq.pop();
			}
		}
		while(pq.size()){
			pq.pop();
		}
		cout << ans << "\n";
	}
}
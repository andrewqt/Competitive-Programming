
// Problem : CCO '15 P6 - Eggscavation
// Contest : DMOJ
// URL : https://dmoj.ca/problem/cco15p6
// Memory Limit : 512.000000 MB 
// Time Limit : 10000.000000 milisec 
// Powered by CP Editor (https://github.com/coder3101/cp-editor)

#include <bits/stdc++.h>

using namespace std;

int N, K, M;
set<int> st[2505];
int diff[2505][2505];
pair<int, int> arr[5];
int bit[100005];

void upd(int p, int v){
	assert(p >= 0);
	if(!p){
		return;
	}
	while(p <= M){
		bit[p] += v;
		p += p&-p;
	}
}

int query(int p){
	int ret = 0;
	while(p){
		ret += bit[p];
		p -= p&-p;
	}
	return ret;
}

using namespace std;

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N >> K >> M;
	for(int i = 1; i<=N-K+1; i++){
		for(int j = 1; j<=N-K+1; j++){
			st[i].insert(j);
		}
	}
	for(int x = 0; x<M; x++){
		int n;
		cin >> n;
		for(int i = 0; i<n; i++){
			cin >> arr[i].first >> arr[i].second;
		}
		for(int m = 1; m<1<<n; m++){
			int x1 = 0, y1 = 0, x2 = N-K+1, y2 = N-K+1;
			for(int i = 0; i<n; i++){
				if((m>>i)&1){
					x1 = max(x1, arr[i].first-K+1);
					y1 = max(y1, arr[i].second-K+1);
					x2 = min(x2, arr[i].first);
					y2 = min(y2, arr[i].second);
				}
			}
			x1 = max(1, x1);
			y1 = max(1, y1);
			x2 = min(x2, N-K+1);
			y2 = min(y2, N-K+1);
			int coe = -1;
			if(__builtin_popcount(m)&1){
				coe = 1;
			}
			if(x1 <= x2 && y1 <= y2){
				diff[x1][y1] += coe;
				diff[x1][y2+1] -= coe;
				diff[x2+1][y1] -= coe;
				diff[x2+1][y2+1] += coe;
			}
		}
	}
	for(int i = 1; i<=N-K+1; i++){
		for(int j = 1; j<=N-K+1; j++){
			diff[i][j] += diff[i-1][j] + diff[i][j-1] - diff[i-1][j-1];
			//cout << diff[i][j] << " ";
			upd(diff[i][j], 1);
		}
		//cout << "\n";
	}
	int Q;
	cin >> Q;
	while(Q--){
		int c;
		cin >> c;
		if(c == 1){
			int x, y;
			cin >> x >> y;
			for(int i = max(x-K+1, 1); i<=min(N-K+1, x); i++){
				while(st[i].size()){
					auto it = st[i].lower_bound(y-K+1);
					if(it != st[i].end() && *it <= y){
						int z = *it;
						upd(diff[i][z], -1);
						st[i].erase(it);
					}
					else{
						break;
					}
				}
			}
		}
		else{
			int v;
			cin >> v;
			long double num = 0;
			if(v <= M){
				num = query(M) - query(v-1);
			}
			cout << num/((N-K+1)*(N-K+1)) << "\n";
		}
	}
}
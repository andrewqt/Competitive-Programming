//#include <tournament.h>
#include <bits/stdc++.h>

using namespace std;

int N;
int bit[100005];
bool good[100005];
vector<int> lft[100005];
vector<int> rht[100005];
set<int> st;

void upd(int p, int v){
	for(int i = p; i<=N; i+=i&-i){
		bit[i] += v;
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

int clmb(int lim){
	int tot = 0;
	int p = 0;
	for(int b = 16; b>=0; b--){
		if((1<<b)+p <= N && tot + bit[(1<<b)+p] < lim){
			tot += bit[(1<<b)+p];
			p += (1<<b);
		}
	}
	return p+1;
}

int GetBestPosition(int NN, int Q, int K, int arr[], int L[], int R[]){
	N = NN;
	for(int i = 1; i<=N; i++){
		upd(i, 1);
	}
	for(int q = 0; q<Q; q++){
		int rng = R[q]-L[q];
		int s = L[q]+2;
		L[q] = clmb(L[q]+1);
		while(rng--){
			int p = clmb(s);
			upd(p, -1);
		}
		R[q] = clmb(s)-1;
		lft[L[q]].push_back(q);
		rht[R[q]].push_back(q);
		//cout << L[q] << " " << R[q] << endl;
	}
	fill(bit, bit+1+N, 0);
	for(int i = 1; i<N; i++){
		if(arr[i-1] > K){
			upd(i, 1);
		}
	}
	for(int q = 0; q<Q; q++){
		good[q] = (query(R[q]-1) == query(L[q]-1));
	}
	fill(bit, bit+1+N, 0);
	int ans = -1, idx = 0;
	for(int i = 1; i<=N; i++){
		for(int q : lft[i]){
			if(good[q]){
				upd(q+1, 1);
			}
			else{
				st.insert(q+1);
			}
		}
		if(st.empty()){
			if(ans < query(Q)){
				ans = query(Q);
				idx = i-1;
			}
		}
		else{
			if(ans < query(*st.begin())){
				ans = query(*st.begin());
				idx = i-1;
			}
		}
		for(int q : rht[i]){
			if(good[q]){
				upd(q+1, -1);
			}
			else{
				st.erase(q+1);
			}
		}
	}
	return idx;
}
/*
int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int N, Q, K;
	cin >> N >> Q >> K;
	int LL[Q], RR[Q], AA[N-1];
	for(int i = 0; i<N-1; i++){
		cin >> AA[i];
	}
	for(int i = 0; i<N; i++){
		cin >> LL[i] >> RR[i];
	}
	cout << GetBestPosition(N, Q, K, AA, LL, RR) << endl;
}
*/
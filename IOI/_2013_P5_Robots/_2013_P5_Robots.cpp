#include "robots.h"
#include <bits/stdc++.h>

using namespace std;

int A, B, N;
pair<int, int> arr[1000005];
int w[50005], s[50005];

bool chk(int k){
	int idx = 0;
	priority_queue<int> pq;
	for(int i = 1; i<=A; i++){
		while(idx < N && arr[idx+1].first < w[i]){
			pq.push(arr[++idx].second);
		}
		int c = k;
		while(c && pq.size()){
			c--;
			pq.pop();
		}
	}
	while(idx < N){
		pq.push(arr[++idx].second);
	}
	for(int i = 1; i<=B; i++){
		int c = k;
		while(c && pq.size()){
			if(pq.top() >= s[i]){
				return 0;
			}
			pq.pop();
			c--;
		}
	}
	return pq.empty();
}

int putaway(int P, int Q, int M, int W[], int S[], int X[], int Y[]){
	A = P, B = Q, N = M;
	for(int i = 1; i<=N; i++){
		arr[i].first = X[i-1];
		arr[i].second = Y[i-1];
	}
	for(int i = 1; i<=A; i++){
		w[i] = W[i-1];
	}
	for(int j = 1; j<=B; j++){
		s[j] = S[j-1];
	}
	sort(arr+1, arr+1+N);
	sort(w+1, w+1+A);
	sort(s+1, s+1+B);
	reverse(s+1, s+1+B);
	int l = 1, r = N, ret = -1;
	while(l <= r){
		int mid = l+r>>1;
		if(chk(mid)){
			r = mid - 1;
			ret = mid;
		}
		else{
			l = mid + 1;
		}
	}
	return ret;
}

/*
int sampleX[3] = {6, 2, 9};
int sampleY[2] = {4, 7};
int sampleW[10] = {4, 8, 2, 7, 1, 5, 3, 8, 7, 10};
int sampleS[10] = {6, 5, 3, 9, 8, 1, 3, 7, 6, 5};
*/
/*
int sampleX[2] = {2, 5};
int sampleY[1] = {2};
int sampleW[10] = {3, 5, 2};
int sampleS[10] = {1, 3, 2};
*/
/*
int main(){

	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//cout << putaway(3, 2, 10, sampleX, sampleY, sampleW, sampleS) << "\n";
	cout << putaway(2, 1, 3, sampleX, sampleY, sampleW, sampleS) << "\n";
}
*/
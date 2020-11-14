#include "crocodile.h"
#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> graph[100005];
long long dist[2][100005];
bool done[100005];
int cnt[100005];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

int travel_plan(int N, int M, int R[][2], int W[], int K, int E[]){
    for(int i= 0; i<M; i++){
        graph[R[i][0]].push_back({R[i][1], W[i]});
    	graph[R[i][1]].push_back({R[i][0], W[i]});
	}
	for(int i = 0; i<N; i++){
		dist[0][i] = dist[1][i] = LLONG_MAX/2;
	}
	for(int i = 0; i<K; i++){
		dist[0][E[i]] = dist[1][E[i]] = 0;
		pq.push({0, E[i]});
	}
	while(pq.size()){
		auto p = pq.top();
		pq.pop();
		if(done[p.second]){
			continue;
		}
		int n = p.second;
		done[n] = 1;
		//cout << n << " " << dist[0][n] << " " << dist[1][n] << "\n";
		for(auto e : graph[n]){
			//cout << e.first << " " << e.second << "\n";
			if(dist[0][e.first] >= dist[1][n] + e.second){
				dist[1][e.first] = dist[0][e.first];
				dist[0][e.first] = dist[1][n] + e.second;
				cnt[e.first]++;
				if(cnt[e.first] >= 2){
					pq.push({dist[1][e.first], e.first});
				}
			}
			else if(dist[1][e.first] > dist[1][n] + e.second){
				dist[1][e.first] = dist[1][n] + e.second;
				cnt[e.first]++;
				if(cnt[e.first] >= 2){
					pq.push({dist[1][e.first], e.first});
				}
			}
		}
	}
	if(dist[1][0] == INT_MAX/2){
		dist[1][0] = -1;
	}
	return dist[1][0];
}
/*
int sampleR[4][2] = {{0, 1}, {0, 2}, {3, 2}, {2, 4}};
int sampleL[4] = {2, 3, 1, 4};
int sampleP[3] = {1, 3, 4};
*/
/*
int sampleR[7][2] = {{0, 2}, {0, 3}, {3, 2}, {2, 1}, {0, 1}, {0, 4}, {3, 4}};
int sampleL[7] = {4, 3, 2, 10, 100, 7, 9};
int sampleP[2] = {1, 3};

int main(){
	cout << travel_plan(5, 7, sampleR, sampleL, 2, sampleP);
}
*/

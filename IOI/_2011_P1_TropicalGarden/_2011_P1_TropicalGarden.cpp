#include "garden.h"
#include "gardenlib.h"
#include <bits/stdc++.h>

using namespace std;

int N, M, P, Q;
int beau[2][150005];
int nxt[300005];
bool island[300005];
int hasP[300005];
int cyc[2];
int dist[2][300005];
int par[2][300005];
int rem[2][300005];
vector<int> graph[300005];
vector<int> c[2];
/*
void answer(int X){
	cout << X << "\n";
}
*/
void dfs(int n, int b, int rt){
	hasP[n] |= b;
	for(int e : graph[n]){
		if(!(hasP[e]&b)){
			dist[b-1][e] = dist[b-1][n] + 1;
			par[b-1][e] = n;
			dfs(e, b, rt);
		}
		else{
			cyc[b-1] = dist[b-1][n] + 1;
			c[b-1].emplace_back(e);
			int crnt = e;
			int cnt = 0;
			while(crnt != rt){
				rem[b-1][crnt] = ++cnt;
				crnt = par[b-1][crnt];
				c[b-1].emplace_back(e);
			}
		}
	}
}

void bfs(int b){
	queue<int> qu;
	for(int n : c[b]){
		dist[b][n] = 0;
		par[b][n] = n;
		qu.push(n);
	}
	while(qu.size()){
		int n = qu.front();
		qu.pop();
		for(int e : graph[n]){
			if(dist[b][e] > dist[b][n] + 1){
				dist[b][e] = dist[b][n] + 1;
				par[b][e] = par[b][n];
				qu.push(e);
			}
		}
	}
}

void count_routes(int NN, int MM, int PP, int R[][2], int QQ, int G[]){
	N = NN, M = MM, P = PP, Q = QQ;
	for(int i = M; i; i--){
		beau[1][R[i-1][0]] = beau[0][R[i-1][0]];
		beau[0][R[i-1][0]] = i;
		beau[1][R[i-1][1]] = beau[0][R[i-1][1]];
		beau[0][R[i-1][1]] = i;
	}
	for(int i = 0; i<N; i++){
		if(!beau[0][i]){
			island[i+N] = island[i] = 1;
			continue;
		}
		else if(!beau[1][i]){
			int n = (R[beau[0][i]-1][0] == i ? R[beau[0][i]-1][1] : R[beau[0][i]-1][0]);
			nxt[i+N] = nxt[i] = n + (beau[0][n] == beau[0][i])*N;
		}
		else{
			int n = (R[beau[0][i]-1][0] == i ? R[beau[0][i]-1][1] : R[beau[0][i]-1][0]);
			nxt[i] = n + (beau[0][n] == beau[0][i])*N;
			n = (R[beau[1][i]-1][0] == i ? R[beau[1][i]-1][1] : R[beau[1][i]-1][0]);
			nxt[i+N] = n + (beau[0][n] == beau[1][i])*N;
		}
		graph[nxt[i]].emplace_back(i);
		graph[nxt[i+N]].emplace_back(i+N);		
		//cout << nxt[i] << " " << nxt[i+N] << "\n";
	}
	dfs(P, 1, P);
	dfs(P+N, 2, P+N);
	fill(dist[0], dist[0]+2*N, 6*N);
	fill(dist[1], dist[1]+2*N, 6*N);
	if(c[0].empty()){
		c[0].push_back(P);
	}
	if(c[1].empty()){
		c[1].push_back(P+N);
	}
	bfs(0);
	bfs(1);	
	for(int q = 0; q<Q; q++){
		int k = G[q];
		int ans = 0;
		for(int i =0 ; i<N; i++){
			bool good = 0;
			if((hasP[i]&1) && k >= dist[0][i]){
				if(cyc[0]){
					good = (rem[0][par[0][i]] == (k-dist[0][i])%cyc[0]);
				}
				else{
					good = (dist[0][i] == k);
				}
			}
			if(!good && (hasP[i]&2) && k >= dist[1][i]){
				if(cyc[1]){
					good = (rem[1][par[1][i]] == (k-dist[1][i])%cyc[1]);
				}
				else{
					good = (dist[1][i] == k);
				}
			}
			ans += good;
		}
		answer(ans);
	}
}
/*
int main(){
	int NN, MM, PP, QQ;
	cin >> NN >> MM >> PP;
	int RR[MM][2];
	for(int i = 0; i<MM; i++){
		cin >> RR[i][0] >> RR[i][1];
	}
	cin >> QQ;
	int GG[QQ];
	for(int q = 0; q<QQ; q++){
		cin >> GG[q];
	}
	count_routes(NN, MM, PP, RR, QQ, GG);
}
*/
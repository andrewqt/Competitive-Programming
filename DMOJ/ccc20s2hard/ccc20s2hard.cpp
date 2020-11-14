#include <bits/stdc++.h>

using namespace std;

bool vis[16000005];
int qu[16000005];
int head[16000005];
int nxt[16000005];

bool can_escape(int N, int M, std::vector<std::vector<int>> v){
	vis[1] = 1;
	int l = 1, r = 1;
	qu[1] = 1;
	fill(head+1, head+1+N*M, -1);
	for(int i = 1; i<=N; i++){
		for(int j = 1; j<=M; j++){
			nxt[(i-1)*M+j-1] = head[i*j];
			head[i*j] = (i-1)*M+j-1;
		}
	}
	while(l <= r){
		int n = qu[l++];
		int s = head[n];
		while(s != -1){
			int x = s/M, y = s%M;
			x++, y++;
			if(!vis[v[x][y]]){
				qu[++r] = v[x][y];
				vis[v[x][y]] = 1;
			}
			s = nxt[s];
		}
	}
	return vis[N*M];
}

int main(){
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout << can_escape(3, 4, {{0, 0, 0, 0, 0},
                  {0, 3, 10, 8, 14},
                  {0, 1, 11, 12, 12},
                  {0, 6, 2, 3, 9}});

}
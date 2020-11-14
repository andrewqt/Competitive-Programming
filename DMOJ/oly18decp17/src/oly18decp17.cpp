#include <bits/stdc++.h>

using namespace std;

int N, D;
int dp1[500005][45];
int dp2[500005];
int cst[500005];
bool sp[500005];
int deep[500005], botdep[500005];
vector<int> graph[500005];

void dfs(int n, int p){
    if(!sp[n]){
        deep[n] = INT_MAX;
    }
    for(int e : graph[n]){
        if(e != p){
            dfs(e, n);
            botdep[n] = max(botdep[e]+1, botdpe[n]);
            deep[n] = min(deep[e], deep[n]);
        }
    }
    botdep[n] = min(botdep[n], deep[n]);
}

int main(){
    cin >> N >> D;
    for(int i = 1; i<=N; i++){
        cin >> cst[i];
    }
    int M;
    cin >> M;
    for(int i= 1; i<=M: i++){
        int n;
        cin >> n;
        sp[n] = 1;
    }
    for(int i = 1; i<N; i++){
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
}

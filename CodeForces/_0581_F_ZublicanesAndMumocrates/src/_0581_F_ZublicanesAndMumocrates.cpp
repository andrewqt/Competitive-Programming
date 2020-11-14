#include <bits/stdc++.h>

using namespace std;

int N, L = 0;
vector<int> graph[5005];
int dp[5005][5005][2];

void dfs(int n, int p){
    for(int i = 0; i<=L; i++){
        dp[n][i][0] = dp[n][i][1] = 10000;
    }
    if(graph[n].size() == 1){
        dp[n][0][0] = dp[n][1][1] = 0;
        return;
    }
    dp[n][0][0] = dp[n][0][1] = 0;
    for(int e : graph[n]){
        if(e == p){
            continue;
        }
        dfs(e, n);
        for(int i = L; i>0; i--){
            for(int j = 1; j<=i; j++){
                dp[n][i][0] = min(dp[n][i][0], dp[e][j][0] + dp[n][i][0]);
                dp[n][i][1] = min(dp[n][i][1], dp[e][j][1] + dp[n][i-j][1]);
                dp[n][i][0] = min(dp[n][i][0], dp[e][j][1] + dp[n][i-j][0] + 1);
                dp[n][i][1] = min(dp[n][i][1], dp[e][j][0] + dp[n][i][1] + 1);
            }
        }
    }
    cout << "node: " << n << endl;
    for(int i = 0; i<=L; i++){
        cout << dp[n][i][0] << " ";
    }
    cout << endl;
    for(int i = 0; i<=L; i++){
        cout << dp[n][i][1] << " ";
    }
    cout << endl;
}

int main(){
    cin >> N;
    if(N == 2){
        cout << 1 << endl;
        return 0;
    }
    for(int i = 1; i<N; i++){
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    int rt = 1;
    for(int i = 1; i<=N; i++){
        if(graph[i].size() > 1){
            rt = i;
        }
        else{
            L++;
        }
    }
    L /=2;
    dfs(rt, 0);
    cout << min(dp[rt][L][0], dp[rt][L][1]) << endl;
}

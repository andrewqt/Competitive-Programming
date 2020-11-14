#include <bits/stdc++.h>

using namespace std;

int vis[100005];
long long dp[100005][3];
vector<int> graph[100005];
int cst[100005];
int N;
vector<vector<int>> cmp;
deque<int> dq;
bool done[100005];
int in[100005];

vector<int> bfs(int n){
    dq.push_back(n);
    vector<int> vec;
    vis[n] = 1;
    while(dq.size()){
        n = dq.front();
//        cout << n << endl;
        dq.pop_front();
        vec.push_back(n);
        for(int e : graph[n]){
            if(!vis[e]){
//                cout << n << " " << e << endl;
                vis[e] = 1;
                dq.push_back(e);
            }
        }
    }
    return vec;
}

void dfs(int n){
    bool leaf = 1;
    for(int e : graph[n]){
        if(!vis[e]){
            vis[e] = n;
            dfs(e);
            leaf = 0;
        }
    }
    long long tot = 0;
    dp[n][0] = cst[n];
    for(int e : graph[n]){
        if(vis[e] == n){
            tot += dp[e][1];
            dp[n][0] += dp[e][2];
            dp[n][2] += dp[e][1];
        }
    }
    dp[n][1] = LONG_MAX;
    for(int e : graph[n]){
        if(vis[e] == n){
            dp[n][1] = min(dp[n][1], tot + dp[e][0] - dp[e][1]);
        }
    }
    dp[n][1] = min(dp[n][0], dp[n][1]);
    dp[n][2] = min(dp[n][1], dp[n][2]);
//    cout << n << " " << dp[n][0] << " " << dp[n][1] << " " << dp[n][2] << endl;
}

int main(){
    cin >> N;
    for(int i = 1; i<=N; i++){
        cin >> cst[i];
    }
    for(int i =1; i<=N; i++){
        int n;
        cin >> n;
        graph[i].push_back(n);
        graph[n].push_back(i);
    }
    long long ans = 0;
    for(int i = 1; i<=N; i++){
        if(!vis[i]){
            cmp.push_back(bfs(i));
        }
    }
    fill(vis, vis+1+N, 0);
    for(vector<int> v : cmp){
        long long best = LLONG_MAX;
        for(int i : v){
            //cout << i << endl;
            vis[i] = -1;
            dfs(i);
            best = min(best, dp[i][1]);
            fill(vis, vis+1+N, 0);
            for(int j = 1; j<=N; j++){
                dp[j][0] = dp[j][1] = dp[j][2] = 0;
            }
        }
        ans += best;
    }
    cout << ans << endl;
}

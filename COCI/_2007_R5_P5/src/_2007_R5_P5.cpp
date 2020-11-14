#include <bits/stdc++.h>

using namespace std;

int N, K;
int xc[300005], yc[300005];
pair<pair<int, int>, int> cord[300005];
int amt[300005];
int dp[300005];
int x[100005], y[100005];
int par[300005];

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    for(int i = 1; i<=N; i++){
        cin >> cord[i].first.first >> cord[i].first.second >> amt[i];
        cord[i].second = i;
        xc[i] = cord[i].first.first, yc[i] = cord[i].first.second;
    }
    sort(cord+1, cord+1+N);
    bool done = 0;
    for(int i = 1; i<=N; i++){
        done |= (cord[i].second == 1);
        if(!done){
            continue;
        }
        int n = cord[i].second;
        if(n == 1){
            dp[n] = amt[n];
            x[cord[i].first.first] = n;
            y[cord[i].first.second] = n;
            continue;
        }
        /*
        cout << n << " " << max(dp[x[cord[i].first.first]], dp[y[cord[i].first.second]]) << endl;
        cout << n << " " << amt[n] << endl;
        cout << n << " " << x[cord[i].first.first] << " " << cord[i].first.second << endl;
        */
        if(max(dp[x[cord[i].first.first]], dp[y[cord[i].first.second]]) - K < 0){
            continue;
        }
        dp[n] = max(dp[x[cord[i].first.first]], dp[y[cord[i].first.second]]) - K + amt[n];
        if(dp[n] == dp[x[cord[i].first.first]] - K + amt[n]){
            par[n] = x[cord[i].first.first];
        }
        else{
            par[n] = y[cord[i].first.second];
        }
        if(dp[x[cord[i].first.first]] < dp[n]){
            x[cord[i].first.first] = n;
        }
        if(dp[y[cord[i].first.second]] < dp[n]){
            y[cord[i].first.second] = n;
        }
        if(n == N){
            break;
        }
    }
    int c = N;
    stack<int> stk;
    do{
        stk.push(c);
        c = par[c];
    }
    while(c != 1);
    stk.push(1);
    cout << dp[N] << "\n";
    cout << stk.size() << "\n";
    while(stk.size()){
        int n = stk.top();
        stk.pop();
        cout << xc[n] << " " << yc[n] << "\n";
    }
}

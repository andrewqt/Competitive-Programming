#include <bits/stdc++.h>

using namespace std;

int N, K;
int dp[105][105][10];
char arr[105];

int solve(int l, int r, int k){
    if(l > r){
        return 0;
    }
    if(l == r){
        if(k == K){
            return 1;
        }
        else{
            return N+1;
        }
    }
    if(dp[l][r][k] != -1){
        return dp[l][r][k];
    }
    dp[l][r][k] = N+1;
    if(k == K){
        dp[l][r][k] = min(dp[l][r][k], solve(l+1, r, 1)+1);
    }
    for(int idx = l+1; idx<=r; idx++){
        if(arr[idx] == arr[l]){
            dp[l][r][k] = min(dp[l][r][k], solve(l+1, idx-1, 1)+solve(idx, r, min(K, k+1)));
        }
    }
    return dp[l][r][k];
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    for(int i = 1; i<=N; i++){
        for(int j = 1; j<=N; j++){
            for(int k = 0; k<=K; k++){
                dp[i][j][k] = -1;
            }
        }
    }
    for(int i = 1; i<=N; i++){
        cin >> arr[i];
    }
    int out  = solve(1, N, 1);
    if(out > N){
        out = -1;
    }
    cout << out << endl;
}

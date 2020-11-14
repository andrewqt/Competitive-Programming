#include <bits/stdc++.h>

using namespace std;

long long dp[305][305][16];
int N, M;
long long K;

long long solve(long long n, long long m, int t){
    if(dp[n][m][t] != -1){
        return dp[n][m][t];
    }
    dp[n][m][t] = (n*m-K)*(n*m-K);
    if(((1<<0)&t) || ((1<<2)&t) || ((1<<1)&t && (1<<3)&t)){
        for(int i = 1; i<m; i++){
            dp[n][m][t] = min(dp[n][m][t], solve(n, i, t&(15^8)) + solve(n, m-i, t&(15^2)));
        }
    }
    if(((1<<1)&t) || ((1<<3)&t) || ((1<<0)&t &
                                    & (1<<2)&t)){
        for(int i = 1; i<n; i++){
            dp[n][m][t] = min(dp[n][m][t], solve(i, m, t&(15^1)) + solve(n-i, m, t&(15^4)));
        }
    }
    return dp[n][m][t];
}

int main(){
    cin >> N >> M >> K;
    for(int i = 0; i<=N; i++){
        for(int j = 0; j<=M; j++){
            for(int k = 0; k<16; k++){
                dp[i][j][k] = -1;
            }
        }
    }
    cout << solve(N, M, 15);
}

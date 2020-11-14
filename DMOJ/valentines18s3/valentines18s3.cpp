#include <bits/stdc++.h>

using namespace std;

int dp[103][102][102][102];
int N, K;
int MOD = 1e9+7;

int add(int a, int b){
    return(a+b%MOD)%MOD;
}

int main(){
    cin >> N >> K;
    dp[1][1][1][1] = 1;
    for(int a = 2; a<=N; a++){
        for(int b = 1; b<=a; b++){
            for(int d = 1; d<=a; d++){
                for(int j = 1; j<=d; j++){
                    dp[a][b][1][d] = add(dp[a][b][1][d], dp[a-1][a-1][j][d] - dp[a-1][b-1][j][d] + MOD);
                }
                for(int c = 2; c<=d; c++){
                    dp[a][b][c][d] = add(dp[a][b][c][d], dp[a-1][b-1][c-1][d]);
                }
                dp[a][b][d][d] = add(dp[a][b][d][d], dp[a-1][b-1][d-1][d-1]);
            }
        }
        for(int b = 1; b<=N; b++){
            for(int d = 1; d<=N; d++){
                for(int c = 1; c<=d; c++){
                    dp[a][b][c][d] = add(dp[a][b-1][c][d], dp[a][b][c][d]);
                }
            }
        }
    }
    int ans = 0;
    for(int j = 1; j<=K; j++){
        ans = add(ans, dp[N][N][j][K]);
    }
    cout << ans << endl;
}

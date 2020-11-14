#include <bits/stdc++.h>

using namespace std;

int N, T, L;
int dp[105][505][55];
int amt[105], cst[105];

int main(){
    cin >> N >> L;
    L = min(N-L, L);
    long long S = 0;
    for(int i= 1; i<=N; i++){
        cin >> amt[i];
        T += amt[i];
    }
    for(int i = 1; i<=N; i++){
        cin >> cst[i];
        S += cst[i];
    }
    for(int i = 0; i<=N; i++){
        for(int j = 0; j<=T; j++){
            for(int k = 0; k<=L; k++){
                dp[i][j][k] = INT_MAX>>1;
            }
        }
    }
    dp[0][0][0] = 0;
    for(int i = 1; i<=N; i++){
        for(int j = 0; j<=T; j++){
            for(int k = 0; k<=L; k++){
                dp[i][j][k] = dp[i-1][j][k];
                if(j >= amt[i] && k){
                    dp[i][j][k] = min(dp[i][j][k], dp[i-1][j-amt[i]][k-1] + cst[i]);
                }
            }
        }
    }
    double ans = 1e14;
    for(int k = 1; k<T; k++){
        if(dp[N][k][L] != INT_MAX>>1){
            ans = min(ans, (1.0*S-dp[N][k][L])/(1.0*T-k)/(1.0*k)*(1.0*dp[N][k][L]));
        }
    }
    printf("%.3f", ans);
}

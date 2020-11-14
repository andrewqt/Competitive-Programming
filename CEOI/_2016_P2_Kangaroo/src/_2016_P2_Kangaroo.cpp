#include <bits/stdc++.h>

using namespace std;

int N, S, E;
long long dp[2005][2005];
long long MOD = 1000000007;

long long add(long long a, long long b){
    return (a+b)%MOD;
}

long long sub(long long a, long long b){
    a = add(a, -b);
    if(a < 0){
        a += MOD;
    }
    return a;
}

long long mult(long long a, long long b){
    return a*b%MOD;
}

int main(){
    cin >> N >> S >> E;
    dp[0][0] = 1;
    for(int i = 1; i<=N; i++){
        for(int j = 0; j<=i; j++){
            if(i == S || i == E){
                dp[i][j] = add(dp[i-1][j+1]*(j+1), dp[i-1][j]);
            }
            else{
                if(j){
                    dp[i][j] = dp[i-1][j-1];
                }
                dp[i][j] = add(dp[i-1][j+1]*j*(j+1), dp[i][j]);
                dp[i][j] = add(dp[i-1][j+1]*(j+1)*(i >= S), dp[i][j]);
                dp[i][j] = add(dp[i-1][j+1]*(j+1)*(i >= E), dp[i][j]);
            }
            cout << dp[i][j] << " " << i << " " << j << endl;
        }
    }
    cout << dp[N][0] << endl;
}

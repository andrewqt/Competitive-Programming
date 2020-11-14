#include <bits/stdc++.h>

using namespace std;

long long MOD = 1e9+7;

long long mult(long long a, long long b){
    return a*b%MOD;
}

long long add(long long a, long long b){
    return (a+b)%MOD;
}

int N;
int graph[505][505];
long long dp[505][505];

long long solve(int l, int r){
    cout << " " << l << " " << r << endl;
    if(l == r){
        return 1;
    }
    if(r-l == 1){
        if(graph[l][r]){
            return 1;
        }
        else{
            return 0;
        }
    }
    if(dp[l][r] != -1){
        return dp[l][r];
    }
    dp[l][r] = 0;
    for(int i = l+1; i<=r; i++){
        if(graph[l][i%N]){
            cout << l << " " << r << " " << solve(l, i-1) << " " << solve(i, r) << endl;
            dp[l][r] = add(mult(solve(l, i), solve(i, r)), dp[l][r]);
        }
    }
    cout << l << " " << r << " " << dp[l][r] << endl;
    return dp[l][r];
}

int main(){
    cin >> N;
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            cin >> graph[i][j];
        }
    }
    memset(dp, -1, sizeof(dp));
    cout << solve(0, N) << endl;
}

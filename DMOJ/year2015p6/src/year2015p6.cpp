#include <bits/stdc++.h>

using namespace std;

int N, M;
long long cnt[51][51][32];
long long sum[51][51];
long long dp[51][51][51]; //blocks, rows, filled
long long MOD = 1000000007;

long long add(long long a, long long b){
    return (a+b)%MOD;
}

long long mul(long long a, long long b){
    return (a*b)%MOD;
}

long long power(long long b, long long e){
    if(e){
        long long mid = power(b, e/2);
        mid = mul(mid, mid);
        if(e%2){
            mid = mul(mid, b);
        }
        return mid;
    }
    else{
        return 1;
    }
}

long long combo(long long n, long long r){
    long long ans = 1;
    if(n-r < r){
        r = n-r;
    }
    for(long long i = r+1; i<=n; i++){
        ans = mul(ans, i);
    }
    r = n-r;
    long long bot = 1;
    for(long long i = 1; i<=r; i++){
        bot = mult(bot, i);
    }
    ans = mul(ans, power(bot, MOD-2));
}

int main(){
    cin >> N >> M;
    cnt[0][0][0] = 1;
    for(int i = 1; i<=M; i++){
        for(int j = 1; j<=M; j++){
            for(int k = 1; k<32; k++){
                if(__builtin_popcount(k) <= j){
                    for(int l = 0; l<32; l++){
                        if(!(k&l)){
                            cnt[i][j][k] = add(cnt[i][j][k], cnt[i-1][j-__builtin_popcount(k)][l]);
                        }
                    }
                }
                sum[i][j] = add(cnt[i][j][k], sum[i][j]);
            }
        }
    }
    dp[0][0][0] = 1;
    for(int i = 1; i<=M; i++){
        for(int j =1; j<=M; j++){
            for(int k = 1; k<=M; k++){
                for(int l = 1; l<=j; l++){
                    for(int m = 1; m<=k; m++){
                        dp[i][j][k] = sum(dp[i][j][k], mult(dp[i-1][j-l][k-m], sum[l][m]));
                    }
                }
            }
        }
    }

}

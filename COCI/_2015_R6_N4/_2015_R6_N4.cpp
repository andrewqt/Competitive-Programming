#include <bits/stdc++.h>

using namespace std;

int N;
int dp[2][1<<20];
int MOD = 1000000000;

int main(){
    cin >> N;
    int cnt = 0;
    dp[0][0] = 1;
    for(int i = 1; i<=N; i++){
        for(int j = i+1; j<=N; j++){
            if(__gcd(i, j) == 1){
                cout << i << " " << j << endl;
                cnt ^= 1;
                int msk = ((1<<(i-1))-1)^((1<<(j-1))-1);
                for(int m = 0; m<1<<20; m++){
                    dp[cnt][m] = dp[cnt^1][m];
                }
                for(int m = 0; m<1<<20; m++){
                    dp[cnt][m|msk] += dp[cnt^1][m];
                    if(dp[cnt][m|msk] > MOD){
                        dp[cnt][m|msk] -= MOD;
                    }
                }
            }
        }
    }
    cout << dp[cnt][((1<<(N-1))-1)] << endl;
}

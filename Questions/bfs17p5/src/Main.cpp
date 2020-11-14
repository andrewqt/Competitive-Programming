#include <bits/stdc++.h>

using namespace std;

long long dp[1000005], cache[1<<7][1<<7];
long long MOD = 1000000007;
int N, K;
int mask[1000005];

long long add(long a, long b){
    return (a+b)%MOD;
}

int main(){
    scanf("%d", &N);
    scanf("%d", &K);
    for(int i = 1; i<=K; i++){
        int n;
        scanf("%d", &n);
        while(n--){
            int crnt;
            scanf("%d", &crnt);
            mask[crnt] |= (1<<(i-1));
        }
    }
    dp[1] = 1;
    if(true){
        int m = mask[1];
        int lo = mask[1]%(1<<7), hi = mask[1]/(1<<7);
        for(int j = 0; j<(1<<7); j++){
            if((j&(lo)) == 0){
                cache[j][hi] = add(cache[j][hi], 1);
            }
        }
    }
    for(int i = 2; i<=N; i++){
        int m = mask[i];
        int lo = mask[i]%(1<<7), hi = mask[i]/(1<<7);
        for(int j = 0; j<(1<<7); j++){
            if((j&(hi)) == 0){
                dp[i] = add(dp[i], cache[lo][j]);
            }
        }
        for(int j = 0; j<(1<<7); j++){
            if((j&(lo)) == 0){
                cache[j][hi] = add(cache[j][hi], dp[i]);
            }
        }
    }
    printf("%lld\n", dp[N]);
}

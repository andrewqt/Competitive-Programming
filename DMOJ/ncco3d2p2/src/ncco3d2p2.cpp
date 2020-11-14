#include <bits/stdc++.h>

using namespace std;

int dp[1005][305];
pair<int, int> arr[305];

int main(){
    int N, K;
    cin >> K >> N;
    for(int i = 1; i<=N; i++){
        cin >> arr[i].first >> arr[i].second;
    }
    for(int i= 1; i<=1000; i++){
        for(int j = 1; j<=300; j++){
            dp[i][j] = K+1;
        }
    }
    arr[N+1].second = arr[N+1].first = 1001;
    dp[1][0] = 0;
    for(int i = 1; i<=1000; i++){
        for(int j = 0; j<=N; j++){
            if(dp[i][j] == K+1){
                continue;
            }
            if(j == N){
                cout << i+1 << endl;
                return 0;
            }
            int sumpre = dp[i][j], sumsuf = 0;
            for(int k = j; k<=N; k++){
                if(sumpre > K || sumsuf > K){
                    break;
                }
                dp[i+1][k] = min(sumsuf, dp[i+1][k]);
                sumpre += arr[k+1].first;
                sumsuf += arr[k+1].second;
            }
        }
    }
}

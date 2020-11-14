#include <bits/stdc++.h>

using namespace std;

int N, K;
bool dp[501];
int arr[501];

int main(){
    cin >> N >> K;
    dp[0] = 1;
    for(int i = 1; i<=N; i++){
        int n;
        cin >> n;
        for(int j = K; j>=n; j--){
            dp[j] |= dp[j-n];
        }
    }
    int cnt = 0;
    for(int i = 0; i<=K; i++){
        if(dp[i]){
            cnt++;
        }
    }
    cout << cnt << endl;
    for(int i = 0; i<=K; i++){
        if(dp[i]){
            cout << i << " ";
        }
    }
}

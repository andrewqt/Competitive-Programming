#include <bits/stdc++.h>

using namespace std;

int N, Q;
int arr[2000005];
int dp[2000005];

int main(){
    cin >> N >> Q;
    for(int i = 1; i<=N; i++){
        cin >> arr[i];
        arr[i+N] = arr[i];
    }
    while(Q--){
        long long K;
        cin >> K;
        long long tot = 0;
        int ans = INT_MAX;
        for(int l= 1, r = 1; r<=2*N; r++){
            tot += arr[r];
            while(tot > K){
                tot -= arr[l++];
            }
            dp[r] = dp[l-1] + 1;
            if(r > N){
                ans = min(dp[r]-dp[r-N], ans);
            }
        }
        for(int i = 1; i<=2*N; i++){
            cout << dp[i] << " ";
        }
        cout << endl;
        cout << ans << endl;
    }
}

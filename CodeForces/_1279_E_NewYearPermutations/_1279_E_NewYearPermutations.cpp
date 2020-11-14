#include <bits/stdc++.h>

using namespace std;

int T;
long long dp[55];
int ans[55];
long long fact[55];

int main(){
    cout.tie(0);
    cin >> T;
    dp[0] = 1;
    for(int i = 1; i<=51; i++){
        for(int j = 1; j<=i; j++){
            dp[i] += dp[i-j];
        }
    }
    while(T--){
        int N;
        long long K;
        cin >> N >> K;
        if(dp[N] < K){
            cout << -1 << "\n";
            continue;
        }
        int crnt = 0, idx = 1;
        while(idx <= N){
            //cout << K << endl;
            for(int i = 1; i<=N; i++){
                if(dp[N-idx-i+1] >= K){
                    int l = i + idx - 1;
                    ans[idx] = l--;
                    int r = idx + i - 1;
                    while(r > idx){
                        ans[r--] = l--;
                    }
                    idx += i;
                    break;
                }
                else{
                    K -= dp[N-idx-i+1];
                }
            }
        }
        for(int i = 1; i<=N; i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
}

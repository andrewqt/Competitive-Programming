#include <bits/stdc++.h>

using namespace std;

int N;
int dp[60][300000];

int main(){
    freopen("262144.in", "r", stdin);
    freopen("262144.out", "w", stdout);
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    int ans = 0;
    for(int i= 1; i<=N; i++){
        int n;
        cin >> n;
        ans = max(ans, n);
        dp[n][i] = i;
        for(int j = n+1; 1; j++){
            dp[j][i] = dp[j-1][dp[j-1][i]-1];
            if(!dp[j][i]){
                break;
            }
            ans = max(ans, j);
        }
    }
    cout << ans << endl;
}

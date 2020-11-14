#include <bits/stdc++.h>

using namespace std;

int N;
int dp[1<<20];
string s;

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for(int i = 1; i<=N; i++){
        cin >> s;
        int m = 0;
        for(char c : s){
            m ^= (1<<(c-'a'));
        }
        dp[m]++;
    }
    for(int k = 19; k>=0; k--){
        for(int m = (1<<20)-1; m>=0; m--){
            if(m&(1<<k));
            else{
                dp[m] += dp[m^(1<<k)];
            }
        }
    }
    int ans = 21;
    for(int m = 0; m<1<<20; m++){
        if(dp[m] == 1){
            ans = min(ans, __builtin_popcount(m));
        }
    }
    if(ans == 21){
        ans = -1;
    }
    cout << ans << endl;
}

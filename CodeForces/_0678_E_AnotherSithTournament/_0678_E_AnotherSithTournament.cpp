#include <bits/stdc++.h>

using namespace std;

int N;
double arr[18][18];
double dp[1<<18][18];

int main(){
    cin >> N;
    cout.precision(11);
    for(int i = 0; i<N; i++){
        for(int j =0; j<N; j++){
            cin >> arr[i][j];
        }
    }
    dp[1][0]= 1;
    for(int m = 1; m<(1<<N); m++){
        for(int i = 0; i<N; i++){
            for(int j = 0; j<N; j++){
                if(i != j && ((1<<i)&m) && ((1<<j)&m)){
                    dp[m][i] = max(dp[m][i], (dp[m^(1<<j)][i] + dp[m^(1<<j)][j])*arr[i][j]);
                }
            }
            cout << dp[m][i] << " " << m << " " << i << endl;
        }
    }
    double ans = 0;
    for(int i = 0; i<N; i++){
        ans = max(ans, dp[(1<<N)-1][i]);
    }
    cout << ans << endl;
}

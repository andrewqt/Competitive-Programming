#include <bits/stdc++.h>

using namespace std;

int N;
int lftcst[1005], rhtcst[1005];
long long dp[1005][20005], maxi[1005][20005];

int main(){
    cin >> N;
    cin >> lftcst[1];
    for(int i = 1; i<N; i++){
        cin >> rhtcst[i] >> lftcst[i+1];
    }
    for(int i = 0; i<lftcst[1]; i++){
        maxi[1][i] = dp[1][i] = i;
    }
    for(int i = lftcst[1]; i<=20000; i++){
        dp[1][i] = INT_MIN;
        maxi[1][i] = lftcst[1]-1;
    }
    for(int i = 2; i<=N; i++){
        for(int j = 0; j<=20000; j++){
            maxi[i][j] = maxi[i][j-1];
            if(j < lftcst[i]){
                dp[i][j] = max(maxi[i-1][rhtcst[i-1]-1] + j, dp[i-1][j+rhtcst[i-1]]);
            }
            else if(j >= rhtcst[i-1]+lftcst[i]){
                dp[i][j] = dp[i-1][j];
            }
            else{
                dp[i][j] = dp[i-1][j-lftcst[i]] + lftcst[i];
            }
            maxi[i][j] = max(maxi[i][j], dp[i][j]);
        }
    }
    cout << maxi[N][20000] << endl;
}

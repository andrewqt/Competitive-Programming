#include <bits/stdc++.h>

using namespace std;

unsigned short dp[55][1005][1005];
unsigned short opt[55][1005][1005];
unsigned short pre[55][1005];
int N, M;
string s;

//difference between actual array elements and positions

int main(){
    cin >> N >> M;
    getline(cin, s);
    for(int i = 1; i<=N; i++){
        getline(cin, s);
        for(int j = M; j>=1; j--){
            pre[M-j+1][i] = s[j-1]-'0' + pre[M-j+1][i-1];
        }
    }
    for(short n = 1; n<=M; n++){
        for(int l = 0; l<=N; l++){
            opt[n][l][l] = l;
        }
        for(short s = 1; s<=N; s++){
            for(short l = 0; l+s<=N; l++){
                short r = l + s;
                int lb = opt[n][l][r-1], ub = opt[n][l+1][r];
//                cout << lb << " " << ub << " " << l << " " << r << endl;
                dp[n][l][r] = 60000;
                for(short k = lb; k<=ub; k++){
                    if(dp[n][l][r] > (r - k - (pre[n][r] - pre[n][k]) + pre[n][k] - pre[n][l] +
                                      dp[n-1][l][k] + dp[n-1][k][r])){
                        dp[n][l][r] = (r - k - (pre[n][r] - pre[n][k]) + pre[n][k] - pre[n][l] +
                                      dp[n-1][l][k] + dp[n-1][k][r]);
                        opt[n][l][r] = k;
                    }
                }
//                cout << l << " " << r << " " << dp[n][l][r] << endl;
            }
        }
    }
    /*
    for(int i = 1; i<=M; i++){
        for(int l = 1; l<=N; l++){
            for(int r = l; r<=N; r++){
                cout << dp[i][l][r] << " ";
            }
            cout << endl;
        }
    }
    */
    cout << dp[M][0][N] << endl;
}

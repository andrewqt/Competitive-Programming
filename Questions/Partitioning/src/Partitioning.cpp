#include <bits/stdc++.h>

using namespace std;

int N, K;
long long arr[20005];
bool dp[1<<11][20005];
long long val[12];
int ptr[12];

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> K;
    assert(N <= 10000 && K <= N && K <= 4);
    for(int i = 1; i<=N; i++){
        cin >> arr[i];
        assert(arr[i] <= 1000000000);
        arr[i] += arr[i-1];
    }
    for(int k = 0; k<K; k++){
        cin >> val[k];
        assert(val[k] <= 100000000000000);
    }
    dp[0][0] = 1;
    for(int i = 1; i<=N; i++){
        for(int k = 0; k<K; k++){
            while(ptr[k] < i && arr[i] - arr[ptr[k]+1] >= val[k]){
                ptr[k]++;
            }
        }
        for(int m = 0; m<1<<K; m++){
            if(dp[m][i-1]){
                dp[m][i] = 1;
            }
            else{
                for(int k = 0; k<K; k++){
                    if(((1<<k)&m) && ptr[k] != i && arr[i]-arr[ptr[k]] >= val[k]){
                        dp[m][i] |= dp[m^(1<<k)][ptr[k]];
                    }
                }
            }
        }
    }
    if(dp[(1<<K)-1][N]){
        cout << "YES" << endl;
    }
    else{
        cout << "NO" << endl;
    }
}

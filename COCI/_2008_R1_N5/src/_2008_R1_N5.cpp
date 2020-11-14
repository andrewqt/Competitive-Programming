#include <bits/stdc++.h>

using namespace std;

struct qu{
    short r, c;
    int v;
    bool operator < (qu q) const{
        return v < q.v;
    }
};

int N, sR, sC;
qu arr[2500005];
short bigr[1505][5], bigc[1505][5];
int dp[1505][1505];

int main(){
    cin >> N >> sR >> sC;
    for(int i = 1; i<=N; i++){
        for(int j = 1; j<=N; j++){
            int v;
            cin >> v;
            arr[(i-1)*N+j-1] = {i, j, v};
        }
    }
    int ans = 1;
    sort(arr, arr+N*N);
    for(int i = 1; i<=N; i++){
        bigr[i][3] = bigc[i][3] = 1504;
    }
    for(int i = 0; i<N*N; i++){
//        cout << arr[i].v << endl;
        int idx = i;
        while(idx < N*N && arr[idx].v == arr[i].v){
//            cout << arr[idx].r << " " << arr[idx].c << endl;
            for(int j = 0; j<4; j++){
                if(abs((arr[idx].c - bigr[arr[idx].r-1][j])) > 1){
                    dp[arr[idx].r][arr[idx].c] = max(dp[arr[idx].r][arr[idx].c],
                                                     dp[arr[idx].r-1][bigr[arr[idx].r-1][j]]);
                    break;
                }
            }
            for(int j = 0; j<4; j++){
                if(abs((arr[idx].c - bigr[arr[idx].r+1][j])) > 1){
                    dp[arr[idx].r][arr[idx].c] = max(dp[arr[idx].r][arr[idx].c],
                                                     dp[arr[idx].r+1][bigr[arr[idx].r+1][j]]);
                    break;
                }
            }
            for(int j = 0; j<4; j++){
                if(abs((arr[idx].r - bigc[arr[idx].c+1][j])) > 1){
                    dp[arr[idx].r][arr[idx].c] = max(dp[arr[idx].r][arr[idx].c],
                                                     dp[bigc[arr[idx].c+1][j]][arr[idx].c+1]);
                    break;
                }
            }
            for(int j = 0; j<4; j++){
                if(abs((arr[idx].r - bigc[arr[idx].c-1][j])) > 1){
                    dp[arr[idx].r][arr[idx].c] = max(dp[arr[idx].r][arr[idx].c],
                                                     dp[bigc[arr[idx].c-1][j]][arr[idx].c-1]);
                    break;
                }
            }
//            cout << "val: " << dp[arr[idx].r][arr[idx].c] << endl;
            idx++;
        }
        for(int tidx = i; tidx<idx; tidx++){
            if(arr[tidx].r == sR && arr[tidx].c == sC){
                dp[sR][sC] = 1;
                bigr[sR][0] = sC;
                bigc[sC][0] = sR;
                continue;
            }
            if(dp[arr[tidx].r][arr[tidx].c]){
                dp[arr[tidx].r][arr[tidx].c]++;
                for(int j = 3; j>=0; j--){
                    if(dp[arr[tidx].r][arr[tidx].c] < dp[arr[tidx].r][bigr[arr[tidx].r][j]]){
                        bigr[arr[tidx].r][j+1] = arr[tidx].c;
                        break;
                    }
                    else if(!j){
                        bigr[arr[tidx].r][j] = arr[tidx].c;
                    }
                    else{
                        bigr[arr[tidx].r][j] = bigr[arr[tidx].r][j-1];
                    }
                }
                for(int j = 3; j>=0; j--){
                    if(dp[arr[tidx].r][arr[tidx].c] < dp[bigc[arr[tidx].c][j]][arr[tidx].c]){
                        bigc[arr[tidx].c][j+1] = arr[tidx].r;
                        break;
                    }
                    else if(!j){
                        bigc[arr[tidx].c][j] = arr[tidx].r;
                    }
                    else{
                        bigc[arr[tidx].c][j] = bigc[arr[tidx].c][j-1];
                    }
                }
                ans = max(dp[arr[tidx].r][arr[tidx].c], ans);
            }
        }
        i = idx-1;
    }
    cout << ans << endl;
}

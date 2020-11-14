#include <bits/stdc++.h>

using namespace std;

struct trio{
    short x, y, z;
    bool operator < (trio t) const{
        return abs(x) + abs(y) + abs(z) > abs(t.x) + abs(t.y) + abs(t.z);
    }
};

int N, K;
long long dp[205][205][205];
int x[5005], y[5005], z[5005], t[5005];
long long MOD = 1e9+7;
int offset = 101;
vector<trio> v;

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> K;
    for(int i = 1; i<=N; i++){
        cin >> x[i] >> y[i] >> z[i] >> t[i];
    }
    for(int i = -100; i<=100; i++){
        for(int j = -100; j<=100; j++){
            for(int k = -100; k<=100; k++){
                v.push_back({i, j, k});
            }
        }
    }
    sort(v.begin(), v.end());
    long long ans = 1;
    for(int k = 1; k<=K; k++){
        for(int i = 0; i<205; i++){
            for(int j = 0; j<205; j++){
                for(int k = 0; k<205; k++){
                    dp[i][j][k] = 0;
                }
            }
        }
        for(int i = 1; i<=N; i++){
            if(t[i] == k){
                dp[x[i]+101][y[i]+101][z[i]+101] = 1;
            }
            else{
                dp[x[i]+101][y[i]+101][z[i]+101] = -1;
            }
        }
        for(auto p : v){
            if(dp[p.x+101][p.y+101][p.z+101] != -1){
                int xc = p.x+101, yc = p.y+101, zc = p.z+101;
                for(int d = -1; d<=1; d+=2){
                    if(abs(p.x+d) > abs(p.x)){
                        dp[xc][yc][zc] += max(0LL, dp[xc+d][yc][zc]);
                    }
                    if(abs(p.y+d) > abs(p.y)){
                        dp[xc][yc][zc] += max(0LL, dp[xc][yc+d][zc]);
                    }
                    if(abs(p.z+d) > abs(p.z)){
                        dp[xc][yc][zc] += max(0LL, dp[xc][yc][zc+d]);
                    }
                }
                //cout << dp[xc][yc][zc] << " " << xc << " " << yc << " " << zc << " " << k << endl;
                dp[xc][yc][zc] %= MOD;
            }
        }
        ans *= dp[101][101][101];
        ans %= MOD;
    }
    cout << ans << endl;
}

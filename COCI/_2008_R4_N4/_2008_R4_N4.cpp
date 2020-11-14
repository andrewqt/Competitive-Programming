#include <bits/stdc++.h>

using namespace std;

int N;
string s;
int mp[512][512];
int pre[512][512];
map<long long, int> dp[3];
map<long long, int> dp1, dp2;

long long cmp(int lx, int rx, int ly, int ry){
    return 1LL*lx*1000000000L+1LL*rx*1000000L+1LL*ly*1000L+1LL*ry;
}

//typ = 0 continue, typ = 1 all 1s, typ = 2 all 0s

void rec(int lx, int rx, int ly, int ry, int typ){
    if(rx-lx == 1 && ry-ly == 1){
        dp[typ][cmp(lx, rx, ly, ry)] = 0;
        return;
    }
    if(typ == 1){
        dp[typ][cmp(lx, rx, ly, ry)] = (rx-lx)*(ry-ly) -
        (pre[rx][ry] - pre[rx][ly] - pre[lx][ry] + pre[lx][ly]);
        return;
    }
    if(typ == 2){
        dp[typ][cmp(lx, rx, ly, ry)] =
        (pre[rx][ry] - pre[rx][ly] - pre[lx][ry] + pre[lx][ly]);
        return;
    }
    int midx = (lx+rx)/2, midy = (ly+ry)/2;
    for(int i = 0; i<3; i++){
        rec(lx, midx, ly, midy, i);
        rec(lx, midx, midy, ry, i);
        rec(midx, rx, ly, midy, i);
        rec(midx, rx, midy, ry, i);
    }
    vector<int> p = {0, 0, 1, 2};
    int ans = INT_MAX;
    do{
        int sum = dp[p[0]][cmp(lx, midx, ly, midy)]
                  + dp[p[1]][cmp(lx, midx, midy, ry)]
                  + dp[p[2]][cmp(midx, rx, ly, midy)]
                  + dp[p[3]][cmp(midx, rx, midy, ry)];
        if(ans > sum){
            ans = sum;
            for(int i =0; i<4; i++){
                for(int j =i+1; j<4; j++){
                    if(!p[i] && !p[j]){
                        dp1[cmp(lx, rx, ly, ry)] = i;
                        dp2[cmp(lx, rx, ly, ry)] = j;
                    }
                }
            }
        }
    }
    while(next_permutation(p.begin(), p.end()));
    dp[typ][cmp(lx, rx, ly, ry)] = ans;
}

int main(){
    cin >> N;
    for(int i = 0; i<N; i++){
        cin >> s;
        for(int j = 0; j<N; j++){
            mp[i][j] = s[j]-'0';
            pre[i][j] = mp[i][j] + pre[i][j-1] + pre[i-1][j] - pre[i-1][j-1];
        }
    }
    rec(0, N, 0, N, 0);

}

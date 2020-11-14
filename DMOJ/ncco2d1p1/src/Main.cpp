#include <bits/stdc++.h>

using namespace std;

int N, T;
long long dp[305][305][2];
vector <int> al;

long long solve(int l, int r, int s, int sz){
    if(r-l >= sz){
        return 0;
    }
    if(dp[l][r][s] != LONG_MAX){
        return dp[l][r][s];
    }
    int pos = s ? al[l] : al[r];
    if(l > 0){
        dp[l][r][s] = min(dp[l][r][s], solve(l - 1, r, 1, sz) + (sz-(r-l))*(pos-al[l-1]));
    }
    if(r < N) {
        dp[l][r][s] = min(dp[l][r][s], solve(l, r + 1, 0, sz) + (sz-(r-l))*(al[r+1] - pos));
    }
    return dp[l][r][s];
}

int main(){
    scanf("%d %d", &N, &T);
    for(int i = 1; i<=N; i++){
        int n;
        scanf("%d", &n);
        al.push_back(n);
    }
    al.push_back(0);
    sort(al.begin(), al.end());
    int org = find(al.begin(), al.end(), 0) - al.begin();
    long long best = 0;
    for(int i = 0; i<=N; i++){
        for(int j =0; j<=N; j++){
            for(int k = 0; k<=N; k++){
                dp[j][k][0] = dp[j][k][1] = LONG_MAX;
            }
        }
        best = max(best, i*T - solve(org, org, 0, i));
    }
    cout << best << endl;
}

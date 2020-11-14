#include <bits/stdc++.h>

using namespace std;

vector<int> graph[200000];
bool sp[200000];
int N;
long long dp[2][200000];
const long long MOD = 1000000007;

long long mult(long long a, long long b){
    return (a%MOD*b%MOD)%MOD;
}

long long add(long long a, long long b){
    return (a%MOD+b%MOD)%MOD;
}

void dfs(int n, int p){
    if(sp[n]){
        dp[1][n]++;
        for(auto e : graph[n]){
            if(e != p){
                dfs(e, n);
                dp[1][n] = mult(dp[1][n], add(dp[0][e], dp[1][e]));
            }
        }
    }
    else{
        dp[0][n]++;
        for(auto e : graph[n]){
            if(e != p){
                dfs(e, n);
                dp[1][n] = add(dp[1][n], add(mult(dp[1][e], dp[0][n]), dp[0][e]));
                dp[0][n] = mult(dp[0][n], add(dp[0][e], dp[1][e]));
            }
        }
    }
    cout << n << " " << dp[0][n] << " " << dp[1][n] << endl;
}

int main(){
    scanf("%d", &N);
    for(int i =2; i<=N; i++){
        int n;
        scanf("%d", &n);
        n++;
        graph[i].push_back(n);
        graph[n].push_back(i);
    }
    for(int i = 1; i<=N; i++){
        int n;
        scanf("%d", &n);
        sp[i] = n;
    }
    dfs(1,0 );
    cout << dp[1][1] << endl;
}

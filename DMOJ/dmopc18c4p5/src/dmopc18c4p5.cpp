#include <bits/stdc++.h>

using namespace std;

int N, K;
bool special[300000];
vector<pair<int, pair<bool, long long>>> graph[300000];
long long ans = 0;
long long longestpath1[300000];
long long longestpath2[300000];
long long bestpath[300000];
long long extra[300000];
int par[300000];

void solve(int n){
    for(auto e : graph[n]){
        int cld = e.first;
        if(cld != par[n]){
            par[cld] = n;
            solve(cld);
            longestpath2[n] += (longestpath2[cld]+e.second.second*2)*e.second.first;
        }
    }
    ans = max(ans, longestpath2[n]);
    bestpath[n] = longestpath2[n];
    for(auto e : graph[n]){
        int cld = e.first;
        long long curpath = 0;
        if(par[n] != cld){
            if(e.second.first){
                curpath = bestpath[cld] - longestpath2[cld] - extra[cld];
            }
            else{
                curpath = bestpath[cld] + e.second.second;
            }
        }
        ans = max(bestpath[n]+curpath, ans);
        if(e.second.first){
            if(curpath + longestpath2[n] > bestpath[n]){
                extra[n] = extra[cld] + e.second.second;
            }
            bestpath[n] = max(bestpath[n], curpath + longestpath2[n]);
        }
        else{
            if(curpath + longestpath2[n] > bestpath[n]){
                extra[n] = extra[cld] + e.second.second;
            }
            bestpath[n] = max(bestpath[n], curpath + longestpath2[n]);
        }
    }
    cout << n << " " << bestpath[n] << " " << longestpath2[n] << endl;
}

int main(){
    scanf("%d %d", &N, &K);
    fill(special+1, special+N+1, 0);
    for(int i =1; i<=K; i++){
        int n;
        scanf("%d", &n);
        special[n] = 1;
    }
    for(int i = 1; i<N; i++){
        int a, b;
        long long v;
        scanf("%d %d %lld", &a, &b, &v);
        graph[a].push_back({b, {special[i], v}});
        graph[b].push_back({a, {special[i], v}});
    }
    solve(1);
    printf("%lld\n", ans);
}

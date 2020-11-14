#include <bits/stdc++.h>

using namespace std;

int N;
long long ans = 0;
int nxt[1000005];
long long val[1000005];
bool istree[1000005];
vector<int> graph[1000005];
long long sdp[1000005][2], tdp[1000005][2];
bool done[1000005];

long long nmax(long long a, long long b){
    return a > b ? a : b;
}


void dfs(int n){
    done[n] = 1;
    tdp[n][1] = val[n];
    for(int e : graph[n]){
        if(istree[e]){
            continue;
        }
        dfs(e);
        tdp[n][0] += nmax(tdp[e][0], tdp[e][1]);
        tdp[n][1] += tdp[e][0];
    }
}

void solve(int n){
    while(!done[n]){
        done[n] = 1;
        n = nxt[n];
    }
    while(!istree[n]){
        istree[n] = 1;
        n = nxt[n];
    }
    while(!tdp[n][1]){
        dfs(n);
        n = nxt[n];
    }
    int s = n;
    sdp[n][1] = LLONG_MIN/10;
    sdp[n][0] = tdp[n][0];
    n = nxt[n];
    int p = s;
    while(n != s){
        sdp[n][0] = nmax(sdp[p][0], sdp[p][1]) + tdp[n][0];
        sdp[n][1] = sdp[p][0] + tdp[n][1];
        p = n;
        n = nxt[n];
    }
    long long opt = nmax(sdp[p][0], sdp[p][1]);
    sdp[n][1] = tdp[n][1];
    sdp[n][0] = LLONG_MIN/10;
    n = nxt[n];
    p = s;
    while(n != s){
        sdp[n][0] = nmax(sdp[p][0], sdp[p][1]) + tdp[n][0];
        sdp[n][1] = sdp[p][0] + tdp[n][1];
        p = n;
        n = nxt[n];
    }
    ans += nmax(opt, sdp[p][0]);
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for(int i =1 ; i<=N; i++){
        cin >> val[i] >> nxt[i];
        graph[nxt[i]].push_back(i);
    }
    for(int n = 1; n<=N; n++){
        if(!done[n]){
            solve(n);
        }
    }
    cout << ans << "\n";
}

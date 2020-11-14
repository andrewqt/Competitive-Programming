#include <bits/stdc++.h>

using namespace std;

vector<int> graph[100005];
int N, K;
int a[100005], b[100005], t[100005];
int up[100005], down[100005], par[100005][20], dep[100005];

long long power(int b, int e){
    if(e == 0){
        return 1;
    }
    long long res = power(b, e/2);
    res = (res*res)%1000000007;
    if(e%2 == 1){
        res = (res*b)%1000000007;
    }
    return res;
}

void dfs1(int n){
    for(auto e : graph[n]){
        if(e != par[n][0]){
            dep[e] = dep[n] + 1;
            par[e][0] = n;
            dfs1(e);
        }
    }
}

void dfs2(int n){
    for(auto e : graph[n]){
        if(e != par[n][0]){
            dfs2(e);
            up[n] += up[e];
            down[n] += down[e];
        }
    }
}

int lca(int a, int b){
    if(dep[a] < dep[b]){
        swap(a, b);
    }
    for(int i = 19; i>=0; i--){
        if(dep[a] - (1<<i) >= dep[b]){
            a = par[a][i];
        }
    }
    if(a == b){
        return a;
    }
    for(int i = 19; i>=0; i--){
        if(par[a][i] != par[b][i]){
            a = par[a][i];
            b = par[b][i];
        }
    }
    return par[a][0];
}

int main(){
    scanf("%d", &N);
    for(int i = 1; i<N; i++){
        scanf("%d %d %d", &a[i], &b[i], &t[i]);
        graph[a[i]].push_back(b[i]);
        graph[b[i]].push_back(a[i]);
    }
    dep[1] = 1;
    dfs1(1);
    for(int i = 1; i<20; i++){
        for(int j = 1; j<=N; j++){
            par[j][i] = par[par[j][i-1]][i-1];
        }
    }
    scanf("%d", &K);
    int x = 1;
    while(K--){
        int y;
        scanf("%d", &y);
        int z = lca(x, y);
        up[x]++;
        up[z]--;
        down[y]++;
        down[z]--;
        x = y;
    }
    dfs2(1);
    long long tot = 0;
    for(int i =1; i<N; i++){
        if(t[i]){
            if(dep[a[i]] < dep[b[i]]){
                tot = (tot + power(2, up[b[i]])-1)%1000000007;
            }
            else{
                tot = (tot + power(2, down[a[i]])-1)%1000000007;
            }
        }
    }
    cout << tot << endl;
}

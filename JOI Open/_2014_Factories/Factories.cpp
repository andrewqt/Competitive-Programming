#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> graph[500005];
deque<int> ll;
long long cdist[500005][21], dist[500005], SET = LLONG_MAX/2;
int par[500005], sz[500005], lvl[500005], cpar[500005][21], hvy[500005];
bool vis[500005];

void dfs1(int n){
    sz[n] = 1;
    for(auto e : graph[n]){
        if(e.first != par[n] && !vis[e.first]){
            int edge = e.first;
            hvy[edge] = 0;
            par[edge] = n;
            dfs1(edge);
            sz[n] += sz[edge];
            hvy[n] = sz[edge] > sz[hvy[n]] ? edge : hvy[n];
        }
    }
}

void dfs2(int n, int l){
    ll.push_back(n);
    while(!ll.empty()){
        n = ll.front();
        ll.pop_front();
        for(auto e : graph[n]){
            if(e.first != par[n] && !vis[e.first]){
                int edge = e.first;
                cdist[edge][l] = cdist[n][l] + e.second;
                par[edge] = n;
                cpar[edge][l] = cpar[n][l];
                ll.push_back(edge);
            }
        }
    }
}

int getcent(int n){
    hvy[n] = 0;
    dfs1(n);
    int siz = sz[n];
    while(sz[hvy[n]]*2 >= siz){
        n = hvy[n];
    }
    return n;
}

void solve(int n, int l){
    n = getcent(n);
    vis[n] = 1;
    par[n] = 0;
    cpar[n][l] = n;
    dfs2(n, l);
    for(auto e : graph[n]){
        if(!vis[e.first]){
            lvl[e.first] = lvl[n] + 1;
            solve(e.first, l+1);
        }
    }
}

void Init(int N, int A[], int B[], int D[]){
    for(int i = 0; i<N-1; i++){
        A[i]++;
        B[i]++;
        graph[A[i]].push_back({B[i], D[i]});
        graph[B[i]].push_back({A[i], D[i]});
    }
    fill(dist, dist+N+1, SET);
    solve(1, 0);
}

long long Query(int M, int Y[], int N, int X[]){
    long long ans = SET;
    for(int i = 0; i<N; i++){
        int n = ++X[i];
        for(int j = 0; cpar[n][j]; j++){
            dist[cpar[n][j]] = min(dist[cpar[n][j]], cdist[n][j]);
        }
    }
    for(int i = 0; i<M; i++){
        int n = ++Y[i];
        for(int j = 0; cpar[n][j]; j++){
            ans = min(dist[cpar[n][j]] + cdist[n][j], ans);
        }
    }
    for(int i = 0; i<N; i++){
        int n = X[i];
        for(int j = 0; cpar[n][j]; j++){
            dist[cpar[n][j]] = SET;
        }
    }
    return ans;
}

int main(){
    int N, Q;
    assert(scanf("%i %i", &N, &Q) == 2);
    int *A = (int*)malloc(sizeof(int) * (N - 1));
    int *B = (int*)malloc(sizeof(int) * (N - 1));
    int *D = (int*)malloc(sizeof(int) * (N - 1));
    for(int a = 0; a < N - 1; a++){
        assert(scanf("%i %i %i", A + a, B + a, D + a) == 3);
    }
    Init(N, A, B, D);
    for(int a = 0; a < Q; a++){
        int S, T;
        assert(scanf("%i %i", &S, &T) == 2);
        int *X = (int*)malloc(sizeof(int) * S);
        int *Y = (int*)malloc(sizeof(int) * T);
        for(int b = 0; b < S; b++){
            assert(scanf("%i", X + b) == 1);
        }
        for(int b = 0; b < T; b++){
            assert(scanf("%i", Y + b) == 1);
        }
        printf("%i\n", Query(S, X, T, Y));
        free(X);
        free(Y);
    }
    free(A);
    free(B);
    free(D);
}

#include "dreaming.h"
#include <bits/stdc++.h>

using namespace std;

int N, M, L;
vector<pair<int, int>> graph[100005];
long long dist[2][100005];
bool vis[100005];

long long dfs(int n, int t, int p){
    int ret = n;
    vis[n] = 1;
    for(auto e : graph[n]){
        if(e.first != p){
            dist[t][e.first] = dist[t][n] + e.second;
            int k = dfs(e.first, t, n);
            if(dist[t][k] > dist[t][ret]){
                ret = k;
            }
        }
    }
    return ret;
}

long long solve(int n, int p){
    long long ret = max(dist[0][n], dist[1][n]);
    for(auto e : graph[n]){
        if(e.first != p){
            long long k = solve(e.first, n);
            ret = min(k, ret);
        }
    }
    return ret;
}

int travelTime(int n, int m, int l, int A[], int B[], int T[]){
    N = n, M = m, L = l;
    for(int i = 0; i<M;i ++){
        A[i]++, B[i]++;
        graph[A[i]].push_back({B[i], T[i]});
        graph[B[i]].push_back({A[i], T[i]});
    }
    vector<long long> v;
    long long ans = 0;
    for(int i = 1; i<=N; i++){
        if(!vis[i]){
            int n = dfs(i, 0, 0);
            dist[0][n] = 0;
            n = dfs(n, 0, 0);
            ans = max(ans, dist[0][n]);
            dfs(n, 1, 0);
            long long r = solve(n, 0);
            //cout << "d: " << i << " " << r << "\n";
            v.push_back(r);
        }
    }
    //cout << ans << "\n";
    sort(v.begin(), v.end(), greater<long long>());
    if(v.size() >= 2){
        //cout << v[0] << " " << v[1] << " " << l << "\n";
        ans = max(ans, v[0] + v[1] + l);
    }
    //cout << ans << "\n";
    if(v.size() >= 3){
        ans = max(ans, v[1] + v[2] + 2*l);
    }
    return ans;
}

int sampleA[8] = {0, 8, 2, 5, 5, 1, 1, 10};
int sampleB[8] = {8, 2, 7, 11, 1, 3, 9, 6};
int sampleT[8] = {4, 2, 4, 3, 7, 1, 5, 3};

/*
int main(){
    cout<< travelTime(12, 8, 2, sampleA, sampleB, sampleT) << "\n";
}
*/

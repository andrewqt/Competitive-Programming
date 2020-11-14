#include <bits/stdc++.h>

using namespace std;

int N, S, M;
int arr[2005];
vector<int> v;
vector<int> pos[2005];
int dp[2005], par[2005];
bool vis[2005];

int solve(int p, int lvl){
    int ret = INT_MAX;
    int n = pos[lvl].size();
    for(int i = 0; i<n; i++){

    }
}

int main(){
    cin >> N >> S;
    S--;
    for(int i = 0; i<N; i++){
        cin >> arr[i];
        v.push_back(arr[i]);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    M = v.size();
    for(int i= 0; i < N; i++){
        pos[v.lower_bound(v.begin(), v.end(), arr[i]) - v.begin()].push_back(i);
    }
    for(int i = 0; i < M; i++){
        sort(pos[i].begin(), pos[i].end());
    }
    for(int p : pos[0]){
        par[p] = S;
        vis[p] = 1;
        if(p < S){
            dp[i] = min(S - p, p - S + N);
        }
        else{
            dp[i] = min(p - S, S + N - p);
        }
    }
    for(int lvl = 0; lvl < M-1; lvl++){
        for(int p : pos[lvl]){
            dp[p] = INT_MAX;
            for(int q : pos[lvl]){

            }
        }
    }
}

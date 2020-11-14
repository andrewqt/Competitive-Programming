#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> graph[200005];
int sz[200005], par[200005], dist[200005], cnt[200005], ll[200005];
bool vis[200005];
map<int, int> mapf;

int dfs(int n){
    sz[n] = 1;
    for(auto e : graph[n]) {
        if(e.first != par[n] && !vis[e.first]){
            par[e.first] = n;
            dfs(e.first);
            sz[n] += sz[e.first];
        }
    }
//    cout << " " << n << "  " << sz[n] << endl;
}

int getcent(int n){
    dfs(n);
    int totsize = sz[n];
    while(true){
        int hvy = 200001;
        for(auto e : graph[n]){
            if(e.first != par[n] && !vis[e.first]){
                hvy = sz[hvy] < sz[e.first] ? e.first : hvy;
            }
        }
//        cout << sz[hvy] << "  " << n << endl;
        if(2*sz[hvy] >= totsize){
            n = hvy;
        }
        else{
            break;
        }
    }
    return n;
}

int solve(int n, int K){
    n = getcent(n);
//    cout << " " << n << endl;
    vis[n] = 1;
    mapf.clear();
    mapf[0] = 0;
    int minval = 1000000000;
    for(auto edge : graph[n]){
        if(!vis[edge.first] && edge.second <= K){
            dist[edge.first] = edge.second;
            cnt[edge.first] = 1;
            int l = 1, r = 1;
            stack<int> stk;
            ll[1] = edge.first;
            par[edge.first] = n;
            while(l <= r){
                int crnt = ll[l++];
//                cout << crnt << " " << dist[crnt] << endl;
                stk.push(crnt);
                for(auto e : graph[crnt]){
                    if(e.first != par[crnt] && !vis[e.first] && dist[crnt] + e.second <= K){
                        par[e.first] = crnt;
                        dist[e.first] = dist[crnt] + e.second;
                        cnt[e.first] = cnt[crnt] + 1;
                        ll[++r] = e.first;
                    }
                }
 //               cout << crnt << " " << K-dist[crnt] << " " << mapf.count(K-dist[crnt])
//                << "  " << cnt[crnt] << endl;
                if(mapf.count(K-dist[crnt])){
                    minval = min(mapf[K-dist[crnt]] + cnt[crnt], minval);
                }
 //               cout << minval << endl;
            }
            while(!stk.empty()){
                int crnt = stk.top();
                stk.pop();
                if(mapf[dist[crnt]] == 0){
                    mapf[dist[crnt]] = cnt[crnt];
                }
                mapf[dist[crnt]] = min(mapf[dist[crnt]], cnt[crnt]);
            }
        }
    }
    for(auto e : graph[n]){
        if(!vis[e.first]){
            minval = min(solve(e.first, K), minval);
        }
    }
//    cout << "  " << n << "  " << minval << endl;
    return minval;
}

int best_path(int N, int K, int H[][2], int L[]){
    for(int i =0; i<N-1; i++){
        int a = H[i][0], b = H[i][1];
        graph[a].push_back({b, L[i]});
        graph[b].push_back({a, L[i]});
    }
    fill(par, par+N+1, -1);
    int ans = solve(1, K);
    return ans == 1000000000 ? -1 : ans;
}

int main(){
    int H[10][2];
    H[0][0] = 0;
    H[0][1] = 1;
    H[1][0] = 0;
    H[1][1] = 2;
    H[2][0] = 2;
    H[2][1] = 3;
    H[3][0] = 3;
    H[3][1] = 4;
    H[4][0] = 4;
    H[4][1] = 5;
    H[5][0] = 0;
    H[5][1] = 6;
    H[6][0] = 6;
    H[6][1] = 7;
    H[7][0] = 6;
    H[7][1] = 8;
    H[8][0] = 8;
    H[8][1] = 9;
    H[9][0] = 8;
    H[9][1] = 10;
    int L[] = {3,4,5,4,6,3,2,5,6,7};
    cout << best_path(11, 12, H, L);
}

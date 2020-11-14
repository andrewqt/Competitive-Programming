#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> graph[100005];
pair<pair<int, int>, int> edge[100005];
bool vis[100005];
int dep[100005];
int c[40];
vector<int> v;
vector<int> ans[40];

void dfs(int n, int p){
    vis[n] = 1;
    for(auto e : graph[n]){
        int k = edge[e].first.first;
        if(k == n){
            k = edge[e].first.second;
        }
        if(!vis[k]){
            dep[k] = dep[n] ^ edge[e].second;
            dfs(k, n);
        }
        else if(p != k){
            v.push_back(e);
        }
    }
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> M;
    for(int i = 1; i<=M; i++){
        cin >> edge[i].first.first >> edge[i].first.second >> edge[i].second;
        graph[edge[i].first.first].push_back(i);
        graph[edge[i].first.second].push_back(i);
    }
    dfs(1, 0);
    int out = 0;
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    for(int e : v){
        int k = dep[edge[e].first.first]^dep[edge[e].first.second]^edge[e].second;
        for(int b = 29; b>=0; b--){
            if((k>>b)&1){
                if(c[b] == 0){
                    c[b] = k;
                    out++;
                }
                k ^= c[b];
                ans[b].push_back(e);
            }
        }
    }
    cout << out << "\n";
    for(int b = 29; b>=0; b--){
        if(c[b]){
            cout << c[b] << " ";
            cout << ans[b].size() << " ";
            for(int e : ans[b]){
                cout << e << " ";
            }
            cout << "\n";
        }
    }
}

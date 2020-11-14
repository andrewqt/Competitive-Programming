#include <bits/stdc++.h>

using namespace std;

int N, M, D;
map<int, long long> mp[100005];
vector<int> graph[100005];
pair<int, int> item[100005];

void dfs(int n){
    mp[n][0] = 0;
    if(item[n].second){
        mp[n][item[n].first] = item[n].second;
    }
    for(int e : graph[n]){
        dfs(e);
        vector<pair<int, long long>> vec;
        if(mp[e].size() > mp[n].size()){
            swap(mp[e], mp[n]);
        }
        for(auto p : mp[e]){
            long long v = (*(--mp[n].upper_bound(p.first))).second;
            v += p.second;
            vec.push_back({p.first, v});
        }
        for(auto p : vec){
            mp[n][p.first] = p.second;
            while(mp[n].upper_bound(p.first) != mp[n].end()){
                if((*mp[n].upper_bound(p.first)).second <= p.second){
                    mp[n].erase(mp[n].upper_bound(p.first));
                }
                else{
                    break;
                }
            }
        }
    }
    cout << "Node: " << n << endl;
    for(auto p : mp[n]){
        cout << p.first << " " << p.second << endl;
    }
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> D;
    for(int i = 2; i<=N; i++){
        int p;
        cin >> p;
        graph[p].push_back(i);
    }
    for(int i = 1; i<=M; i++){
        int n, d, w;
        cin >> n >> d >> w;
        item[n] = {d, w};
    }
    dfs(1);
    cout << (*(--mp[1].end())).second << endl;
}

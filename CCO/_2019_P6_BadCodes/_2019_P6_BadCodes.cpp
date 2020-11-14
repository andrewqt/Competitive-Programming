#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<pair<pair<int, int>, int>> graph[55][55];
int dist[55][55];
string arr[55];
priority_queue
<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for(int i = 0; i<=N; i++){
        if(i){
            cin >> arr[i];
        }
        for(int j = 0; j<=M; j++){
            dist[i][j] = INT_MAX;
        }
    }
    for(int i = 1; i<=N; i++){
        for(int j = 0; j<arr[i].size(); j++){
            for(int k = 1; k<=N; k++){
                if(!j && i == k){
                    continue;
                }
                int szi = arr[i].size(), szk = arr[k].size();
                int cnt = min(szi-j, szk);
                bool b = 1;
                for(int l = 0; l<cnt; l++){
                    if(arr[i][j+l] != arr[k][l]){
                        b = 0;
                        break;
                    }
                }
                if(!b){
                    continue;
                }
                if(cnt == (szi-j) && cnt == szk){
                    graph[i][j].push_back({{0, 0}, cnt});
                }
                else if(cnt == szk){
                    graph[i][j].push_back({{i, j+cnt}, cnt});
                }
                else{
                    graph[i][j].push_back({{k, cnt}, cnt});
                }
            }
        }
    }
    for(int i = 1; i<=N; i++){
        dist[i][0] = 0;
        pq.push({0, {i, 0}});
    }
    while(pq.size()){
        auto p = pq.top();
        pq.pop();
        if(p.first != dist[p.second.first][p.second.second]){
            continue;
        }
        int a = p.second.first, b = p.second.second;
        for(auto e : graph[a][b]){
            if(dist[e.first.first][e.first.second] > dist[a][b] + e.second){
                dist[e.first.first][e.first.second] = dist[a][b] + e.second;
                pq.push({dist[e.first.first][e.first.second], {e.first.first, e.first.second}});
            }
        }
    }
    if(dist[0][0] == INT_MAX){
        dist[0][0] = -1;
    }
    cout << dist[0][0] << endl;
}

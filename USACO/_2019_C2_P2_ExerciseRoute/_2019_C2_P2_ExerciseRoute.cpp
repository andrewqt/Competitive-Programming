#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> graph[200005];
pair<int, int> ed[200005];



int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for(int i= 1; i<N; i++){
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    M -= N-1;
    for(int i = 1; i<=M; i++){
        cin >> ed[i].first >> ed[i].second;
    }

}

#include <bits/stdc++.h>

using namespace std;

int N, M;
set<int> graph[100005];

int main(){
    cin >> N >> M;
    for(int i = 1; i<=M; i++){
        int a, b;
        cin >> a >> b;
        graph[a].insert(b);
    }
    long long ans = 0;
    for(int i = 1; i<=N; i++){
        if(graph[i].size()){
            int f = *graph[i].begin();
            ans += (graph[i].size());
            graph[i].erase(f);
            if(graph[f].size() < graph[i].size()){
                swap(graph[f], graph[i]);
            }
            for(int n : graph[i]){
                graph[f].insert(n);
            }
        }
    }
    cout << ans << endl;
}

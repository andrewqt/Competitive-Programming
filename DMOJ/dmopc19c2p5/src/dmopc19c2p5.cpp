#include <bits/stdc++.h>

using namespace std;

int N;
int val[300005];
vector<int> graph[300005];

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for(int i = 1; i<=N; i++){
        cin >> val[i];
    }
    for(int i = 1; i<N; i++){
        int a, b;
        cin>> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

}

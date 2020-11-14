#include <bits/stdc++.h>

using namespace std;

int N, M, Q;
vector<int> graph[100005];
vector<int> val[100005];

int main(){
    scanf("%d %d %d", &N, &M, &Q);
    for(int i = 1; i<N; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for(int i = 1; i<=M; i++){
        int c;
        scanf("%d", &c);
        val[c].push_back(i);
    }

}

#include <bits/stdc++.h>

using namespace std;

int N, Q;
int pre[1000005];
vector<int> graph[1000005];

void dfs(int n, int p){
    for(int e : graph[n]){
        if(e != p){
            pre[e] = min(pre[n], e);
            dfs(e, n);
        }
    }
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> Q;
    for(int i = 1; i<N; i++){
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    Q--;
    int c, rt, lst = 0;
    cin >> c >> rt;
    rt = rt%N+1;
    int tot = rt;
    pre[rt] = rt;
    dfs(rt, 0);
    while(Q--){
        int n;
        cin >> c >> n;
        n = (lst+n)%N+1;
        if(c == 1){
            tot = min(tot, pre[n]);
        }
        else{
            cout << (lst = min(pre[n], tot)) << "\n";
        }
    }
}

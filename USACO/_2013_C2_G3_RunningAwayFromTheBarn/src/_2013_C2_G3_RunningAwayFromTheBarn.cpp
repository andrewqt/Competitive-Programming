#include <bits/stdc++.h>

using namespace std;

int N;
long long L;
vector<pair<int, long long>> graph[200005];
long long dep[200005];
int ans[200005];

priority_queue<long long> dfs(int n){
    priority_queue<long long> ret;
    ret.push(dep[n]);
    for(auto e : graph[n]){
        dep[e.first] = dep[n] + e.second;
        auto p = dfs(e.first);
        if(p.size() > ret.size()){
            swap(p, ret);
        }
        while(p.size()){
            ret.push(p.top());
            p.pop();
        }
    }
    while(ret.size() && ret.top() > dep[n] + L){
        ret.pop();
    }
    ans[n] = ret.size();
    return ret;
}

int main(){
    freopen("runaway.in", "r", stdin);
    freopen("runaway.out", "w", stdout);
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> L;
    for(int i = 2; i<=N; i++){
        int p;
        long long l;
        cin >> p >> l;
        graph[p].push_back({i, l});
    }
    dfs(1);
    for(int i = 1; i<=N; i++){
        cout << ans[i] << "\n";
    }
}

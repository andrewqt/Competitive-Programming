#include <bits/stdc++.h>

using namespace std;

int N, M;
int ans[50005];
pair<int, int> edge[50005];
vector<int> graph[50005];
pair<int, pair<int, int>> upd[50005];
int par[50005];
int dep[50005];
int dsu[50005];

int getrt(int n){
    return dsu[n] = (dsu[n] == n ? n : getrt(dsu[n]));
}

int getnxtedge(int e, int n){
    if(edge[e].first == n){
        return edge[e].second;
    }
    else{
        return edge[e].first;
    }
}

void dfs(int n){
    for(int e : graph[n]){
        if(e != par[n]){
            int k = getnxtedge(e, n);
            par[k] = e;
            dep[k] = dep[n] + 1;
            dfs(k);
        }
    }
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	if(fopen("disrupt.in", "r")){
		freopen("disrupt.in", "r", stdin);
		freopen("disrupt.out", "w", stdout);
	}
    cin >> N >> M;
    for(int i = 1; i<N; i++){
        ans[i] = -1;
        cin >> edge[i].first >> edge[i].second;
        graph[edge[i].first].push_back(i);
        graph[edge[i].second].push_back(i);
        dsu[i] = i;
    }
    dsu[N] = N;
    dep[1] = 1;
    dfs(1);
    for(int i = 1; i<=M; i++){
        cin >> upd[i].second.first >> upd[i].second.second >> upd[i].first;
    }
    sort(upd+1, upd+1+M);
    for(int m = 1;m <=M; m++){
        int a = getrt(upd[m].second.first), b = getrt(upd[m].second.second), w = upd[m].first;
        while(a != b){
            if(dep[a] < dep[b]){
                swap(a, b);
            }
            int k = getnxtedge(par[a], a);
            ans[par[a]] = w;
            dsu[a] = dsu[getrt(k)];
            a = getrt(a);
        }
    }
    for(int i = 1; i<N; i++){
        cout << ans[i] << "\n";
    }
}

#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> graph[100005], rgraph[100005], cgraph[100005];
vector<vector<int>> cmp;
int dfn[100005], low[100005], t = 0, cnt = 0;
int typ[100005], sz[100005], dgr[100005];
bool instk[100005];
stack<int> stk;
int dp1[100005], dp2[100005];

void dfs1(int n){
    dfn[n] = low[n] = ++t;
    stk.push(n);
    instk[n] = 1;
    for(int e : graph[n]){
        if(!dfn[e]){
            dfs1(e);
            low[n] = min(low[n], low[e]);
        }
        else if(instk[e]){
            low[n] = min(low[n], dfn[e]);
        }
    }
    if(low[n] == dfn[n]){
        int c;
        ++cnt;
        vector<int> v;
        do{
            c = stk.top();
            stk.pop();
            v.push_back(c);
            instk[c] = 0;
            typ[c] = cnt;
            sz[cnt]++;
        }
        while(c != n);
        cmp.push_back(v);
    }
}

vector<int> toposort(){
    queue<int> qu;
    for(int n = 1; n<=N; n++){
        dgr[n] = rgraph[n].size();
        if(rgraph[n].size() == 0){
            qu.push(n);
        }
    }
    vector<int> ret;
    while(qu.size()){
        int n = qu.front();
        qu.pop();
        ret.push_back(n);
        for(int e : cgraph[n]){
            dgr[e]--;
            if(!dgr[e]){
                qu.push(e);
            }
        }
    }
    return ret;
}

int main(){
    freopen("grass.in", "r", stdin);
    freopen("grass.out", "w", stdout);
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for(int i= 1; i<=M; i++){
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
    }
    for(int n = 1; n<=N; n++){
        if(!dfn[n]){
            dfs1(n);
        }
    }
    for(int n= 1; n<=N; n++){
        for(int e : graph[n]){
            if(typ[e] != typ[n]){
                rgraph[typ[e]].push_back(typ[n]);
                cgraph[typ[n]].push_back(typ[e]);
            }
        }
    }
    N = cnt;
    for(int n = 1; n<=N; n++){
        sort(rgraph[n].begin(), rgraph[n].end());
        rgraph[n].erase(unique(rgraph[n].begin(), rgraph[n].end()), rgraph[n].end());
        sort(cgraph[n].begin(), cgraph[n].end());
        cgraph[n].erase(unique(cgraph[n].begin(), cgraph[n].end()), cgraph[n].end());
    }
    vector<int> srt = toposort();
    for(int n : srt){
        if(!dp1[n] && n != typ[1]){
            continue;
        }
        dp1[n] += sz[n];
        for(int e : cgraph[n]){
            dp1[e] = max(dp1[e], dp1[n]);
        }
    }
    reverse(srt.begin(), srt.end());
    int ans = dp1[typ[1]];
    for(int n : srt){
        if(!dp2[n] && n != typ[1]){
            continue;
        }
        dp2[n] += sz[n];
        for(int e : rgraph[n]){
            dp2[e] = max(dp2[e], dp2[n]);
        }
    }
    reverse(srt.begin(), srt.end());
    for(int n : srt){
        if(dp1[n]){
            for(int e : rgraph[n]){
                if(dp2[e]){
                    ans = max(ans, dp1[n] + dp2[e] - sz[typ[1]]);
                }
            }
        }
    }
    cout << ans << endl;
}

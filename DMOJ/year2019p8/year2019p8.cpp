#include <bits/stdc++.h>

using namespace std;

struct Node{
    int l, r;
};

int N, M;
int leaf[400005];
Node seg[400005];
vector<int> graph[400005], cgraph[400005], rgraph[400005];
int low[400005], typ[400005], val[400005], dp[400005], dgr[400005], t = 0, cnt = 0;
stack<int> stk;
deque<int> dq;

void build(int l, int r, int idx){
    seg[idx].l = l, seg[idx].r = r;
    if(l == r){
        leaf[l] = idx;
        return;
    }
    int mid = l+r>>1;
    build(l, mid, 2*idx);
    build(mid+1, r, 2*idx+1);
    graph[2*idx].push_back(idx);
    graph[2*idx+1].push_back(idx);
}

void upd(int l, int r, int v, int idx){
    if(seg[idx].l == l && seg[idx].r == r){
        graph[idx].push_back(v);
        return;
    }
    int mid = seg[idx].l + seg[idx].r >> 1;
    if(r <= mid){
        upd(l, r, v, 2*idx);
    }
    else if(l > mid){
        upd(l, r, v, 2*idx+1);
    }
    else{
        upd(l, mid, v, 2*idx);
        upd(mid+1, r, v, 2*idx+1);
    }
}

void dfs(int n){
    bool isrt = 1;
    low[n] = ++t;
    stk.push(n);
    for(int e : graph[n]){
        if(!low[e]){
            dfs(e);
        }
        if(low[n] > low[e]){
            low[n] = low[e];
            isrt = 0;
        }
    }
    if(isrt){
        cnt++;
        while(true){
            int k = stk.top();
            stk.pop();
            typ[k] = cnt;
            if(seg[k].l == seg[k].r){
                val[cnt]++;
            }
            low[k] = INT_MAX;
            if(k == n){
                break;
            }
        }
    }
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    build(1, N, 1);
    while(M--){
        int v, a, b;
        cin >> v >> a >> b;
        v = leaf[v];
        upd(a, b, v, 1);
    }
    N *= 4;
    dfs(leaf[1]);
    for(int i = 1; i<=N; i++){
        for(int e : graph[i]){
            if(typ[e] && typ[i]){
                if(typ[e] != typ[i]){
                    cgraph[typ[i]].push_back(typ[e]);
                    rgraph[typ[e]].push_back(typ[i]);
                    dgr[typ[i]]++;
                }
            }
        }
    }
    N = cnt;
    for(int i = 1; i<=N; i++){
        if(!dgr[i]){
            dq.push_back(i);
        }
    }
    while(dq.size()){
        int n = dq.front();
        dq.pop_front();
        for(int e : cgraph[n]){
            dp[n] = max(dp[e], dp[n]);
        }
        dp[n] += val[n];
        for(int e : rgraph[n]){
            dgr[e]--;
            if(!dgr[e]){
                dq.push_back(e);
            }
        }
    }
    cout << dp[typ[leaf[1]]] << endl;
}

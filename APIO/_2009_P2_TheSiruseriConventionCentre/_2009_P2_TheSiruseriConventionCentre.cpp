#include <bits/stdc++.h>

using namespace std;

int N;
int par[200005][20], mini[200005][20];
int dep[200005];
int pre[400005];
priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>,
 greater<pair<pair<int, int>, int>>> pq;
vector<int> cmp;

// x < y ?
bool chk(int x, int y){
    if(dep[x] != dep[y]){
        return dep[x] > dep[y];
    }
    int minx = x, miny = y;
    for(int d = 19; d>=0; d--){
        if(par[x][d] != par[y][d]){
            minx = min(minx, mini[x][d]);
            miny = min(miny, mini[y][d]);
            x = par[x][d];
            y = par[y][d];
        }
    }
    return minx < miny;
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N;
    for(int i = 1; i<=N; i++){
        pair<int, int> p;
        cin >> p.second >> p.first;
        pq.push({p, i});
        cmp.push_back(p.first);
        cmp.push_back(p.second);
    }
    cmp.push_back(0);
    sort(cmp.begin(), cmp.end());
    cmp.erase(unique(cmp.begin(), cmp.end()), cmp.end());
    int M = cmp.size();
    for(int i = 1; i<M; i++){
        pre[i] = pre[i-1];
        while(pq.size() && pq.top().first.first == cmp[i]){
            int l = pq.top().first.second, r = pq.top().first.first, idx = pq.top().second;
            l = lower_bound(cmp.begin(), cmp.end(), l) - cmp.begin();
            r = lower_bound(cmp.begin(), cmp.end(), r) - cmp.begin();
            pq.pop();
            par[idx][0] = pre[l-1];
            mini[idx][0] = idx;
            dep[idx] = dep[pre[l-1]] + 1;
            for(int d = 1; d<20; d++){
                par[idx][d] = par[par[idx][d-1]][d-1];
                mini[idx][d] = min(mini[idx][d-1], mini[par[idx][d-1]][d-1]);
            }
            if(chk(idx, pre[i])){
                pre[i] = idx;
            }
        }
    }
    cout << dep[pre[M-1]] << "\n";
    int crnt = pre[M-1];
    vector<int> ans;
    while(crnt){
        ans.push_back(crnt);
        crnt = par[crnt][0];
    }
    sort(ans.begin(), ans.end());
    for(int n : ans){
        cout << n << " ";
    }
    cout << "\n";
}

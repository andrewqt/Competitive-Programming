#include <bits/stdc++.h>

using namespace std;

int N, Q;
int K = 0, M = 0;
int arr[200005];
unordered_map<pair<int, int>, int> mp;
int l[500005], r[500005], x[500005], y[500005];
int le[1000005], re[1000005], xe[1000005], ye[1000005];
int par[1000005], sz[1000005];
vector<int> pos[200005];

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N;
    for(int i = 1; i<=N; i++){
        cin >> arr[i];
        pos[i].push_back(0);
    }
    cin >> Q;
    for(int q = 1; q<=Q; q++){
        cin>> l[q] >> r[q] >> x[q] >> y[q];
        mp[{x[q], q}] = ++K, mp[{y[q], q}] = ++K;
        pos[x[q]].push_back(q), pos[y[q]].push_back(q);
    }
    for(int i = 1; i<=N; i++){
        mp[{i, 0}] = ++K, mp[{i, Q+1}] = ++K;
        pos[i].push_back(Q+1);
    }
    for(int i = 1; i<=Q; i++){
        int q = ++M;
        le[q] = l[i], re[q] = r[i], xe[q] = mp[{x[i], i}], ye[q] = mp[{y[i], i}];
        q = ++M;
        le[q] = 0, re[q] =

    }
}

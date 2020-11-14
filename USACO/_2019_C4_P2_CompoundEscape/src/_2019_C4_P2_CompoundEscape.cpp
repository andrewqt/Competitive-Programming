#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> v;
stack<int> stk;
vector<int> t;
vector<int> pos;
int tot = 0;
vector<pair<int, int>> hgraph[200], vgraph[200];
int N, K, M;
int par[6];
int clr[6];
int lst[6];
long long dp[200][60005];
long long cnt[200][60005];

int getrt(int n){
    return par[n] = (par[n] == n ? n : getrt(par[n]));
}

void rec(int n){
    if(n == 0){
        v.push_back(t);
        int add = 1;
        int mx = *max_element(t.begin(), t.end());
        for(int i = 6; i>=mx; i--){
            add *= i;
        }
        for(int i = 1; i<=6-mx; i++){
            add /= i;
        }
        tot += add;
        return;
    }
    int nxt = (t.empty() ? 1 : *max_element(t.begin(), t.end()) + 1);
    vector<int> k;
    for(int x = 1; x<nxt; x++){
        if(find(pos.begin(), pos.end(), x) != pos.end()){
            while(pos.size() && pos.back() != x){
                k.push_back(pos.back());
                pos.pop_back();
            }
            t.push_back(x);
            rec(n-1);
            t.pop_back();
            while(k.size()){
                pos.push_back(k.back());
                k.pop_back();
            }
        }
    }
    pos.push_back(nxt);
    t.push_back(nxt);
    rec(n-1);
    t.pop_back();
    pos.pop_back();
}

int getnxt(){
    vector<int> ret;
    int cnt = 0;
    for(int b = 0; b<K; b++){
        if(par[b] == b){
            clr[b] = ++cnt;
        }
        ret.emplace_back(clr[getrt(b)]);
    }
    return lower_bound(v.begin(), v.end(), ret) - v.begin();
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    if(fopen("escape.in", "r")){
        freopen("escape.in", "r", stdin);
        freopen("escape.out", "w", stdout);
    }
    cin >> N >> K;
    rec(K);
    M = v.size();
    sort(v.begin(), v.end());
    for(int m = 0; m<M; m++){
        for(int k = 0; k<(1<<(K-1)); k++){
            for(int b = 0; b<K; b++){
                lst[b] = -1;
                par[b] = b;
            }
            for(int b = 0; b<K; b++){
                if(lst[v[m][b]] == -1){
                    lst[v[m][b]] = b;
                }
                par[b] = lst[v[m][b]];
            }
            for(int b = 0; b<K-1; b++){
                if((k>>b)&1){
                    par[b+1] = getrt(b);
                }
            }
            auto l = getnxt();
            vgraph[m].push_back({k, l});
        }
    }
    for(int m = 0; m<M; m++){
        for(int k = 0; k<1<<K; k++){
            for(int b = 0; b<K; b++){
                lst[b] = -1;
                par[b] = b;
            }
            for(int b = 0; b<K; b++){
                if((1<<b)&k){
                    if(lst[v[m][b]] == -1){
                        lst[v[m][b]] = b;
                    }
                    par[b] = lst[v[m][b]];
                }
            }
            int l = getnxt();
            hgraph[m].push_back({k, l});
        }
    }
    for(int m = 0; m<M; m++){
        for(int i = 0; i<2*N; i++){
            dp[m][i] = LLONG_MAX/2;
        }
    }
    dp[m][]
}

#include <bits/stdc++.h>

using namespace std;

struct edge{
    int u, v, w, id;
    bool operator < (edge e) const{
        return w > e.w;
    }
};

int N, M, Q, B = 1000;
edge srt[100005], arr[100005];
int ans[100005];
int par[50005], sz[50005];
int lst[100005];
vector<pair<pair<int, int>, int>> upd, qu;
bool cupd[100005];
int stk[100005], stkidx = 0;

int getrt(int n, bool cmp){
    if(cmp){
        return par[n] = (par[n] == n ? n : getrt(par[n], 1));
    }
    while(n != par[n]){
        n = par[n];
    }
    return n;
}

void unite(int x, int y, bool b){
    if(sz[x] < sz[y]){
        swap(x, y);
    }
    sz[x] += sz[y];
    par[y] = x;
    if(b){
        stk[++stkidx] = y;
    }
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> M;
    for(int i = 1; i<=M; i++){
        cin >> arr[i].u >> arr[i].v >> arr[i].w;
        arr[i].id = i;
    }
    cin >> Q;
    for(int q = 1; q<=Q; q++){
        int c, x, y;
        cin >> c >> x >> y;
        if(c == 1){
            upd.push_back({{y, x}, q});
            cupd[x] = 1;
        }
        else{
            qu.push_back({{y, x}, q});
        }
        if(q%B == 0 || q == Q){
            for(int m = 1; m<=M; m++){
                srt[m] = arr[m];
            }
            for(int n = 1; n<=N; n++){
                par[n] = n;
                sz[n] = 1;
            }
            sort(qu.begin(), qu.end(), greater<pair<pair<int, int>, int>>());
            sort(srt+1, srt+1+M);
            int idx = 0;
            for(auto k : qu){
                int wt = k.first.first, n = k.first.second, t = k.second;
                while(idx < M && srt[idx+1].w >= wt){
                    ++idx;
                    if(cupd[srt[idx].id]){
                        continue;
                    }
                    int x = getrt(srt[idx].u, 1), y = getrt(srt[idx].v, 1);
                    if(x != y){
                        unite(x, y, 0);
                    }
                }
                for(auto u : upd){
                    if(u.second < t){
                        lst[u.first.second] = u.second;
                    }
                    else{
                        break;
                    }
                }
                for(auto u : upd){
                    if(lst[u.first.second] == u.second && u.first.first >= wt){
                        int ed = u.first.second;
                        int x = getrt(arr[ed].u, 0), y = getrt(arr[ed].v, 0);
                        if(x != y){
                            unite(x, y, 1);
                        }
                        lst[u.first.second] = -1;
                    }
                    else if(!lst[u.first.second] && arr[u.first.second].w >= wt){
                        int ed = u.first.second;
                        int x = getrt(arr[ed].u, 0), y = getrt(arr[ed].v, 0);
                        if(x != y){
                            unite(x, y, 1);
                        }
                        lst[u.first.second] = -1;
                    }
                }
                ans[t] = sz[getrt(n, 0)];
                while(stkidx){
                    int p = stk[stkidx--];
                    int rt = getrt(p, 0);
                    sz[rt] -= sz[p];
                    par[p] = p;
                }
                for(auto u : upd){
                    lst[u.first.second] = 0;
                }
            }
            for(auto e : upd){
                arr[e.first.second].w = e.first.first;
                cupd[e.first.second] = 0;
            }
            qu.clear();
            upd.clear();
        }
    }
    for(int q = 1; q<=Q; q++){
        if(ans[q]){
            cout << ans[q] << "\n";
        }
    }
}

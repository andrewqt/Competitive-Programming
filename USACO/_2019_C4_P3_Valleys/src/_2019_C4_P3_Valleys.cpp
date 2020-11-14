#include <bits/stdc++.h>

using namespace std;

int N;
pair<int, int> par[755][755];
int arr[755][755];
int sz[755][755], edg[755][755], sqr[755][755];
bool on[755][755];
vector<pair<int, int>> v[1000005];

pair<int, int> getrt(int i, int j){
    return par[i][j] = ((par[i][j] == make_pair(i, j)) ? make_pair(i, j) :
                        getrt(par[i][j].first, par[i][j].second));
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    if(fopen("valleys.in", "r")){
        freopen("valleys.in", "r", stdin);
        freopen("valleys.out", "w", stdout);
    }
    cin >> N;
    for(int i = 0; i<=N+1; i++){
        par[0][i] = {0, i};
        par[i][0] = {i, 0};
        par[N+1][i] = {N+1, i};
        par[i][N+1] = {i, N+1};
    }
    for(int i = 1; i<=N; i++){
        for(int j = 1; j<=N; j++){
            cin >> arr[i][j];
            v[arr[i][j]].push_back({i, j});
            sz[i][j] = 1;
            par[i][j] = {i, j};
        }
    }
    long long ans = 0;
    for(int w = 1; w<=1000000; w++){
        for(auto n : v[w]){
            int x = n.first, y = n.second;
            on[x][y] = 1;
            for(int i = -1; i<=1; i++){
                for(int j = -1; j<=1; j++){
                    if(((!i && j) || (i && !j)) && on[x+i][y+j]){
                        auto rt1 = getrt(x+i, y+j), rt2 = getrt(x, y);
                        edg[rt2.first][rt2.second]++;
                        if(rt1 != rt2){
                            sz[rt1.first][rt1.second] += sz[rt2.first][rt2.second];
                            edg[rt1.first][rt1.second] += edg[rt2.first][rt2.second];
                            sqr[rt1.first][rt1.second] += sqr[rt2.first][rt2.second];
                            par[rt2.first][rt2.second] = rt1;
                        }
                    }
                    else if(i && j){
                        if(on[x+i][y+j] && on[x+i][y] && on[x][y+j]){
                            auto rt = getrt(x, y);
                            sqr[rt.first][rt.second]++;
                        }
                    }
                }
            }
        }
        set<pair<int, int>> st;
        for(auto n : v[w]){
            auto rt = getrt(n.first, n.second);
            if(!st.count(rt)){
                //cout << sz[rt.first][rt.second] - edg[rt.first][rt.second] + sqr[rt.first][rt.second] << endl;
                if(sz[rt.first][rt.second] - edg[rt.first][rt.second] + sqr[rt.first][rt.second] == 1){
                    ans += sz[rt.first][rt.second];
                    //cout << w << endl;
                }
            }
            st.insert(rt);
        }
    }
    cout << ans << endl;
}

#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> rgraph[5005], graph[5005];
bool tkn[5005], st[5005];
bool win[5005];
bool vis[5005];
int todgr[5005], odgr[5005];
int qu[5005];

vector<int> who_wins(vector<int> owr, vector<int> re, vector<int> u, vector<int> v){
    N = owr.size();
    M = u.size();
    for(int i= 0; i<M; i++){
        u[i]++;
        v[i]++;
        graph[u[i]].push_back(v[i]);
        rgraph[v[i]].push_back(u[i]);
        odgr[u[i]]++;
    }
    for(int i=0 ; i<N; i++){
        tkn[i+1] = owr[i];
        st[i+1] = re[i];
        win[i+1] = 1;
    }
    for(int t = 1; t<=2500; t++){
        int l = 1, r = 0;
        for(int i= 1; i<=N; i++){
            if(win[i] && st[i]){
                qu[++r] = i;
            }
            todgr[i] = odgr[i];
            vis[i] =0;
        }
        while(l<=r){
            int n = qu[l++];
            for(int e : rgraph[n]){
                todgr[e]--;
                if(win[e] && (tkn[e] || !todgr[e]) && !vis[e]){
                    vis[e] = 1;
                    if(!st[e]){
                        qu[++r] = e;
                    }
                }
            }
        }
        for(int i = 1; i<=N; i++){
            if(!vis[i]){
                win[i] = 0;
            }
        }
    }
    vector<int> ans;
    for(int i = 1; i<=N; i++){
        ans.push_back(win[i]);
    }
    return ans;
}

int main(){
    vector<int> who = {0, 1};
    vector<int> stations = {1, 0};
    vector<int> u = {0, 0, 1, 1};
    vector<int> v = {0, 1, 0, 1};
    vector<int> a = who_wins(who, stations, u, v);
    cout << a[0] << " " << a[1] << endl;
}


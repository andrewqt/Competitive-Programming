#include <bits/stdc++.h>

using namespace std;

vector<int> graph[25000];
int sz[25000], hvy[25000];
string arr[25000];
bool works[25000];
long long hsh[250000][5];
long long MOD = 1000000007, sd[5] = {31, 131, 43, 139, 97};
long long powsd[100005][2];
int N;

void dfs1(int n, int k){
    sz[n] = max(0, (int) (arr[n].size() - k + 1));
    for(int e : graph[n]){
        dfs1(e, k);
        sz[n] += sz[e];
        hvy[n] = sz[hvy[n]] < sz[e] ? e : hvy[n];
    }
}

unordered_set<int> dfs2(int n, int k, int a){
    unordered_set<int> s;
    int cnt = 0;
    if(hvy[n]){
        s = dfs2(hvy[n], k, a);
        cnt = s.size();
    }
    bool b = 0;
    for(int e : graph[n]){
        if(e != hvy[n]){
            unordered_set<int> t = dfs2(e, k, a);
            for(int h : t){
                s.insert(h);
                cnt++;
                b |= cnt > s.size();
            }
        }
    }
    works[n] &= b;
    for(int i = 1; i<=arr[n].size(); i++){
        hsh[i][a] = (hsh[i-1][a]*sd[a] + arr[n][i-1] - 'A'+1)%MOD;
        if(i >= k){
            long long v = ((hsh[i][a]-hsh[i-k][a]*powsd[k][a])%MOD+MOD)%MOD;
            s.insert(v);
        }
    }
    return s;
}

int main(){
    cin >> N;
    for(int i = 2; i<=N; i++){
        int p;
        cin >> p;
        graph[p].push_back(i);
    }
    for(int i = 1; i<N; i++){
        if(graph[i].size() > 1){
            break;
        }
        else if(i == N-1){
            cout << -1 << endl;
            return 0;
        }
    }
    powsd[0][0] = powsd[0][1] = 1;
    for(int i= 1; i<=100000; i++){
        for(int j= 0; j<5; j++){
            powsd[i][j] = (powsd[i-1][j]*sd[j])%MOD;
        }
    }
    for(int i =1 ; i<=N; i++){
        cin >> arr[i];
        for(int j = 0; j<arr[i].size(); j++){
            if(arr[i][j] == 'G'){
                arr[i][j] = 'B';
            }
            if(arr[i][j] == 'T'){
                arr[i][j] = 'D';
            }
        }
    }
    int l = 1, r = 100000, ans = 0;
    while(l <= r){
        int mid = (l+r)>>1;
        dfs1(1, mid);
        for(int a = 0; a<5; a++){
            dfs2(1, mid, a);
        }
        for(int i =1 ; i<=N; i++){
            if(works[i]){
                l = mid+1;
                ans = mid;
                break;
            }
            else if(i == N){
                r = mid - 1;
            }
        }
        fill(works, works+N+1, 1);
    }
    cout << ans << endl;
}

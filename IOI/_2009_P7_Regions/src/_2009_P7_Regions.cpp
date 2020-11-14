#include <bits/stdc++.h>

using namespace std;

int N, R, Q, M, B = 500;
vector<int> graph[200005], nod[25005];
int reg[200005], rsz[25005];
int lft[200005], rht[200005], t = 0;
int ishvy[25005];
int hvyans[25005][405];

void dfs(int n){
    lft[n] = ++t;
    nod[reg[n]].push_back(n);
    for(int e : graph[n]){
        dfs(e);
    }
    rht[n] = ++t;
}

int solve(int s, int t){
    int ans = 0;
    for(int n : nod[s]){
        int l = 0, r = nod[t].size()-1, L = nod[t].size(), R = -1;
        while(l <= r){
            int mid = l+r>>1;
            if(lft[nod[t][mid]] > lft[n]){
                L = mid;
                r = mid - 1;
            }
            else{
                l = mid + 1;
            }
        }
        l = 0, r = nod[t].size()-1;
        while(l <= r){
            int mid = l+r>>1;
            if(lft[nod[t][mid]] < rht[n]){
                R = mid;
                l = mid + 1;
            }
            else{
                r = mid - 1;
            }
        }
        ans += max(0, R-L+1);
    }
    return ans;
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> R >> Q;
    cin >> reg[1];
    for(int i = 2; i<=N; i++){
        int p;
        cin >> p >> reg[i];
        graph[p].push_back(i);
        rsz[reg[i]]++;
    }
    dfs(1);
    for(int r = 1; r<=R; r++){
        if(rsz[r] >= B){
            ishvy[r] = ++M;
            for(int i = 1; i<=R; i++){
                hvyans[i][M] = solve(i, r);
            }
        }
    }
    while(Q--){
        int a, b;
        cin >> a >> b;
        if(ishvy[b]){
            cout << hvyans[a][ishvy[b]] << endl;
        }
        else{
            cout << solve(a, b) << endl;
        }
    }
}

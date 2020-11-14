#include <bits/stdc++.h>

using namespace std;

int N, M, X, Y;
vector<vector<int>> cmp;
vector<pair<int, int>> graph[1505];
vector<int> c;
int dis[1505];
long long dp[2505], cnt[2505], t[2505];
int MOD = 1e9 + 7;
long long ans = 0, crnt = 0, pthcnt = 0;

long long mult(long long a, long long b){
    return (a%MOD*b%MOD)%MOD;
}

long long add(long long a, long long b){
    return (a%MOD+b%MOD)%MOD;
}

long long sub(long long a, long long b){
    return ((a-b)%MOD+MOD)%MOD;
}

void dfs1(int n){
    c.push_back(n);
    dis[n] = 1;
    for(pair<int, int> e : graph[n]) {
        if(!dis[e.first]){
            dfs1(e.first);
        }
    }
}

void dfs2(int n){
    for(pair<int, int> e : graph[n]){
        if(dis[e.first] == -1){
            dis[e.first] = dis[n] + e.second;
            if(dis[e.first] < Y){
                cnt[dis[e.first]]++;
            }
            crnt += dis[e.first];
            dfs2(e.first);
        }
    }
}

int main(){
    freopen("mooriokart.in", "r", stdin);
	freopen("mooriokart.out", "w", stdout);
    cin >> N >> M >> X >> Y;
    for(int i = 1; i<=M; i++){
        int a, b, v;
        cin >> a >> b >> v;
        graph[a].push_back({b, v});
        graph[b].push_back({a, v});
    }
    for(int i = 1; i<=N; i++){
        if(!dis[i]){
//            cout << i << endl;
            dfs1(i);
            cmp.push_back(c);
            c.clear();
        }
    }
    bool f = 1;
    for(vector<int> v : cmp){
        crnt = 0;
        int k = v.size();
        for(int n : v){
            fill(dis, dis+1501, -1);
            dis[n] = 0;
            dfs2(n);
        }
        if(f){
            swap(dp, cnt);
            for(int i = 0; i<=2500; i++){
                dp[i] /= 2;
            }
            ans = crnt/2;
            f = 0;
            pthcnt = k*(k-1)/2;
        }
        else{
            crnt %= MOD;
            ans = add(mult(ans, k*(k-1)), mult(crnt, pthcnt));
            for(int i = 0; i<=2500; i++){
                if(cnt[i]){
                    for(int j = 0; j<=2500-i; j++){
                        t[i+j] = add(t[i+j], mult(cnt[i], dp[j]));
                    }
                }
            }
            pthcnt = mult(k*(k-1), pthcnt);
            swap(dp, t);
        }
//        cout << ans << endl;
        fill(cnt, cnt+2501, 0);
        fill(t, t+2501, 0);
    }
    int s = cmp.size();
    for(int i = 0; i<Y-X*s; i++){
        ans = sub(ans, mult(dp[i], i));
        pthcnt = sub(pthcnt, dp[i]);
    }
    ans = add(ans, mult(pthcnt, mult(s, X)));
    for(int i = 1; i<s; i++){
        ans = mult(ans, i);
    }
    cout << ans << endl;
}

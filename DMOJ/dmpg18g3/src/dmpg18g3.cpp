#include <bits/stdc++.h>

using namespace std;

struct Query{
    int p, d, id;
    bool operator < (Query q) const{
        if(d == q.d){
            return id > q.id;
        }
        return d > q.d;
    }
};

int N, Q, B = 450;
int lft[200005], rht[200005], et[400005], tim = 0;
vector<int> graph[200005];
int dep[200005], par[200005], dgr[200005];
bool ishvy[200005];
long long hvysz[200005];
int hvyid[200005];
long long ans[200005];
long long BIT[400005];
priority_queue<Query> pq;
vector<pair<int, int>> hvyqu[200005];
queue<int> dq;

void upd(int p){
    for(int i = p; i<=tim; i+=i&-i){
        BIT[i]++;
    }
}

long long sum(int p){
    int s = 0;
    for(int i = p; i>0; i-=i&-i){
        s += BIT[i];
    }
    return s;
}

void dfs(int n){
    lft[n] = ++tim;
    et[tim] = n;
    for(int e : graph[n]){
        if(e != par[n]){
            dep[e] = dep[n]+1;
            par[e] = n;
            dfs(e);
        }
    }
    rht[n] = ++tim;
    et[tim] = n;
}

void bfs(int n){
    hvyid[n] = 0;
    hvysz[n] = 0;
    for(int e : graph[n]){
        if(e != par[n]){
            hvyid[e] = e;
            dq.push(e);
        }
    }
    long long cnt = 1, tot = 1;
    for(pair<int, int> q : hvyqu[n]){
        while(dq.size() && dep[dq.front()] <= q.first){
            int c = dq.front();
            dq.pop();
            hvysz[hvyid[c]]++;
            cnt++;
            tot += cnt-hvysz[hvyid[c]];
            for(int e : graph[c]){
                if(e != par[c]){
                    hvyid[e] = hvyid[c];
                    dq.push(e);
                }
            }
        }
        ans[q.second] = tot;
    }
    while(dq.size()){
        dq.pop();
    }
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for(int i = 1; i<N; i++){
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
        dgr[a]++;
        dgr[b]++;
    }
    dfs(1);
    for(int i = 1; i<=N; i++){
        if(dgr[i] > B){
            ishvy[i] = 1;
        }
        else{
            ishvy[i] = 0;
        }
    }
    cin >> Q;
    for(int i = 1; i<=Q; i++){
        int n, d;
        cin >> n >> d;
        d += dep[n];
        if(!ishvy[n]){
            pq.push({n, d, i});
        }
        else{
            hvyqu[n].push_back({d, i});
        }
    }
    for(int i = 1; i<=N; i++){
        pq.push({i, dep[i], 0});
    }
    for(int i = 1; i<=N; i++){
        if(ishvy[i]){
            sort(hvyqu[i].begin(), hvyqu[i].end());
            bfs(i);
        }
    }
    while(pq.size()){
        Query q = pq.top();
        pq.pop();
        if(q.id){
            long long cnt = 1;
            ans[q.id]++;
            for(int e : graph[q.p]){
                if(e != par[q.p]){
                    long long s = sum(rht[e]);
                    s -= sum(lft[e]);
                    ans[q.id] += cnt * s;
                    cnt += s;
                }
            }
        }
        else{
            upd(rht[q.p]);
        }
    }
    for(int i = 1; i<=Q; i++){
        printf("%lld\n", ans[i]);
    }
}

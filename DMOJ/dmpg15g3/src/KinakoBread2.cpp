#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> graph[200001];
deque<int> ll;
string s;
bool vis[200001], typ[200001];
int par[200001], sz[200001], dep[200001];
pair<int, int> dist[200001];
long long BIT[200005];

void upd(int n, int v){
    n++;
    while(n <= 200000){
        BIT[n] += v;
        n += n&-n;
    }
}

long long qu(int n){
    n++;
    long long ans = 0;
    while(n > 0){
        ans += BIT[n];
        n -= n&-n;
    }
    return ans;
}

void dfs(int n){
    sz[n] = 1;
    for(int e : graph[n]){
        if(e != par[n] && !vis[e]){
            par[e] = n;
            dfs(e);
            sz[n] += sz[e];
        }
    }
}

long long swpln(vector<pair<int, int>> al, int x, int y){
//    cout << x << " " << y << endl;
    long long ans = 0;
    for(auto p : al){
        upd(p.second, 1);
    }
    int idx = al.end() - al.begin() - 1;
    for(auto p : al){
//        cout << " " << p.first << " " << p.second << endl;
        if(p.first > x){
            break;
        }
        while(idx >= 0 && p.first + al[idx].first > x){
            upd(al[idx].second, -1);
            idx--;
        }
        if(y < p.second) {
            continue;
        }
        ans += qu(y-p.second);
        if(2*p.first <= x && 2*p.second <= y){
            ans--;
        }
//        cout << p.first << " " << p.second << " " << ans << " " << idx << endl;
    }
    while(idx >= 0){
        upd(al[idx].second, -1);
        idx--;
    }
//    cout << " " << ans << endl;
    return ans/2;
}

int getcent(int n){
    dfs(n);
    int siz = sz[n];
    while(true){
        int hvy = 0;
        for(int e : graph[n]){
            if(e != par[n] && !vis[e]){
                hvy = sz[hvy] > sz[e] ? hvy : e;
            }
        }
        if(sz[hvy]*2 <= siz){
            break;
        }
        else{
            n = hvy;
        }
    }
    return n;
}

long long solve(int n, int xlb, int ylb, int xub, int yub){
    long long ans = 0;
    int dx = 0, dy = 0;
    vector<pair<int, int>> altot, alsub;
    altot.push_back({0,0});
    n = getcent(n);
//    cout << n << " " << x << " " << y << endl;
    vis[n] = 1;
    par[n] = 0;
    if(typ[n]){
        dx--;
    }
    else{
        dy--;
    }
//    cout << X << " " << Y << endl;
    if(xlb <= -dx && -dx <= xub && ylb <= -dy && -dy <= yub){
        ans++;
    }
    for(int edge : graph[n]){
        if(!vis[edge]){
            ll.push_back(edge);
            par[edge] = n;
            dist[edge] = {0,0};
            while(!ll.empty()){
                int crnt = ll.front();
//                cout << "dist: " << crnt << " " << dist[crnt].first << " " << dist[crnt].second << endl;
                if(typ[crnt]){
                    dist[crnt].first++;
                }
                else{
                    dist[crnt].second++;
                }
                altot.push_back(dist[crnt]);
                alsub.push_back(dist[crnt]);
                ll.pop_front();
                for(int e : graph[crnt]){
                    if(par[crnt] != e && !vis[e]){
                        par[e] = crnt;
                        dist[e].first = dist[crnt].first;
                        dist[e].second = dist[crnt].second;
                        ll.push_back(e);
                    }
                }
                dist[crnt] = {0,0};
            }
//            for(auto p : alsub){
//                cout << p.first << " " << p.second << endl;
//            }
//            cout << endl;
            sort(alsub.begin(), alsub.end());
            ans -= swpln(alsub, xub+dx, yub+dy);
            ans += swpln(alsub, xub+dx, ylb+dy-1);
            ans += swpln(alsub, xlb+dx-1, yub+dy);
            ans -= swpln(alsub, xlb+dx-1, ylb+dy-1);
            alsub.clear();
        }
    }
    sort(altot.begin(), altot.end());
    ans += swpln(altot, xub+dx, yub+dy);
    ans -= swpln(altot, xub+dx, ylb+dy-1);
    ans -= swpln(altot, xlb+dx-1, yub+dy);
    ans += swpln(altot, xlb+dx-1, ylb+dy-1);
//    cout << ans << endl;
    for(int e : graph[n]){
        if(!vis[e]){
            ans += solve(e, xlb, ylb, xub, yub);
        }
    }
    return ans;
}

int main(){
    int xlb, ylb, xub, yub;
    scanf("%d %d %d %d %d\n", &N, &xlb, &xub, &ylb, &yub);
    cout << "HERE" << endl;
    getline(cin, s);
    for(int i = 1; i<=N; i++){
        typ[i] = s[i-1] == 'K';
    }
    for(int i =1; i<N; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    printf("%lld\n", solve(1, xlb, ylb, xub, yub));
}

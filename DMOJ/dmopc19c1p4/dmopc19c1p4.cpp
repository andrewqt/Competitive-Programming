#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<int> graph[100005];
long long MOD = 1915442707;
long long pows[100005];
long long cache[100005];
char ans[100005];
map<long long, vector<int>> mp;
map<long long, set<int>> cgraph;
map<long long, char> let;
map<long long, bool> vis;
set<int> st;

long long add(long long a, long long b){
    return (a+b)%MOD;
}

long long mult(long long a, long long b){
    return (a*b)%MOD;
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> M;
    for(int i = 1; i<=M; i++){
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    pows[0] = 1;
    for(int i = 1; i<=N; i++){
        pows[i] = mult(pows[i-1], 31);
    }
    int sz = 0;
    for(int n = 1; n<=N; n++){
        graph[n].push_back(n);
        long long hsh = 0;
        for(int e : graph[n]){
            hsh = add(hsh, pows[e]);
        }
        if(!mp.count(hsh)){
            sz++;
        }
        mp[hsh].push_back(n);
        cache[n] = hsh;
    }
    if(sz > 26){
        cout << -1 << endl;
        return 0;
    }
    for(auto p : mp){
        int n = p.second.front();
        for(int e : graph[n]){
            cgraph[cache[n]].insert(cache[e]);
        }
        if(cgraph[p.first].size() >= 4){
            cout << -1 << endl;
            return 0;
        }
    }
    char cur = 'a';
    for(auto p : mp){
        long long n = p.first;
        if(vis[n] || cgraph[n].size() == 3){
            continue;
        }
        while(!vis[n]){
            vis[n] = 1;
            if(cur > 'z'){
                cout << -1 << endl;
                return 0;
            }
            let[n] = cur;
            cur++;
            for(int e : cgraph[n]){
                if(!vis[e]){
                    n = e;
                    break;
                }
            }
        }
        cur++;
    }
    for(auto p : mp){
        long long n = p.first;
        while(!vis[n]){
            vis[n] = 1;
            if(cur > 'z'){
                cout << -1 << endl;
                return 0;
            }
            let[n] = cur;
            cur++;
            for(int e : cgraph[n]){
                if(!vis[e]){
                    n = e;
                    break;
                }
            }
        }
    }
    for(int n = 1; n<=N; n++){
        ans[n] = let[cache[n]];
    }
    for(auto p : mp){
        int n = p.second.front();
        for(int e : graph[n]){
            //cout << n << " " << e << endl;
            st.insert(e);
        }
        for(int k = 1; k<=N; k++){
            int a = (int) (ans[n]-'a'), b = (int) (ans[k]-'a');
            //cout << a << " " << n << " " << b << " " << k << endl;
            if((a == 0 && b == 25) || (a == 25 && b == 0) || (abs(a-b) <= 1)){
                if(!st.count(k)){
                    //cout << "ping" << endl;
                    cout << -1 << endl;
                    return 0;
                }
            }
            else{
                if(st.count(k)){
                    //cout << "pong" << endl;
                    cout << -1 << endl;
                    return 0;
                }
            }
        }
        st.clear();
    }
    for(int n = 1; n<=N; n++){
        cout << ans[n];
    }
    cout << endl;
}

/*
26 25
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 11
11 12
12 13
13 14
14 15
15 16
16 17
17 18
18 19
19 20
20 21
21 22
22 23
23 24
24 25
25 26
26 1

25 24
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 11
11 12
12 13
13 14
14 15
15 16
16 17
17 18
18 19
19 20
20 21
21 22
22 23
23 24
24 25
25 1

5 7
1 2
2 3
1 3
4 2
4 3
5 2
5 1
*/

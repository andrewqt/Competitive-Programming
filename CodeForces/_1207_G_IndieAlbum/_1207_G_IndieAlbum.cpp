#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds; 
using namespace std;
 
int N, Q;
vector<pair<int, char>> graph[400005];
long long pows[400005];
long long hsh[400005];
const long long sd = 2377;
const long long MOD = 1617945349;
int dep[400005];
vector<int> qu[400005];
int hshq[400005];
int len[400005];
vector<int> v;
string s;
int ans[400005];
gp_hash_table<int, int> mp;
int mx[400005];
 
long long mult(long long a, long long b){
    return a*b%MOD;
}
 
long long add(long long a, long long b){
    return (a+b)%MOD;
}
 
long long sub(long long a, long long b){
    a = add(a, -b);
    if(a < 0){
        a += MOD;
    }
    return a;
}
 
int gethsh(int l, int r){
    return (int) (sub(hsh[r], mult(hsh[l-1], pows[r-l+1])));
}
 
void predfs(int n){
    for(int q : qu[n]){
        mx[n] = max(mx[n], len[q]);
    }
    for(auto e : graph[n]){
        dep[e.first] = dep[n] + 1;
        predfs(e.first);
        mx[n] = max(mx[n], mx[e.first]);
    }
}
 
void dfs(int n, int l){
    if(dep[n] >= l){
        //cout << "add: " << n << " " << gethsh(dep[n]-l+1, dep[n]) << endl;
        mp[gethsh(dep[n]-l+1, dep[n])]++;
    }
    for(int q : qu[n]){
        if(len[q] == l){
            //cout << q << " " << hshq[q] << " " << mp[hshq[q]] << endl;
            ans[q] = mp[hshq[q]];
        }
    }
    for(auto e : graph[n]){
        if(mx[e.first] >= l){
            hsh[dep[e.first]] = add(mult(hsh[dep[n]], sd), e.second);
            dfs(e.first, l);
        }
    }
    if(dep[n] >= l){
        //cout << "del: " << n << " " << gethsh(dep[n]-l+1, dep[n]) << endl;
        mp[gethsh(dep[n]-l+1, dep[n])]--;
    }
}
 
int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N;
    for(int i= 1; i<=N; i++){
        int t;
        cin >> t;
        if(t == 1){
            char c;
            cin >> c;
            graph[0].emplace_back(i, c);
        }
        else{
            int n;
            char c;
            cin >> n >> c;
            graph[n].emplace_back(i, c);
        }
    }
    pows[0] = 1;
    for(int i = 1; i<=N; i++){
        pows[i] = mult(pows[i-1], sd);
    }
    cin >> Q;
    for(int i =1; i<=Q; i++){
        int n;
        cin >> n >> s;
        len[i] = s.size();
        v.emplace_back(len[i]);
        qu[n].emplace_back(i);
        for(int j = 1; j<=len[i]; j++){
            hshq[i] = (int) (add(s[j-1], mult(hshq[i], sd)));
        }
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    predfs(0);
    for(int l : v){
        dfs(0, l);
        mp.clear();
    }
    for(int i = 1; i<=Q; i++){
        cout << ans[i] << "\n";
    }
}
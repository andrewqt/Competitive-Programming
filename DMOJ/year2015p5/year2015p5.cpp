#include <bits/stdc++.h>

using namespace std;

int N, M;
bitset<2001> dp[2001];
string str, s;
int nxt[1500000][26];
int idx = 1;
bool endpt[1500000];

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> str >> M;
    for(int i = 1; i<=M; i++){
        cin >> s;
        int crnt = 1;
        for(int j = s.size()-1; j>=0; j--){
            if(!nxt[crnt][s[j]-'a']){
                nxt[crnt][s[j]-'a'] = ++idx;
            }
            crnt = nxt[crnt][s[j]-'a'];
        }
        endpt[crnt] = 1;
    }
    N = str.size();
    int ans = -N;
    dp[0].set(0);
    for(int i = 1; i<=N; i++){
        dp[i].set(i);
        int crnt = 1;
        for(int j = i-1; j>=0 && crnt; j--){
            crnt = nxt[crnt][str[j]-'a'];
            if(endpt[crnt]){
                dp[i]|=dp[j];
            }
        }
        ans += dp[i].count();
    }
    cout << ans << endl;
}

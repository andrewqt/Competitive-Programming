#include <bits/stdc++.h>

using namespace std;

int N, Q;
int nxt[1000000][26];
int rt[100005];
int endpt[1000000], pth[1000000];
int idx = 0;
string s;

void cop(int s, int t){
    endpt[t] = endpt[s];
    pth[t] = pth[s];
    for(int i = 0; i<26; i++){
        nxt[t][i] = nxt[s][i];
    }
}

int query(int crnt){
    int ret = 0;
    for(int i=0; i<s.size(); i++){
        ret += endpt[crnt];
        crnt = nxt[crnt][s[i]-'a'];
    }
    ret += pth[crnt];
    return ret;
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> Q;
    for(int i =1 ; i<=N; i++){
        cin >> s;
        rt[i] = ++idx;
        cop(rt[i-1], rt[i]);
        int crnt = idx;
        for(int j= 0; j<s.size(); j++){
            idx++;

            cop(nxt[crnt][s[j]-'a'], idx);
            nxt[crnt][s[j]-'a'] = idx;
            crnt = idx;
            pth[crnt]++;
        }
        endpt[crnt]++;
    }
    while(Q--){
        int l, r;
        cin >> s >> l >> r;
        cout << query(rt[r]) - query(rt[l-1]) << "\n";
    }
}

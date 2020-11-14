#include <bits/stdc++.h>

using namespace std;

string s, t;
int cnt = 0;
int nxt[7505][200];
long long val[7505][200];
long long N;

void rec(long long n){
    if(n == 1){
        for(int i = 0; i<t.size(); i++){
            nxt[i][cnt] = i;
            for(int j = 0; j<s.size(); j++){
                if(t[nxt[i][cnt]] == s[j] || s[j] == '&'){
                    nxt[i][cnt]++;
                    if(nxt[i][cnt] == t.size()){
                        val[i][cnt]++;
                        nxt[i][cnt] = 0;
                    }
                }
            }
        }
        return;
    }
    rec(n/2);
    cnt++;
    for(int i = 0; i<t.size(); i++){
        nxt[i][cnt] = nxt[nxt[i][cnt-1]][cnt-1];
        val[i][cnt] = val[nxt[i][cnt-1]][cnt-1] + val[i][cnt-1];
    }
    if(n&1){
        cnt++;
        for(int i = 0; i<t.size(); i++){
            nxt[i][cnt] = nxt[nxt[i][cnt-1]][0];
            val[i][cnt] = val[nxt[i][cnt-1]][0] + val[i][cnt-1];
        }
    }
}

int main(){
        //freopen((f+"stringsin.txt").c_str(), "r", stdin);
        //freopen((f+"stringsout.txt").c_str(), "w", stdout);
        //cnt = 0;
        cin >> s >> t >> N;
        rec(N);
        cout << val[0][cnt] << endl;
}

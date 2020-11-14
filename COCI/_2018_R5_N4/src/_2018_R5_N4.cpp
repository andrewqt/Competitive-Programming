#include <bits/stdc++.h>

using namespace std;

int N, M;
unordered_map<int, unsigned int> mp[1<<6][1<<6];
long long pows[6] = {1, 26, 676, 17576, 456976, 11881376};
pair<int, int> arr[50005];
string s[50005];
int msk[50005];

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for(int i = 1; i<=N; i++){
        cin >> s[i];
        int val = 0;
        for(int j = 0; j<M; j++){
            if(s[i][j] == '?'){
                msk[i] += (1<<j);
            }
        }
        arr[i] = {msk[i], i};
    }
    long long ans = 0;
    sort(arr+1, arr+1+N, greater<pair<int, int>>());
    for(int i = 1; i<=N; i++){
        int idx = arr[i].second;
        for(int m = msk[idx]; m<1<<M; m++){
            int hsh = 0;
            for(int k = 0; k<M; k++){
                if(!((1<<k)&m) && !((1<<k)&msk[idx])){
                    hsh += pows[k]*(s[idx][k]-'a');
                }
            }
            if(mp[m][msk[idx]].count(hsh)){
                ans += mp[m][msk[idx]][hsh];
            }
        }
        int hsh = 0;
        for(int m = 0; m<=msk[idx]; m++){
            int hsh = 0;
            for(int k = 0; k<M; k++){
                if(!((1<<k)&m) && !((1<<k)&msk[idx])){
                    hsh += pows[k]*(s[idx][k]-'a');
                }
            }
            mp[msk[idx]][m][hsh]++;
        }
    }
    cout << ans << endl;
}

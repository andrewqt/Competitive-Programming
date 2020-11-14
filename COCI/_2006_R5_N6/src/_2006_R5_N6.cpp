#include <bits/stdc++.h>

using namespace std;

int N;
long long seed = 31;
long long expo[200005];
long long hsh[200005];
string s;

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> s;
    expo[0] = 1;
    for(int i= 1; i<=N; i++){
        expo[i] = expo[i-1] * 31;
        hsh[i] = hsh[i-1]*31 + s[i-1]-'a';
    }
    int l = 1, r = N, ans = 0;
    while(l <= r){
        int mid = l+r>>1;
        vector<long long> v;
        for(int i = mid; i<=N; i++){
            v.push_back(hsh[i]-hsh[i-mid]*expo[mid]);
        }
        sort(v.begin(), v.end());
        bool works = 0;
        for(int i = 1; i<v.size(); i++){
            if(v[i-1] == v[i]){
                works = 1;
            }
        }
        if(works){
            l = mid + 1;
            ans = mid;
        }
        else{
            r = mid - 1;
        }
    }
    cout << ans << endl;
}

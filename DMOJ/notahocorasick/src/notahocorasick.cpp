#include <bits/stdc++.h>

using namespace std;

int N;
long long MOD;
long long M1 = 1780078627, M2 = 1285654789;
long long sd1 = 31, sd2 = 131;
pair<long long, long long> pows[100005];
pair<long long, long long> hsh[200005];
string s;
vector<int> len;
unordered_map<long long, int> mp[100005];
vector<long long> temp;
long long dp[100005];

void build(int K){
    for(int i = 1; i<=K; i++){
        hsh[i].first += hsh[i-1].first * sd1;
        hsh[i].second += hsh[i-1].second * sd2;
        hsh[i].first %= M1, hsh[i].second %= M2;
    }
}

long long gethsh(int r, int l){
    long long a = hsh[r].first - hsh[l-1].first * pows[r-l+1].first;
    long long b = hsh[r].second - hsh[l-1].second * pows[r-l+1].second;
    a %= M1, b %= M2;
    if(a < 0){
        a += M1;
    }
    if(b < 0){
        b += M2;
    }
    return a*M2+b;
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> MOD;
    pows[0] = {1LL, 1LL};
    for(int i = 1; i<=100000; i++){
        pows[i] = {pows[i-1].first * sd1, pows[i-1].second * sd2};
        pows[i].first %= M1, pows[i].second %= M2;
    }
    for(int i= 1; i<=N; i++){
        cin >> s;
        int K = s.size();
        len.push_back(K);
        for(int k = 1; k<=K; k++){
            hsh[k].first = hsh[k+K].first = hsh[k].second = hsh[k+K].second = s[k-1]-'a'+1;
        }
        build(2*K);
        for(int k = K+1; k<=2*K; k++){
            //cout << gethsh(k, k-K+1).first << " " << gethsh(k, k-K+1).second << endl;
            temp.push_back(gethsh(k, k-K+1));
        }
        sort(temp.begin(), temp.end());
        temp.erase(unique(temp.begin(), temp.end()), temp.end());
        for(auto p : temp){
            mp[K][p]++;
        }
        temp.clear();
    }
    cin >> s;
    int K = s.size();
    for(int i = 1; i<=K; i++){
        hsh[i].first = hsh[i].second = s[i-1] - 'a' + 1;
    }
    build(K);
    dp[0] = 1;
    sort(len.begin(), len.end());
    len.erase(unique(len.begin(), len.end()), len.end());
    for(int i = 1; i<=K; i++){
        for(int l : len){
            if(l > i){
                break;
            }
            long long te = gethsh(i, i-l+1);
            if(mp[l].count(te)){
                dp[i] += dp[i-l] * mp[l][te];
            }
        }
        dp[i] %= MOD;
    }
    cout << dp[K]%MOD << endl;
}

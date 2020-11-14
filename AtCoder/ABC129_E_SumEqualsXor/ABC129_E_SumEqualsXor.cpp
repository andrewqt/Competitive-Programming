#include <bits/stdc++.h>

using namespace std;

string s;
long long MOD = 1e9+7;
long long power[100005][4];

int main(){
    cin >> s;
    int N = s.size();
    long long ans = 0;
    long long pre = 1;
    power[0][2] = power[0][3] = 1;
    for(int k = 2; k<=3; k++){
        for(int i = 1; i<=N; i++){
            power[i][k] = power[i-1][k]*k;
            power[i][k] %= MOD;
        }
    }
    for(int i = 0; i<N; i++){
        if(s[i] == '1'){
            ans += pre*power[N-i-1][3];
            ans %= MOD;
            pre *= 2;
            pre %= MOD;
        }
    }
    ans += pre;
    ans %= MOD;
    cout << ans << endl;
}

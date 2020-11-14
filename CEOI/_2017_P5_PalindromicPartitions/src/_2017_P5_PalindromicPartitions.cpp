#include <bits/stdc++.h>

using namespace std;

int T;
string s;
long long hsh[1000005];
long long sd = 31, MOD = 1000000007;
long long power[1000005];

long long add(long long a, long long b){
    return (a+b)%MOD;
}

long long mult(long long a, long long b){
    return a*b%MOD;
}

long long sub(long long a, long long b){
    a -= b;
    a %= MOD;
    if(a < 0){
        a += MOD;
    }
    return a;
}

long long gethsh(int l, int r){
    return sub(hsh[r], mult(power[r-l+1], hsh[l-1]));
}

int main(){
    cin >> T;
    while(T--){
        cin >> s;
        int N = s.size();
        power[0] = 1;
        for(int i =1 ; i<=N; i++){
            power[i] = mult(power[i-1], sd);
            hsh[i] = add(mult(hsh[i-1], sd), (s[i-1]-'a'));
        }
        hsh[N+1] = hsh[N];
        int lstl = 0, lstr = N+1;
        int ans = 1;
        for(int l = 1, r = N; l<r; l++, r--){
            if(gethsh(lstl+1, l) == gethsh(r, lstr-1)){
                ans += 2;
                if(l+1 == r){
                    ans--;
                }
                lstl = l, lstr = r;
            }
        }
        cout << ans << "\n";
    }
}

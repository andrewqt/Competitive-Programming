#include <bits/stdc++.h>

using namespace std;

long long a, b, p, x;
int idx[2000000];

pair<long long, long long> extgcd(long long n, long long m){
    if(n == 0){
        return {0, 1};
    }
    auto p = extgcd(m%n, n);
    return {p.second-m/n*p.first, p.first};
}

int main(){
    cin >> a >> b >> p >> x;
    fill(idx, idx+2000000, -1);
    long long l = 0;
    for(long long i = 0, c = 1; i<p; i++, c*=a, c%=p){
        cout << "idx: " << c << endl;
        if(idx[c] != -1){
            l = i;
            break;
        }
        idx[c] = i;
    }
    cout << "here" << endl;
    long long ans = 0;
    long long t = extgcd(l, p).first;
    t %= (l*p);
    if(t < 0){
        t += l*p;
    }
    for(long long i = 0; i<p; i++){
        if(idx[i] != -1){
            long long k = extgcd(i, p).first;
            k %= p;
            if(k < 0){
                k += p;
            }
            k *= b;
            k %= p;
            k = idx[i]-k;
            k%=p;
            if(k < 0){
                k += p;
            }
            k *= t;
            cout << "k: " << k << endl;
        }
    }
    cout << ans << endl;
}

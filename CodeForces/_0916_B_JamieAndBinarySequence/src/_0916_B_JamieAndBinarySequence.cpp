#include <bits/stdc++.h>

using namespace std;

long long N, K;
map<int, int> cnt;
int main(){
    cin >> N >>K;
    if(K < __builtin_popcountll(N)){
        cout << "No" << endl;
        return 0;
    }
    for(long long k = (1LL<<60); k; k/=2){
        if(k < N){
            cnt[__builtin_ctz(k)]++;
            N -= k;
            K--;
        }
    }
    while(K){
        for(int k = 60; 1; k--){
            if(cnt[k]){
                cnt[k-1] += 2;
                cnt[k]--;
                K--;
                break;
            }
        }
    }
    cout << "Yes" << "\n";
    for(int k = 60; k>=-60; k--){
        for(int i = 0; i<cnt[k]; i++){
            cout << k << " ";
        }
    }
}

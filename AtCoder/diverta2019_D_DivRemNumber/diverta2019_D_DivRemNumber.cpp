#include <bits/stdc++.h>

using namespace std;

long long N;

int main(){
    cin >> N;
    long long ans = 0;
    for(long long i = 1; i<=sqrt(N); i++){
        if(N%i == 0){
            long long m = N/i-1;
            if(m && N/m == N%m){
                ans += m;
            }
            if(N/i != i){
                m = i-1;
                if(m && N/m == N%m){
                    ans += m;
                }
            }
        }
    }
    cout << ans << endl;
}

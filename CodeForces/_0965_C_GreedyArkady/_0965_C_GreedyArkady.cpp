#include <bits/stdc++.h>

using namespace std;

long long N, K, M, D;

int main(){
    cin >> N >> K >> M >> D;
    long long ans = 0;
    if(M <= 100000000){
        for(long long i = 1; i<=M; i++){
            if((N+K*i-1)/(K*i) <= D){
                ans = max(ans, (N+K*i-1)/(K*i)*i);
            }
        }
    }
    else{
        for(long long i = 1; i<=D; i++){
            long long T = max(M, N/(K*(max(D-1, 1)))+1LL);
            ans = max(ans, (N+K*i-1)/(T*K)*T);
        }
    }
    cout << ans << endl;
}

#include <bits/stdc++.h>

using namespace std;

long long N, M, K, V;

long long mult(long long a, long long b){
    return (a%M*b%M)%M;
}

long long power(long long b, long long e){
    if(e == 0){
        return 1LL;
    }
    long long mid = power(b, e/2);
    long long res = mult(mid, mid);
    return e%2 ? mult(res, b) : res;
}

int main(){
    cin >> N >> M >> K >> V;
    long long X = 0;
    for(int i = 0; i<K; i++){
        if((V&(1LL<<i))){
            X++;
        }
    }
    cout << power(2, N-1), K) << endl;
    cout << power((power(2, N)-1+M)%M, X) << endl;
    cout << power((power(2, N)-1+M)%M, K-X) << endl;
}

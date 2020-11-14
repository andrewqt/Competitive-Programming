#include <bits/stdc++.h>

using namespace std;

long long N, M, K;
long long cnt[1000005];

int main(){
    cin >> N >> M >> K;
    K = N*K;
    long long tot = 0;
    long long hrs = 0;
    for(int i =1; i<=N; i++){
        long long x;
        int y;
        cin >> x >> y;
        tot += x;
        cnt[y] += M-x;
    }
    if(K > tot)
    for(long long i = 0; i<=1000000; i++){
        if(cnt[i]+tot < K){
            hrs = hrs + cnt[i]*i;
            tot += cnt[i];
        }
        else if(cnt[i]+tot >= K){
            hrs = hrs + (K-tot)*i;
            break;
        }
    }
    cout << hrs << endl;
}

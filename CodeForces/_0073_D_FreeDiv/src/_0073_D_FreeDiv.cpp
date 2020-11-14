#include <bits/stdc++.h>

using namespace std;

int N, M, K;
int par[1000005];

int getrt(int n){
    return par[n] = (par[n] == n ? n : getrt(par[n]));
}

int main(){
    cin >> N >> M >> K;
    for(int i= 1; i<=N; i++){
        par[i] = i;
    }
    int num = N;
    for(int i= 1; i<=M; i++){
        int a, b;
        cin >> a >> b;
        a = getrt(a);
        b = getrt(b);
        if(a == b){
            continue;
        }
        else{
            num--;
            par[a] = b;
        }
    }
    int ans = 0;
    for(; 1LL*num*(num-1)/2 > K; num--){
        ans++;
    }
    cout << ans << endl;
}

#include <bits/stdc++.h>

using namespace std;

int N, M;
int par[100005];

int getrt(int n){
    return par[n] = (par[n] == n ? n : getrt(par[n]));
}

int main(){
    cin >> N >> M;
    for(int i = 1; i<=N; i++){
        par[i] = i;
    }
    while(M--){
        int a, b, c;
        cin >> a >> b >> c;
        if(getrt(a) != getrt(b)){
            N--;
            par[getrt(a)] = getrt(b);
        }
    }
    cout << N << endl;
}

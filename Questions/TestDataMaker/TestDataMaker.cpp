#include <bits/stdc++.h>

using namespace std;

mt19937 g1(chrono::steady_clock::now().time_since_epoch().count());

int randint(int a, int b){
    return uniform_int_distribution<int>(a, b)(g1);
}

int N = 300000, Q = 1;

int main(){
    cout.tie(0);
    freopen("in.txt", "w", stdout);
    cout << N << " " << Q << "\n";
    for(int i = 1; i<=N; i++){
        cout << randint(1, N) << " ";
    }
    cout << "\n";
    for(int q = 1; q<=Q; q++){
        int l = randint(1, N), r = randint(1, N), k = randint(2, 5);
        if(l > r){
            swap(l, r);
        }
        cout << l << " " << r << " " << k << "\n";
    }
}

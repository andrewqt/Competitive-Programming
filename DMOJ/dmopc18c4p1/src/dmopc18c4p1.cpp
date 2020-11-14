#include <bits/stdc++.h>

using namespace std;

long double N, S, tot, crnt;





int main(){
    cin >> N;
    cin >> S;
    tot = 0;
    for(int i =1 ; i<=N; i++){
        int n;
        tot += S;
        cin >> n;
        for(int j = 1; j<=n; j++){
            long double d;
            cin >> d;
            tot += d;
        }
    }
    tot /= N;
    cout << setprecision(4);
    cout << tot << endl;
}

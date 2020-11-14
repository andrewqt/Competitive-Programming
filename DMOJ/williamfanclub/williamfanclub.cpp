#include <bits/stdc++.h>

using namespace std;

int N;

int query(int a, int b){
    cout << "? " << a << " " << b << endl;
    int k;
    cin >> k;
    return k;
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N;
    int crnt = 1;
    for(int i = 2; i<=N; i++){
        if(!query(i, crnt)){
            crnt = i;
        }
    }
    cout << "! " << crnt << endl;
}

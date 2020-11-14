#include <bits/stdc++.h>

using namespace std;

int N;
int ans[100005];

int main(){
    cin >> N;
    if(N == 1){
        cout << 1 << endl;
    }
    if(N == 2){
        cout << -1 << endl;
    }
    if(N <= 2){
        return 0;
    }
    ans[1] = 2;

}

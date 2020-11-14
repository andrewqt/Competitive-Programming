#include <bits/stdc++.h>

using namespace std;

bool tkn[10000000];
int N;

int main(){
    cin >> N;
    for(int i = 1; i<=N; i++){
        int n;
        cin >> n;
        tkn[n] = 1;
    }
    int cnt = 0;
    for(int i = 1; i<=N; i++){
        if(!tkn[i]){
            cnt++;
        }
    }
    cout << cnt << endl;
}

#include <bits/stdc++.h>

using namespace std;

int main(){
    int N, K;
    cin >> N >> K;
    if(N == 1){
        if(!K){
            cout << "0 0 1 1" << endl;
        }
        else{
            cout << -1 << endl;
        }
    }
    else{
        if((1<<N) <= K){
            cout << -1 << endl;
        }
        else{
            for(int i = 0; i<(1<<N); i++){
                if(i != K){
                    cout << i << " ";
                }
            }
            cout << K << " ";
            for(int i = (1<<N)-1; i>=0; i--){
                if(i != K){
                    cout << i << " ";
                }
            }
            cout << K << endl;
        }
    }
}
